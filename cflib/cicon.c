/*
 * CFLIB, a GEM library for ATARI/TOS
 * Copyright (C) 1999, 2000 Christian Felsch
 * Copyright (C) Olaf Meisiek
 * 
 * Modified for FreeMiNT CVS by Frank Naumann <fnaumann@freemint.de>
 * 
 * Please send suggestions, patches or bug reports to me or
 * the MiNT mailing list.
 * 
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
 * 
 */

#include <osbind.h>

#include "intern.h"


static int pal_init = FALSE;
static short farbtbl[256][32];
static short rgb_palette[256][4];

static void
fill_farbtbl (int screen_planes, int handle)
{
	if ((screen_planes > 8) && !pal_init)
	{
		short np, color, pxy[8], backup[32], rgb[3];
		MFDB screen;
		MFDB pixel = { NULL, 16, 1, 1, 0, 1, 0, 0, 0 };
		MFDB stdfm = { NULL, 16, 1, 1, 1, 1, 0, 0, 0 };
		short pixtbl[16] =
			{ 0, 2, 3, 6, 4, 7, 5, 8, 9, 10, 11, 14, 12, 15, 13,
				16 };

		for (color = 0; color < 255; color++)
		{
			if (color < 16)
			{
				vq_color (handle, pixtbl[color], 1,
					  rgb_palette[color]);
				rgb_palette[color][3] = pixtbl[color];
			}
			else
			{
				vq_color (handle, color - 1, 1,
					  rgb_palette[color]);
				rgb_palette[color][3] = color - 1;
			}
		}
		vq_color (handle, 1, 1, rgb_palette[255]);
		rgb_palette[255][3] = 1;

		vs_clip (handle, FALSE, pxy);

		memset (farbtbl, 0, sizeof (farbtbl));
		memset (backup, 0, sizeof (backup));
		screen.fd_addr = NULL;
		stdfm.fd_nplanes = pixel.fd_nplanes = screen_planes;

		vsl_ends (handle, 0, 0);
		vsl_type (handle, 1);
		vsl_width (handle, 1);
		memset (pxy, 0, sizeof (pxy));

		graf_mouse (M_OFF, NULL);

		pixel.fd_addr = backup;	/* Punkt retten */
		vro_cpyfm (handle, S_ONLY, pxy, &screen, &pixel);

		/* Alte Farbe retten */
		vq_color (handle, 15, 1, rgb);

		for (color = 0; color < 256; color++)
		{
			vs_color (handle, 15, rgb_palette[color]);

			vsl_color (handle, 15);
			v_pline (handle, 2, pxy);

			stdfm.fd_addr = pixel.fd_addr = farbtbl[color];

			/* vro_cpyfm, weil v_get_pixel nicht mit TrueColor (24 Planes) funktioniert */
			vro_cpyfm (handle, S_ONLY, pxy, &screen, &pixel);
			vr_trnfm (handle, &pixel, &stdfm);
			for (np = 0; np < screen_planes; np++)
				if (farbtbl[color][np])
					farbtbl[color][np] = 0xffff;
		}

		/* Alte Farbe restaurieren */
		vs_color (handle, 15, rgb);

		pixel.fd_addr = backup;	/* Punkt restaurieren */
		vro_cpyfm (handle, S_ONLY, pxy, &pixel, &screen);

		graf_mouse (M_ON, NULL);
		pal_init = TRUE;
	}
}

static void
fix_cdata (short *col_data, long len, int old_planes, int new_planes)
{
	long x, i, old_len, rest_len, mul[32], pos;
	short np, *new_data, mask, pixel, bit, color, back[32], old_col[32],
		maxcol = 0;

	if (old_planes == new_planes)
		return;

	len >>= 1;
	if (new_planes <= 8)
	{
		old_len = old_planes * len;
		rest_len = new_planes * len - old_len;
		new_data = &col_data[old_len];

		for (x = 0; x < len; x++)
		{
			mask = 0xffff;

			for (i = 0; i < old_len; i += len)
				mask &= col_data[x + i];

			if (mask)
				for (i = 0; i < rest_len; i += len)
					new_data[x + i] |= mask;
		}
	}
	else			/* TrueColor, bzw RGB-orientierte Pixelwerte */
	{
		if (old_planes < 8)
		{
			maxcol = (1 << old_planes) - 1;
			memcpy (old_col, farbtbl[maxcol],
				new_planes * sizeof (short));
			memset (farbtbl[maxcol], 0,
				new_planes * sizeof (short));
		}

		for (i = 0; i < new_planes; i++)
			mul[i] = i * len;

		for (x = 0; x < len; x++)
		{
			bit = 1;
			for (np = 0; np < old_planes; np++)
				back[np] = col_data[mul[np] + x];

			for (pixel = 0; pixel < 16; pixel++)
			{
				color = 0;
				for (np = 0; np < old_planes; np++)
				{
					color += ((back[np] & 1) << np);
					back[np] >>= 1;
				}

				for (np = 0; np < new_planes; np++)
				{
					pos = mul[np] + x;
					col_data[pos] =
						(col_data[pos] & ~bit) |
						(farbtbl[color][np] & bit);
				}

				bit <<= 1;
			}
		}
		if (old_planes < 8)
			memcpy (farbtbl[maxcol], old_col,
				new_planes * sizeof (short));
	}
}

CICON *
fix_cicon (CICONBLK *cicnblk, short screen_planes, short handle)
{
	short best_planes, find_planes;
	short *buf1, *buf2 = NULL;
	CICON *cicn, *new_icn = NULL, *best_icn = NULL;
	long len, *next;
	MFDB s, d;

	len = cicnblk->monoblk.ib_wicon / 8 * cicnblk->monoblk.ib_hicon;

	best_planes = 1;
	if (screen_planes > 8)
	{
		fill_farbtbl (screen_planes, handle);
		find_planes = 4;
	}
	else
		find_planes = screen_planes;

	cicn = cicnblk->mainlist;
	next = (long *) &cicnblk->mainlist;
	while (cicn != NULL)
	{
		*next = (long) cicn;
		next = (long *) &cicn->next_res;

		if (cicn->num_planes >= best_planes
		    && cicn->num_planes <= find_planes)
		{
			best_planes = cicn->num_planes;
			best_icn = cicn;
		}
		cicn = cicn->next_res;
	}

	if (best_icn != NULL)	/* passendes Farbicon gefunden */
	{
		new_icn = cf_malloc (sizeof (CICON), "fix_cicon", FALSE);
		*new_icn = *best_icn;

		if (best_planes > 1)
			new_icn->num_planes = screen_planes;
		else
			new_icn->num_planes = 1;

		new_icn->col_data =
			cf_malloc (len * screen_planes, "fix_cicon", FALSE);
		new_icn->sel_data =
			cf_malloc (len * screen_planes, "fix_cicon", FALSE);

		if (best_planes > 1)
		{
			buf1 =
				cf_malloc (len * screen_planes, "fix_cicon",
					   FALSE);
			memset (buf1, 0, len * screen_planes);
			memcpy (buf1, best_icn->col_data, len * best_planes);

			buf2 =
				cf_malloc (len * screen_planes, "fix_cicon",
					   FALSE);
			memset (buf2, 0, len * screen_planes);
			memcpy (buf2, best_icn->sel_data, len * best_planes);

			if (best_planes < screen_planes)
			{
				fix_cdata (buf1, len, best_planes,
					   screen_planes);
				if (best_icn->sel_data)
					fix_cdata (buf2, len, best_planes,
						   screen_planes);
			}

			d.fd_addr = new_icn->col_data;
			d.fd_w = cicnblk->monoblk.ib_wicon;
			d.fd_h = cicnblk->monoblk.ib_hicon;
			d.fd_wdwidth = d.fd_w >> 4;
			d.fd_stand = 0;
			d.fd_nplanes = screen_planes;

			s.fd_addr = buf1;
			s.fd_w = d.fd_w;
			s.fd_h = d.fd_h;
			s.fd_wdwidth = d.fd_wdwidth;
			s.fd_stand = 1;
			s.fd_nplanes = d.fd_nplanes;

			vr_trnfm (handle, &s, &d);

			s.fd_addr = buf2;
			d.fd_addr = new_icn->sel_data;
			vr_trnfm (handle, &s, &d);

			Mfree (buf2);
			Mfree (buf1);
		}
		else
		{
			memcpy (new_icn->col_data, best_icn->col_data, len);
			memcpy (new_icn->sel_data, best_icn->sel_data, len);
		}
	}
	else
	{
		/* normales Icon anpassen */
		d.fd_addr = cicnblk->monoblk.ib_pmask;
		d.fd_w = cicnblk->monoblk.ib_wicon;
		d.fd_h = cicnblk->monoblk.ib_hicon;
		d.fd_wdwidth = d.fd_w >> 4;
		d.fd_stand = 0;
		d.fd_nplanes = screen_planes;

		s.fd_addr = cicnblk->monoblk.ib_pmask;
		s.fd_w = d.fd_w;
		s.fd_h = d.fd_h;
		s.fd_wdwidth = d.fd_wdwidth;
		s.fd_stand = 1;
		s.fd_nplanes = d.fd_nplanes;

		vr_trnfm (handle, &s, &d);

		s.fd_addr = cicnblk->monoblk.ib_pdata;
		d.fd_addr = cicnblk->monoblk.ib_pdata;
		vr_trnfm (handle, &s, &d);
	}
	return new_icn;
}

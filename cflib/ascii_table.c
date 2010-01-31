/*
 * CFLIB, a GEM library for ATARI/TOS
 * Copyright (C) 1999, 2000 Christian Felsch
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

#ifdef __MINT__
  #include <osbind.h>
#else
  #include <tos.h>
#endif

#include "app.h"
#include "intern.h"
#include "inline.h"


static int last_ascii;

static void
_redraw_obj (OBJECT * tree, short obj)
{
	GRECT r;

	get_objframe (tree, obj, &r);
	objc_draw (tree, obj, 1, r.g_x, r.g_y, r.g_w, r.g_h);
}

static void
set_numbers (short code)
{
	char str[6];

	sprintf (str, "%03d", code);
	set_string (cf_ascii_tab, AT_DEZ, str);
	_redraw_obj (cf_ascii_tab, AT_DEZ);

	sprintf (str, "0x%02X", code);
	set_string (cf_ascii_tab, AT_HEX, str);
	_redraw_obj (cf_ascii_tab, AT_HEX);
}

static void
draw_ascii (short id, short pts)
{
	short wc, hc, wb, hb, d, i, x, y;
	GRECT r;
	char c[2] = "x";

	vst_font (cf_vdi_handle, id);
	vst_point (cf_vdi_handle, pts, &wc, &hc, &wb, &hb);
	vst_alignment (cf_vdi_handle, TA_CENTER, TA_TOP, &d, &d);
	vswr_mode (cf_vdi_handle, MD_TRANS);
	vst_color (cf_vdi_handle, 1);

	get_objframe (cf_ascii_tab, AT_BOX, &r);
	set_clipping (cf_vdi_handle, r.g_x, r.g_y, r.g_w, r.g_h, TRUE);
	x = r.g_x + gl_wbox / 2;
	y = r.g_y + 1;
	for (i = 0; i < 256; i++)
	{
		c[0] = i;
		v_gtext (cf_vdi_handle, x, y, c);
		x += gl_wbox;
		if (((i + 1) % 16) == 0)
		{
			y += gl_hbox;
			x = r.g_x + gl_wbox / 2;
		}
	}
	set_clipping (cf_vdi_handle, r.g_x, r.g_y, r.g_w, r.g_h, FALSE);
}

static int
get_ascii (short x, short y)
{
	short x1, y1;

	objc_offset (cf_ascii_tab, AT_BOX, &x1, &y1);
	x -= x1;
	y -= y1;
	if ((x < 0) || (y < 0))
		return -1;

	x /= gl_wbox;
	y /= gl_hbox;
	if ((x < 16) && (y < 16))
		return (x + y * 16);
	else
		return -1;
}

static void
select_ascii (short obj)
{
	short pxy[4], x, y;

	objc_offset (cf_ascii_tab, AT_BOX, &x, &y);
	pxy[0] = x + (obj % 16) * gl_wbox;
	pxy[1] = y + (obj / 16) * gl_hbox;
	pxy[2] = pxy[0] + gl_wbox - 1;
	pxy[3] = pxy[1] + gl_hbox - 1;

	graf_mouse (M_OFF, NULL);
	vsf_color (cf_vdi_handle, G_BLACK);
	vsf_interior (cf_vdi_handle, FIS_SOLID);
	vswr_mode (cf_vdi_handle, MD_XOR);
	v_bar (cf_vdi_handle, pxy);
	graf_mouse (M_ON, NULL);
}

static void
jump_to (short new)
{
	if (last_ascii != -1)
		select_ascii (last_ascii);
	select_ascii (new);
	last_ascii = new;
	set_numbers (new);
}

short
ascii_table (short id, short pts)
{
	short event, mx, my, kstate, kreturn, breturn, bclicks;
	short d, obj, code = -1;
	MFDB background;
	GRECT r;
	int quit;

	set_string (cf_ascii_tab, AT_DEZ, "000");
	set_string (cf_ascii_tab, AT_HEX, "0x00");

	wind_update (BEG_UPDATE);
	wind_update (BEG_MCTRL);
	form_center (cf_ascii_tab, &r.g_x, &r.g_y, &r.g_w, &r.g_h);
	save_background (&r, &background);
	form_dial (FMD_START, 0, 0, 0, 0, r.g_x, r.g_y, r.g_w, r.g_h);
	graf_mouse (M_OFF, NULL);
	objc_draw (cf_ascii_tab, ROOT, MAX_DEPTH, r.g_x, r.g_y, r.g_w, r.g_h);
	draw_ascii (id, pts);
	graf_mouse (M_ON, NULL);

	last_ascii = -1;
	quit = FALSE;
	graf_mkstate (&mx, &my, &d, &d);
	do
	{
		event = evnt_multi (MU_BUTTON | MU_KEYBD | MU_M1,
				    1, 1, 1,
				    1, mx, my, 1, 1,
				    0, 0, 0, 0, 0,
				    NULL, 0,
				    &mx, &my, &breturn, &kstate, &kreturn,
				    &bclicks);
		if (event & MU_M1)
		{
			obj = get_ascii (mx, my);
			if ((obj != -1) && (obj != last_ascii))
				jump_to (obj);
		}
		if (event & MU_BUTTON)
		{
			obj = get_ascii (mx, my);
			if (obj != -1)
			{
				code = obj;
				quit = TRUE;
			}
			else
			{
				if (objc_find (cf_ascii_tab, ROOT, MAX_DEPTH, mx, my)
					== AT_ABBRUCH)
				{
					code = -1;
					quit = TRUE;
				}
				else
					Bconout (2, 7);
			}
		}
		if (event & MU_KEYBD)
		{
			int scan;

			scan = kreturn >> 8;
			switch (scan)
			{
				case 0x61:	/* UNDO */
					code = -1;
					quit = TRUE;
					break;

				case 0x1C:	/* Return */
				case 0x72:	/* Enter */
					if (last_ascii != -1)
						code = last_ascii;
					else
						code = -1;
					quit = TRUE;
					break;

				case 0x47:	/* HOME */
					if (kstate & K_SHIFT)
						jump_to (255);
					else
						jump_to (0);
					break;

				case 0x4F:	/* MagiCMac: anti-HOME */
					jump_to (255);
					break;

				case 0x4B:	/* Left */
					if (last_ascii == -1)
						jump_to (0);
					else
					{
						if (kstate & K_SHIFT)
						{
							d = last_ascii % 16;
							jump_to (last_ascii - d);
						}
						else if (last_ascii > 0)
							jump_to (last_ascii - 1);
					}
					break;

				case 0x4D:	/* Right */
					if (last_ascii == -1)
						jump_to (0);
					else
					{
						if (kstate & K_SHIFT)
						{
							d = last_ascii % 16;
							jump_to (last_ascii + (15 - d));
						}
						else if (last_ascii < 255)
							jump_to (last_ascii + 1);
					}
					break;

				case 0x48:	/* Up */
					if (last_ascii == -1)
						jump_to (0);
					else if (last_ascii > 15)
						jump_to (last_ascii - 16);
					break;
				case 0x50:	/* Down */
					if (last_ascii == -1)
						jump_to (0);
					else if (last_ascii < 240)
						jump_to (last_ascii + 16);
					break;
			}
		}
	}
	while (!quit);

	form_dial (FMD_FINISH, 0, 0, 0, 0, r.g_x, r.g_y, r.g_w, r.g_h);
	restore_background (&r, &background);
	wind_update (END_MCTRL);
	wind_update (END_UPDATE);

	return code;
}

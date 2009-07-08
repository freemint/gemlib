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

#include <osbind.h>
#include <gemx.h>

#include "app.h"
#include "intern.h"


/* -- Selectric -------------------------------------------------------------- */

typedef struct
{
	unsigned long id;	/* Selectric ID (SLCT)          */
	unsigned short version;	/* version (BCD-Format)         */
	struct
	{
		unsigned:7;	/* reserved                                                     */
		unsigned todaytime:1;
		unsigned pthsav:1;	/* save GEMDOS paths                            */
		unsigned stdest:1;	/* stay in destination path     */
		unsigned:1;	/* reserved                                                     */
		unsigned numsrt:1;	/* numsort                                                      */
		unsigned lower:1;	/* use lowercase letters                */
		unsigned dclick:1;	/* open folder on dclick                */
		unsigned hidden:1;	/* show hidden files                            */
		unsigned bypass:1;	/* Selectric ON/OFF                             */
	}
	config;
	short sort;		/* sort-mode (neg. = rev.)      */
	short num_ext;		/* number of extensions         */
	char *(*ext)[];		/* preset extensions            */
	short num_paths;	/* number of paths              */
	char *(*paths)[];	/* preset paths                 */
	short comm;		/* communication word           */
	short in_count;		/* input counter                */
	void *in_ptr;		/* input pointer                */
	short out_count;	/* output counter               */
	void *out_ptr;		/* output pointer               */
	void *f1;
	void *f2;
	void *f3;
}
SLCT;

#define SLCT_ANZ 10
static SLCT *slct = NULL;


static inline int
slct_check (void)
{
	long l;

	if (getcookie ("FSEL", &l))
	{
		slct = (SLCT *) l;
		if (slct && slct->id != 0x534c4354L)	/* 'SLCT' */
			slct = NULL;
		if (slct && !slct->config.bypass)	/* Selectric auch aktiv? */
			slct = NULL;
	}
	if (slct && (slct->version >= 0x100))
		return TRUE;
	else
		return FALSE;
}

/* -- MagiC ------------------------------------------------------------------ */
static inline int
do_magx (char *path, char *name, char *mask, char *title, FSEL_CB open_cb)
{
	int ok = FALSE;
	void *fsl;
	char def_mask[] = "*\0\0", pat[50], *p, hist_path[256] = "\0\0";
	short num, flags = 0, but, i, j, win, ret;
	EVNT ev;

	j = 0;
	if ((mask[0] != '\0') && strcmp (mask, "*") != 0)
	{
		p = mask;
		j = 0;
		while (*p != '\0')
		{
			pat[j++] = *p;
			p++;
		}
		pat[j++] = '\0';
	}
	for (i = 0; i < 5; i++)
		pat[j++] = def_mask[i];

	if (path[0] != '\0')
	{
		strcpy (hist_path, path);
		i = (int) strlen (path);
		hist_path[i + 1] = '\0';	/* Doppelnull am Ende! */
	}

	if (open_cb != NULL)
		flags |= GETMULTI;

	if (!cf_msg_cb)		/* keine Msg-Routine -> modal */
	{
		i = SORTBYNAME;
		fsl = fslx_do (title, path, 256, name, 60, pat, 0L, hist_path,
			       &i, flags, &but, &num, &p);
		if (fsl)
		{
		}
	}
	else
	{
		fsl =
			fslx_open (title, -1, -1, &win, path, 256, name, 60,
				   pat, 0L, hist_path, SORTBYNAME, flags);
		if (fsl)
		{
			disable_menu ();
			do
			{
#ifdef __GNUC__
				short msg[8];
				short k, mx, my, mb, mc, ks, kr;

				/*
				 * GNU erwartet beim evnt_multi wirklich 'int', in EVNT sind aber
				 * nur 'short', so daû die Struktur nicht Åbergeben werden kann!
				 */
				ev.mwhich =
					evnt_multi (MU_KEYBD |
							    MU_MESAG |
							    MU_BUTTON, 2, 1,
							    1, 0, 0, 0, 0, 0,
							    0, 0, 0, 0, 0,
							    msg, 0, &mx, &my,
							    &mb, &ks, &kr,
							    &mc);
				ev.mx = mx;
				ev.my = my;
				ev.mbutton = mb;
				ev.kstate = ks;
				ev.key = kr;
				ev.mclicks = mc;
				for (k = 0; k < 8; k++)
					ev.msg[k] = msg[k];
#else				
				ev.mwhich =
					(short) evnt_multi (MU_KEYBD |
							    MU_MESAG |
							    MU_BUTTON, 2, 1,
							    1, 0, 0, 0, 0, 0,
							    0, 0, 0, 0, 0,
							    (int *) ev.msg, 0,
							    (int *) &ev.mx,
							    (int *) &ev.my,
							    (int *) &ev.
							    mbutton,
							    (int *) &ev.
							    kstate,
							    (int *) &ev.key,
							    (int *) &ev.
							    mclicks);
#endif
				if (ev.mwhich & MU_MESAG)
				{
					switch (ev.msg[0])
					{
						case WM_REDRAW:
						case WM_MOVED:
						case WM_SIZED:
							if (ev.msg[3] != win)	/* fÅr fremdes Fenster */
							{
#ifdef __GNUC__
								handle_mdial_msg (msg);
#else
								handle_mdial_msg ((int *) ev.msg);
#endif
							}
							break;

						case WM_BOTTOMED:	/* nicht erlaubt! */
							break;

						case WM_TOPPED:
						case WM_NEWTOP:
						case WM_ONTOP:
							ev.msg[0] = WM_TOPPED;	/* immer Filebox toppen! */
							ev.msg[3] = win;
							break;
					}

				}
				ret =
					fslx_evnt (fsl, &ev, path, name, &but,
						   &num, &k, &p);
			}
			while (ret == 1);
			enable_menu ();
		}
	}

	if (fsl)
	{
		if (but == 1)
		{
			if (flags & GETMULTI)
			{
				do
				{
					open_cb (path, name);
					i = fslx_getnxtfile (fsl, name);
				}
				while (i);

				/* leeren */
				path[0] = '\0';
				name[0] = '\0';
			}
			else
			{
				p = strrchr (path, '\\');	/* Maske abhacken */
				p[1] = '\0';
				make_normalpath (path);
			}
			ok = TRUE;
		}
		fslx_close (fsl);
	}
	return ok;
}

/* --------------------------------------------------------------------------- */

int
select_file (char *path, char *name, char *mask, char *title, FSEL_CB open_cb)
{
	short slct_multi = FALSE;
	short but, i, d;
	char *p;
	char *files[SLCT_ANZ];
	int ok = FALSE;

	if (path[0] == '\0')	/* kein Pfad -> aktuellen holen */
		get_path (path, 0);
	else
		make_normalpath (path);

	if (slct_check ())
	{
		if (open_cb != NULL)	/* Selectric-mehrfach Auswahl */
		{
			for (i = 0; i < SLCT_ANZ; i++)
				files[i] =
					cf_malloc (256, "select_file", FALSE);
			slct->comm = 1;
			slct->out_count = SLCT_ANZ;
			slct->out_ptr = files;
			slct_multi = TRUE;
		}
	}
	else if (appl_xgetinfo (7, &i, &d, &d, &d) && (i & 8))
		return do_magx (path, name, mask, title, open_cb);

	/* normale Auswahl */
	if (mask[0] == '\0')
		strcat (path, "*.*");
	else
		strcat (path, mask);

	wind_update (BEG_UPDATE);
	/*      wind_update(BEG_MCTRL); */
	if (slct || gl_gem >= 0x140)
		fsel_exinput (path, name, &but, title);
	else
		fsel_input (path, name, &but);
	/*      wind_update(END_MCTRL); */
	wind_update (END_UPDATE);
	ok = (but == 1);
	if (ok)
	{
		p = strrchr (path, '\\');	/* Maske abhacken */
		p[1] = '\0';
		make_normalpath (path);

		if (slct_multi)	/* Mehrfach-Selectrics */
		{
			short cont = TRUE;

			i = 0;
			while (cont && (i < slct->out_count))
			{
				cont = open_cb (path, files[i]);
				i++;
			}
			for (i = 0; i < SLCT_ANZ; i++)
				if (files[i] != NULL)
					Mfree (files[i]);

			/* leeren */
			path[0] = '\0';
			name[0] = '\0';
		}
		else if (open_cb)	/* Callback, aber keine Mahrfachauswahl */
		{
			open_cb (path, name);

			/* leeren */
			path[0] = '\0';
			name[0] = '\0';
		}
	}
	return ok;
}

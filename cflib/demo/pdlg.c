/*
 * demo programm for the CFLIB
 * Copyright (C) 1999, 2000 Christian Felsch
 * 
 * Modified for FreeMiNT CVS by Frank Naumann <fnaumann@freemint.de>
 * 
 * Please send suggestions, patches or bug reports to me or
 * the MiNT mailing list.
 * 
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 * 
 * This file is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 * 
 */

#include <cflib.h>
#include "demo.h"
#include "pdlg.h"

#ifdef __MTAES__
#include <prdialog.h>
#include <prsettng.h>
#define __CDECL cdecl
#else
#include <gemx.h>
#endif


/* Event-Routine der MDials */
extern void handle_mdial_msg (int *msg);

#ifndef FALSE
#define FALSE	0
#define TRUE	1
#endif


#if defined(__GNUC__) && defined(__MSHORT__)

extern OBJECT *popups;

/*
 * Callbacks fÅr Sub-Dialog
 */
static long __CDECL
init_qed_sub (PRN_SETTINGS * settings, PDLG_SUB * sub_dialog)
{
	OBJECT *tree;
	int offset;

	tree = sub_dialog->tree;
	offset = sub_dialog->index_offset;

	set_string (tree, PS_WPNAME + offset, "<unbekannt>");
	set_int (tree, PS_WPSL + offset, 65);
	set_int (tree, PS_WPZL + offset, 80);

	set_string (tree, PS_GFNAME + offset, "6x6 system font");
	set_int (tree, PS_GFPTS + offset, 10);

	return 1;
}

static long __CDECL
#ifdef __MTAES__
do_qed_sub (PRN_SETTINGS * settings, PDLG_SUB * sub_dialog, int exit_obj)
#else
do_qed_sub (PRN_SETTINGS * settings, PDLG_SUB * sub_dialog, short exit_obj)
#endif
{
	OBJECT *tree;
	int offset;
	int id = 1, pts = 10;

	tree = sub_dialog->tree;
	offset = sub_dialog->index_offset;
	switch (exit_obj - offset)
	{
		case PS_WPDSTR:
		case PS_WPDPOP:
			if ((exit_obj - offset) == PS_WPDPOP)
				handle_popup (tree, PS_WPDPOP + offset,
					      popups, DICHTEPOP, POP_OPEN);
			else
				handle_popup (tree, PS_WPDPOP + offset,
					      popups, DICHTEPOP, POP_CYCLE);
			break;

		case PS_WPSEL:
			set_state (tree, exit_obj, SELECTED, FALSE);
			redraw_obj (tree, exit_obj);
			break;

		case PS_GFSEL:
			do_fontsel ((FS_M_XFSL | FS_M_MAGX),
				    "Druckerfont wÑhlen", &id, &pts);
			set_state (tree, exit_obj, SELECTED, FALSE);
			redraw_obj (tree, exit_obj);
			break;
	}
	return 1;
}

static long __CDECL
reset_qed_sub (PRN_SETTINGS * settings, PDLG_SUB * sub_dialog)
{
	/*
	 * OBJECT       *tree;
	 * int          offset;
	 * 
	 * tree = sub_dialog->tree;
	 * offset = sub_dialog->index_offset;
	 */
	return 1;
}


static PDLG_SUB *
create_sub_dialog (void)
{
	PDLG_SUB *sub = NULL;
	OBJECT *tree;

	sub = malloc (sizeof (PDLG_SUB));
	if (sub)
	{
		sub->next = 0L;
		sub->option_flags = 0;
		sub->sub_id = -1;

		rsrc_gaddr (R_TREE, PDLGICON, &tree);
		sub->sub_icon = tree + PRN_ICON;	/* Zeiger auf das Icon */

		rsrc_gaddr (R_TREE, PRN_SUB, &tree);
		sub->sub_tree = tree;	/* Zeiger auf den Unterdialogs */

		sub->dialog = 0L;	/* Zeiger auf die Struktur des Fensterdialogs oder 0L */
		sub->tree = 0L;	/* Zeiger auf den zusammengesetzen Objektbaum */
		sub->index_offset = 0;	/* Indexverschiebung des Unterdialogs */
		sub->reserved1 = 0;
		sub->reserved2 = 0;

		sub->init_dlg = init_qed_sub;	/* Initialisierungsfunktion */
		sub->do_dlg = do_qed_sub;	/* Behandlungsfunktion */
		sub->reset_dlg = reset_qed_sub;	/* ZurÅcksetzfunktion */
		sub->reserved3 = 0;
	}
	return sub;
}


static int
wlfp_available (void)
{
	int ag1, ag2, ag3, ag4;

	if (appl_xgetinfo (7, &ag1, &ag2, &ag3, &ag4))
	{
		if ((ag1 & 0x17) == 0x17)
			return 1;
	}
	return 0;
}

/* --------------------------------------------------------------------------- */
static void
save_settings (PRN_SETTINGS * settings)
{
	/*
	 * fd = fopen("i:\\pdlg.set", "wb");
	 * if (fd)
	 * {
	 * 	fwrite(settings, 1, sizeof(PRN_SETTINGS), fd);
	 * 	fclose(fd);
	 * }
	 */
}

static PRN_SETTINGS *
load_settings (PRN_DIALOG * prn_dialog)
{
	PRN_SETTINGS *set = NULL;

	set = pdlg_new_settings (prn_dialog);
	if (set)
	{
		/*
		 * fd = fopen("i:\\pdlg.set", "rb");
		 * if (fd)
		 * {
		 * 	fread(set, 1, sizeof(PRN_SETTINGS), fd);
		 * 	fclose(fd);
		 * }
		 * else
		 */
		pdlg_dflt_settings (prn_dialog, set);
	}
	return set;
}
#endif

/* --------------------------------------------------------------------------- */
void
test_pdlg (int in_win)
{
#if defined(__GNUC__) && !defined(__MSHORT__)
	do_alert (1, 0,
		  "[3][pdlg und GNU geht nicht, da ich nicht|"
		  "weiss, wie ich ohne -mshort eine 16bit|"
		  "ParameterÅbergabe realisiere!][schade]");
	return;
#else
	if (wlfp_available ())
	{
		PRN_SETTINGS *prn_settings;
		PRN_DIALOG *prn_dialog;
		int d, button, ret, handle;
		EVNT ev;

#ifdef __MTAES__
		MOBLK n = { 0, 0, 0, 0, 0 };
#endif

		prn_dialog = pdlg_create (PDLG_3D);
		if (prn_dialog)
		{
			PDLG_SUB *sub_dialog;

			if (in_win)
				disable_menu ();

			/* Settings holen */
			prn_settings = load_settings (prn_dialog);

			/* Unterdialoge einhÑngen */
			sub_dialog = create_sub_dialog ();
			if (sub_dialog)
				pdlg_add_sub_dialogs (prn_dialog, sub_dialog);

			if (in_win)
			{
				/* Fenster-Dialog durchfÅhren */

				handle =
					pdlg_open (prn_dialog, prn_settings,
						   "qed", 0x0000, -1, -1);

				/* ob das wohl erlaubt ist?? :-)) */
#ifdef __MTAES__
				wind_set_string (handle, WF_NAME,
						 " Drucker-Konfiguration ");
#else
				wind_set_str (handle, WF_NAME,
					      " Drucker-Konfiguration ");
#endif
				do
				{
#ifdef __MTAES__
					EVNT_multi (MU_KEYBD | MU_MESAG |
						    MU_BUTTON, 2, 1, 1, &n,
						    &n, 0L, &ev);
#else
					ev.mwhich =
						(short) evnt_multi (MU_KEYBD |
								    MU_MESAG |
								    MU_BUTTON,
								    2, 1, 1,
								    0, 0, 0,
								    0, 0, 0,
								    0, 0, 0,
								    0,
								    (int *) ev.msg,
								    0,
								    (int *) &ev.mx,
								    (int *) &ev.my,
								    (int *) &ev.mbutton,
								    (int *) &ev.kstate,
								    (int *) &ev.key,
								    (int *) &ev.mclicks);
#endif
					if (ev.mwhich & MU_MESAG)
					{
						switch (ev.msg[0])
						{
							case WM_REDRAW:
							case WM_MOVED:
							case WM_SIZED:
								if (ev.msg[3] != handle)	/* fÅr fremdes Fenster */
								{
									handle_mdial_msg ((int *) ev.msg);
								}
								break;

								case
							WM_BOTTOMED:	/* nicht erlaubt! */
								break;

							case WM_TOPPED:
							case WM_NEWTOP:
							case WM_ONTOP:
								ev.msg[0] = WM_TOPPED;	/* immer Druckerbox toppen! */
								ev.msg[3] =
									handle;
								break;
						}

					}
					ret =
						pdlg_evnt (prn_dialog,
							   prn_settings, &ev,
							   &button);
				}
				while (ret == 1);

				pdlg_close (prn_dialog, &d, &d);
			}
			else
			{
				/* normalen Dialog durchfÅhren */
				button = pdlg_do (prn_dialog, prn_settings,
						 "document name", 0x0000);
				debug ("pdlg_do(): %d\n", button);
			}

			if (button == PDLG_OK)
				save_settings (prn_settings);

			if (sub_dialog)
			{
				pdlg_remove_sub_dialogs (prn_dialog);
				free (sub_dialog);
			}

			pdlg_free_settings (prn_settings);
			pdlg_delete (prn_dialog);

			if (in_win)
				enable_menu ();
		}
	}
	else
		form_alert (1, "[1][WDialog ist nicht installiert!][Schade]");
#endif
}

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

#ifndef FALSE
#define FALSE	0
#define TRUE	1
#endif

#ifdef __MTAES__
#define wind_create_grect(a,b)		wind_create(a,b)
#define wind_calc_grect(a,b,c,d)	wind_calc(a,b,c,d)
#define wind_open_grect(a,b)		wind_open(a,b)
#define wind_set_str(a,b,c)		wind_set_string(a,b,c)
extern int rc_intersect (GRECT * r1, GRECT * r2);
#endif

/* --------------------------------------------------------------------------- */
OBJECT         *menu, *objdial, *popdial, *wicon, *popups, *about;
WDIALOG        *wdial;
int             quit;
int             msg[8], vdi_handle;
int             event, msx, msy, mbutton, kstate, mclick, kreturn, win_handle;
int             modal = FALSE;
int             id = 1, pts = 10;

static void     handle_msg (int *msg);

/* --------------------------------------------------------------------------- */
/* 
 * Ein Dummy-Fenster, daû einfach nur da ist, damit man sieht, daû bei 
 * app-modalen Dialogen Redraw-, Move- und Size-Aktionen ausgewertet 
 * werden.
 */
static void
redraw_win (int handle, int xc, int yc, int wc, int hc)
{
	GRECT t1, t2;
	int temp[4];

	hide_mouse ();
	wind_update (TRUE);
	t2.g_x = xc;
	t2.g_y = yc;
	t2.g_w = wc;
	t2.g_h = hc;
	wind_get_grect (handle, WF_FIRSTXYWH, &t1);
	vsf_color (vdi_handle, 0);

	wind_get (handle, WF_WORKXYWH, &temp[0], &temp[1], &temp[2],
		  &temp[3]);
	temp[2] += temp[0] - 1;
	temp[3] += temp[1] - 1;

	while (t1.g_w && t1.g_h)
	{
		if (rc_intersect (&t2, &t1))
		{
			set_clipping (vdi_handle, t1.g_x, t1.g_y, t1.g_w,
				      t1.g_h, TRUE);
			v_bar (vdi_handle, temp);
		}
		wind_get (handle, WF_NEXTXYWH, &t1.g_x, &t1.g_y, &t1.g_w,
			  &t1.g_h);
	}
	wind_update (FALSE);
	show_mouse ();
}

static void
open_win (void)
{
	int work_out[57];
	GRECT r = { 100, 100, 350, 150 };

	vdi_handle = open_vwork (work_out);
	win_handle =
		wind_create_grect ((NAME | MOVER | CLOSER | SIZER), &gl_desk);
	wind_set_str (win_handle, WF_NAME, " Fenster ");
	wind_open_grect (win_handle, &r);
}

static void
win_msg (int *msg)
{
	if (msg[3] == win_handle)
	{
		switch (msg[0])
		{
			case WM_CLOSED:
				wind_close (win_handle);
				break;
			case WM_BOTTOMED:
				wind_set (win_handle, WF_BOTTOM, 0, 0, 0, 0);
				break;
			case WM_REDRAW:
				redraw_win (win_handle, msg[4], msg[5],
					    msg[6], msg[7]);
				break;
			case WM_NEWTOP:
			case WM_TOPPED:
				wind_set (win_handle, WF_TOP, 0, 0, 0, 0);
				break;
			case WM_MOVED:
				wind_set (win_handle, WF_CURRXYWH, msg[4],
					  msg[5], msg[6], msg[7]);
				break;
			case WM_SIZED:
				wind_set (win_handle, WF_CURRXYWH, msg[4],
					  msg[5], msg[6], msg[7]);
				break;
		}
	}
}

/* --------------------------------------------------------------------------- */

static void
modal_dial (void)
{
	int antw, edit;
	GRECT r;

	wind_update (BEG_UPDATE);
#ifdef __MTAES__
	form_center (objdial, &r);
	form_dial (FMD_START, &r, &r);
	objc_draw (objdial, ROOT, MAX_DEPTH, &r);
#else
	form_center (objdial, &r.g_x, &r.g_y, &r.g_w, &r.g_h);
	form_dial (FMD_START, r.g_x, r.g_y, r.g_w, r.g_h, r.g_x, r.g_y, r.g_w,
		   r.g_h);
	objc_draw (objdial, ROOT, MAX_DEPTH, r.g_x, r.g_y, r.g_w, r.g_h);
#endif

	edit = EDIT1;
	do
	{
		antw = cf_form_do (objdial, &edit);
	}
	while (antw != ENDE && antw != UNDO);
	set_state (objdial, antw, SELECTED, FALSE);
#ifdef __MTAES__
	form_dial (FMD_FINISH, &r, &r);
#else
	form_dial (FMD_FINISH, r.g_x, r.g_y, r.g_w, r.g_h, r.g_x, r.g_y,
		   r.g_w, r.g_h);
#endif
	wind_update (END_UPDATE);
	if (antw == ENDE)
		quit = TRUE;
}

/* --------------------------------------------------------------------------- */

static void
appmodal_dial (void)
{
	void *mdial;
	int close = FALSE;
	int id, exit_obj;

	mdial = open_mdial (objdial, EDIT1);
	while (!close)
	{
		exit_obj = do_mdial (mdial);
		switch (exit_obj)
		{
			case EXITBUT:
				do_walert (1, 2,
					   "[1][Mdial ist re-entrant!][Toll]",
					   "Alert");
				break;

			case ENDE:
				quit = TRUE;
				close = TRUE;
				break;

			case HELP:
				id = appl_find ("ST-GUIDE");
				if (id > 0)
					send_vastart (id, "*:\\cflib.hyp");
				break;

			case UNDO:
				close = TRUE;
				break;
		}
		if (get_flag (objdial, exit_obj, EXIT))
			set_state (objdial, exit_obj, SELECTED, FALSE);
		if (!close)
			redraw_mdobj (mdial, exit_obj);
	}
	close_mdial (mdial);
}

/* --------------------------------------------------------------------------- */

static POPUP pop;

static void
set_popcolor (int s_obj, OBJECT * d_tree, int d_obj)
{
	OBSPEC spec;
	int color;

	spec.index = get_obspec (popups, s_obj);
	color = spec.obspec.interiorcol;	/* neue Farbe holen */
	spec.index = get_obspec (d_tree, d_obj);
	spec.obspec.interiorcol = color;	/* neue Farbe setzen */
	set_obspec (d_tree, d_obj, spec.index);
}

static void
nonmodal_open_cb (WDIALOG * wd)
{
	char str[10];

	/* dynamisches Popup anlegen */
	set_string (wd->tree, P1TEXT, "bla");
	create_popup (&pop, 5, 23, " zeile1");
	append_popup (&pop, " zeile2zeile2");
	append_popup (&pop, " zeile3zeile3zeile3");

	get_string (popups, 20 /*POPF1 */ , str);
	set_string (wd->tree, P2BOX, str);

	get_string (popups, CPWHITE, str);
	set_string (wd->tree, P3BOX, str);
	set_popcolor (CPWHITE - 16, wd->tree, P3COL);
}

static int
nonmodal_exit_cb (WDIALOG * wd, int obj)
{
	int close = FALSE;
	int y;
	char s[30];

	switch (obj)
	{
		case P1STR:
		case P1BOX:
			y =
				handle_popup (wd->tree, P1BOX, pop.tree, 0,
					      POP_OPEN);
			if (y > 0)
			{
				get_string (pop.tree, y, s);
				set_string (wd->tree, P1TEXT, s + 1);
				redraw_wdobj (wd, P1TEXT);
			}
			break;

		case P2STR:
		case P2BOX:
			if (obj == P2STR)
				handle_popup (wd->tree, P2BOX, popups,
					      FUNCPOP, POP_CYCLE);
			else
				handle_popup (wd->tree, P2BOX, popups,
					      FUNCPOP, POP_OPEN);
			break;

		case P3STR:
		case P3BOX:
			if (obj == P3STR)
				y =
					handle_popup (wd->tree, P3BOX, popups,
						      COLPOP, POP_CYCLE);
			else
				y =
					handle_popup (wd->tree, P3BOX, popups,
						      COLPOP, POP_OPEN);
			if (y > 0)
			{
				set_popcolor (y - 16, wd->tree, P3COL);
				redraw_wdobj (wd, P3COL);
			}
			break;

		case P4BOX:
			handle_popup (NULL, 0, popups, POPUP4, POP_OPEN);
			break;

		case P5STR:
		case P5BOX:
			if (obj == P5STR)
				y =
					handle_colorpop (wd->tree, P5BOX,
							 POP_CYCLE, 8, 0);
			else
				y =
					handle_colorpop (wd->tree, P5BOX,
							 POP_OPEN, 8, 0);
			set_state (wd->tree, obj, SELECTED, FALSE);
			redraw_wdobj (wd, P5BOX);
			break;

		case WD_CLOSER:
			close = TRUE;
			debug ("Closer ohne UNDO-Button!\n");
			break;

	}
	if (close)
		free_popup (&pop);
	return close;
}

/* --------------------------------------------------------------------------- */
static int
fsel_cb (char *path, char *name)
{
	/* hier laufen die Dateinamen/Pfade bei einer Mehrfach-Dateiselektion auf */
	/* wird solange von select_file() aufgerufen, wie TRUE zurÅckgegeben wird. */

	return TRUE;
}

/* --------------------------------------------------------------------------- */
static void
handle_menu (int title, int item)
{
	switch (item)
	{
		case MABOUT:
			if (modal)
				simple_dial (about, 0);
			else
				simple_mdial (about, 0);
			break;


		case MFSEL:
		{
			char            path[50] = "", name[50] = "";

			if (select_file
			    (path, name, "", "Dateiauswahl im Fenster",
			     fsel_cb) && path[0])
				debug ("    %s%s\n", path, name);
		}
			break;

		case MENDE:
			quit = TRUE;
			break;


		case MDIAL1:
			if (modal)
				modal_dial ();
			else
				appmodal_dial ();
			break;

		case MDIAL2:
			open_wdial (wdial, -1, -1);
			break;

		case MALERT:
			if (modal)
				do_alert (1, 2,
					  "[1][Dies ist ein modaler Alert.][OK|UNDO]");
			else
				do_walert (1, 3,
					   "[3][Dies ist ein Alert im Fenster.|Mit Text in der zweiten Zeile|und drei Buttons.|Und UNDO auf Abbruch!][Ja|Nein|Abbruch]",
					   " Fenster-Alert ");
			break;

		case MFONTSEL:
			if (!do_fontsel
			    ((FS_M_MAGX | FS_M_XFSL), "Im Fenster", &id, &pts)
			    && (id == -1))
			{
				if (modal)
					do_alert (1, 0,
						  "[3][Keine Fontauswahl verfÅgbar!][OK]");
				else
					do_walert (1, 0,
						   "[3][Keine Fontauswahl verfÅgbar!][OK]",
						   "Alert");
				id = 1;
				pts = 10;
			}
			break;

		case MPDLG:
			test_pdlg (!modal);
			break;

		case MASCII:
			set_asciitable_strings ("Aktueller Font", "");
			ascii_table (id, 10);
			break;


		case MMODAL:
		case MFENSTER:
			if (!modal && item == MMODAL)
				modal = TRUE;
			else if (modal && item == MFENSTER)
				modal = FALSE;
			menu_icheck (menu, MMODAL, modal);
			menu_icheck (menu, MFENSTER, !modal);
			break;


		default:
			if (title == TSCUT)
			{
				char            str[50], s2[50];

				get_string (menu, item, str);
				sprintf (s2, "[1][%s][OK]", str);
				if (modal)
					do_alert (1, 0, s2);
				else
					do_walert (1, 0, s2,
						   "MenÅ: Shortcuts");
			}
			break;
	}
	menu_tnormal (menu, title, 1);
}

static void
handle_msg (int *msg)
{
	if (!message_wdial (msg))
	{
		switch (msg[0])
		{
			case MN_SELECTED:
				handle_menu (msg[3], msg[4]);
				break;

			case WM_CLOSED:
			case WM_BOTTOMED:
			case WM_REDRAW:
			case WM_NEWTOP:
			case WM_TOPPED:
			case WM_MOVED:
			case WM_SIZED:
				win_msg (msg);
				break;

			case AP_TERM:
				quit = TRUE;
				break;
		}
	}
}

/* --------------------------------------------------------------------------- */

int
main (void)
{
	OBJECT *tree;
	char tmp[20];

#ifdef __MTAES__
	GRECT           n = { 0, 0, 0, 0 };
	EVNTDATA        ev;
#endif

	init_app ("demo.rsc");
	init_colorpop (8);

	rsrc_gaddr (R_TREE, MENUTREE, &menu);
	create_menu (menu);
	menu_icheck (menu, MMODAL, modal);
	menu_icheck (menu, MFENSTER, !modal);

	rsrc_gaddr (R_TREE, OBJDIAL, &objdial);
	fix_dial (objdial);

	rsrc_gaddr (R_TREE, POPDIAL, &tree);
	fix_dial (tree);
	fix_colorpopobj (tree, P5BOX, 0);
	rsrc_gaddr (R_TREE, WINICON, &wicon);
	wdial =
		create_wdial (tree, wicon, P1TEXT, nonmodal_open_cb,
			      nonmodal_exit_cb);

	rsrc_gaddr (R_TREE, POPUPS, &popups);
	fix_menu (popups);

	rsrc_gaddr (R_TREE, ABOUT, &about);
	fix_menu (about);
	get_patchlev (__Ident_cflib, tmp);
	set_string (about, A_PL, tmp);

	rsrc_gaddr (R_TREE, PRN_SUB, &tree);
	fix_dial (tree);

	/* Callback fÅr modale Fensterdialoge, Fenster-Alerts usw. */
	set_mdial_wincb (handle_msg);

	open_win ();

	quit = FALSE;

	while (!quit)
	{
		mbutton = 0;
#ifdef __MTAES__
		event = evnt_multi (MU_MESAG | MU_BUTTON | MU_KEYBD,
				    1, 1, 1,
				    0, &n, 0, &n,
				    msg, 0, &ev, &kreturn, &mclick);
		msx = ev.x;
		msy = ev.y;
		mbutton = ev.bstate;
		kstate = ev.kstate;
#else
		event = evnt_multi (MU_MESAG | MU_BUTTON | MU_KEYBD,
				    1, 1, 1,
				    0, 0, 0, 0, 0,
				    0, 0, 0, 0, 0,
				    msg,
				    0,
				    &msx, &msy, &mbutton, &kstate,
				    &kreturn, &mclick);
#endif

		if (event & MU_MESAG)
			handle_msg (msg);

		if (event & MU_BUTTON)
		{
			if (!click_wdial (mclick, msx, msy, kstate, mbutton))
				;
		}
		if (event & MU_KEYBD)
		{
			if (!key_wdial (kreturn, kstate))
			{
				int             title, item;

				if (is_menu_key
				    (kreturn, kstate, &title, &item))
					handle_menu (title, item);
			}
		}
	}
	delete_wdial (wdial);
	wind_close (win_handle);
	wind_delete (win_handle);
	v_clsvwk (vdi_handle);

	delete_menu ();
	exit_app (0);
	return 0;
}

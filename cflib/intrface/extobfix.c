/*
 * ExtObFix programm for InterFace
 * Copyright (C) 1998, 1999, 2000 Christian Felsch
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

#ifndef FALSE
#define FALSE	0
#define TRUE	1
#endif

/* compatibility */

/* object flags */
#define NONE		 	0x0000
#define SELECTABLE		0x0001
#define DEFAULT			0x0002
#define EXIT			0x0004
#define EDITABLE		0x0008
#define RBUTTON			0x0010
#define LASTOB			0x0020
#define TOUCHEXIT		0x0040
#define HIDETREE		0x0080
#define INDIRECT		0x0100
#define FL3DIND			0x0200	/* bit 9 */
#define FL3DBAK			0x0400	/* bit 10 */
#define FL3DACT			0x0600
#define SUBMENU			0x0800	/* bit 11 */
#define FLAG11			SUBMENU
#define FLAG12			0x1000
#define FLAG13			0x2000
#define FLAG14			0x4000
#define FLAG15			0x8000

/* Object states */
#define NORMAL			0x0000
#define SELECTED		0x0001
#define CROSSED			0x0002
#define CHECKED			0x0004
#define DISABLED		0x0008
#define OUTLINED		0x0010
#define SHADOWED		0x0020
#define WHITEBAK		0x0040
#define DRAW3D			0x0080
#define STATE08			0x0100
#define STATE09			0x0200
#define STATE10			0x0400
#define STATE11			0x0800
#define STATE12			0x1000
#define STATE13			0x2000
#define STATE14			0x4000
#define STATE15			0x8000

#include "exthelp.rsh"
#include "exthelp.h"

/****** Functions ************************************************************/

long pinit_obfix (short status);

static void fix_objs (OBJECT * tree, short is_dialog);
static void (*get_name) (void *window, short obj, char *txt);
static void test_form (OBJECT *tree, short editobj, long get_n, void *window);
static short test_alert (short def, char *str);

/****** Variables ************************************************************/

#ifdef __GNUC__
__attribute__((__used__))
#endif
static long routines[] =
{
	(long) fix_objs,
	(long) test_alert,
	(long) test_form,
	(long) &rs_object[0],
	30363130L, 31393635L,
	(long) pinit_obfix,
};

/*****************************************************************************/

static void
fix_objs (OBJECT * tree, short is_dialog)
{
	fix_dial (tree);
}

/*****************************************************************************/

static void
test_form (OBJECT *tree, short editobj, long get_n, void *window)
{
	short x, y, w, h, but, zw;
	char name[20], buf[80];

	*(long *) &get_name = get_n;

	fix_objs (tree, TRUE);

	wind_update (BEG_UPDATE);
	form_center (tree, &x, &y, &w, &h);
	form_dial (FMD_START, 0, 0, 0, 0, x, y, w, h);

	do
	{
		objc_draw (tree, ROOT, MAX_DEPTH, x, y, w, h);
		but = cf_form_do (tree, &editobj);

		/* keine TOUCHEXITs deselektieren */
		if (get_flag (tree, but, EXIT))
			set_state (tree, but, SELECTED, FALSE);

		(*get_name) (window, but, name);
		sprintf (buf, rs_frstr[EXITALERT], but, name);
		zw = do_alert (1, 2, buf);
	}
	while (zw == 1);

	form_dial (FMD_FINISH, 0, 0, 0, 0, x, y, w, h);
	wind_update (END_UPDATE);
	but = 0;
}

/*****************************************************************************/
static short
test_alert (short def, char *str)
{
	return do_alert (def, 0, str);
}

/*****************************************************************************/

int
main (void)
{
	extern char __Ident_cflib[];
	char pl[10], str[80];

	appl_init ();
	get_patchlev (__Ident_cflib, pl);
	sprintf (str, "[0][ExtObFix, used by InterFace.|CF-Lib PL%s, %s][OK]", pl, __DATE__);
	form_alert (1, str);
#ifndef __GNUC__
	{
	static long dummy;
	dummy = routines[6];	/* Sonst wird die Struktur von Pure C wegoptimiert... */
	}
#endif
	appl_exit ();
	return 0;
}

/*****************************************************************************/

long
pinit_obfix (short status)
{
	short i;

	if (status == TRUE)
	{
		init_app (NULL);

		/* Inline-RSC anpassen */
		for (i = 0; i < NUM_OBS; i++)
			rsrc_obfix (&rs_object[i], 0);
		return ((long) routines);
	}
	else
	{
		exit_gem ();
	}
	return 0;
}

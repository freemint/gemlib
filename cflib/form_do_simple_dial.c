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

/*
 * Ein eigener form_do(), der einige Sondertastentasten kann:
 * 
 * HELP     Button mit Flag11
 * UNDO     Button mit Flag12
 * ^C^V^X   Klemmbrett in Editfeldern
 * ALT-X    MagiC-Shortcut
 *
 */

#include "intern.h"


int
simple_dial (OBJECT * tree, int start_edit)
{
	int exit_obj;
	GRECT r;

#ifdef __MTAES__
	GRECT n = { 0, 0, 0, 0 };
#endif

	graf_mouse (ARROW, NULL);
	wind_update (BEG_UPDATE);
#ifdef __MTAES__
	form_center (tree, &r);
	form_dial (FMD_START, &n, &r);
	graf_mouse (M_OFF, NULL);
	objc_draw (tree, ROOT, MAX_DEPTH, &r);
	graf_mouse (M_ON, NULL);
	exit_obj = cf_form_do (tree, &start_edit) & 0x7FFF;
	form_dial (FMD_FINISH, &n, &r);
#else
	form_center (tree, &r.g_x, &r.g_y, &r.g_w, &r.g_h);
	form_dial (FMD_START, 0, 0, 0, 0, r.g_x, r.g_y, r.g_w, r.g_h);
	graf_mouse (M_OFF, NULL);
	objc_draw (tree, ROOT, MAX_DEPTH, r.g_x, r.g_y, r.g_w, r.g_h);
	graf_mouse (M_ON, NULL);
	exit_obj = cf_form_do (tree, &start_edit) & 0x7FFF;
	form_dial (FMD_FINISH, 0, 0, 0, 0, r.g_x, r.g_y, r.g_w, r.g_h);
#endif
	wind_update (END_UPDATE);
	set_state (tree, exit_obj, SELECTED, FALSE);
	return exit_obj;
}

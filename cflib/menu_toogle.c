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
 * Verwaltung die Menleiste der Applikation.
 * ACHTUNG: Nicht re-entrant, d.h. jede Applikation nur ein Kreuz, „h Men!
 */

#include "menu.h"


static void
toggle_menu (short dis)
{
	if ((__menu_tree != NULL) && (__menu_disabled != dis))
	{
		short titel;

		wind_update (BEG_UPDATE);
		titel = __menu_tree[3].ob_next;	/* 3: Desk-Titel */
		while (titel != 2)	/* 2: Box, die die Titel umgibt */
		{
			set_state (__menu_tree, titel, OS_DISABLED, dis);
			titel = __menu_tree[titel].ob_next;
		}
		menu_bar (__menu_tree, TRUE);

		/* Ersten String (About) suchen */
#ifdef G_SHORTCUT
		while (!
		       (__menu_tree[titel].ob_type == G_STRING
			|| __menu_tree[titel].ob_type == G_SHORTCUT))
#else
		/* FIXME ... */
		while (!(__menu_tree[titel].ob_type == G_STRING))
#endif
			titel++;
		menu_ienable (__menu_tree, titel, !dis);

		__menu_disabled = dis;

		wind_update (END_UPDATE);
	}
}

void
disable_menu (void)
{
	if (__menu_tree != NULL)
	{
		__menu_dis_cnt++;
		if (__menu_dis_cnt == 1)
			toggle_menu (TRUE);
	}
}

void
enable_menu (void)
{
	if (__menu_tree != NULL)
	{
		if (__menu_dis_cnt > 0)
			__menu_dis_cnt--;
		if (__menu_dis_cnt == 0)
			toggle_menu (FALSE);
	}
}

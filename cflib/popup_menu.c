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

#include "intern.h"


/*
 * Emulation/Erweiterung von menu_popup().
 * Falls Button = 0 und das System menu_popup() hat, wird dieses aufgerufen.
 * Ist Button = 1/2 (linke/rechte Maustaste), wird das Popup selbst verwaltet.
 * Es geht dann z.B. sofort auf (nicht wie bei menu_popup() erst beim Loslassen
 * der Taste).
 * offset gibt den Offset zwischen Root und dem ersten Popup-String an (i.d.R.
 * ist offset 0, bei einem Farb-Popup aber z.B. nicht).
 */
int
cf_menu_popup (MENU * m1, int x, int y, MENU * m2, int button, int offset)
{
	int i, d;

	if ((button == 0) && appl_xgetinfo (9, &d, &i, &d, &d) && (i == 1))	/* gibts menu_popup? */
		return menu_popup (m1, x, y, m2);
	else
	{
		OBJECT *tree;
		int root, m_x, m_y, event, item,
			msg[8], olditem, kstate, mask, clicks;
		GRECT box, r;
		MFDB save;

#ifdef __MTAES__
		EVNTDATA ev;
		GRECT n = { 0, 0, 0, 0 };
#endif

		tree = m1->mn_tree;
		root = m1->mn_menu;
		item = m1->mn_item;

		tree[root].ob_x = x;
		tree[root].ob_y =
			y -
			((item - offset - root - 1) * tree[item].ob_height);

		/* bei RSM liegt der das Popup enthaltende Dialog nicht unbedingt bei (0,0)!! */
		if (root != 0 && tree[0].ob_x > 0)
			tree[0].ob_x = 0;
		if (root != 0 && tree[0].ob_y > 0)
			tree[0].ob_y = 0;

		box.g_x = tree[root].ob_x - 1;
		box.g_y = tree[root].ob_y - 1;
		box.g_w = tree[root].ob_width + 4;
		box.g_h = tree[root].ob_height + 4;

		wind_update (BEG_MCTRL);
		save_background (&box, &save);
		graf_mouse (ARROW, NULL);

		if (button == 0)
			button = 1;

#ifdef __MTAES__
		graf_mkstate (&ev);
		m_x = ev.x;
		m_y = ev.y;
		i = ev.bstate;
#else
		graf_mkstate (&m_x, &m_y, &i, &d);
#endif

		if (i & button)	/* Taste immer noch gedrckt? */
		{
			clicks = 1;	/* -> evnt_multi wartet auf Loslassen /der/ Taste */
			mask = button;
		}
		else
		{
			clicks = 0x101;	/* -> evnt_multi wartet auf Drcken /einer/ Taste */
			mask = 3;
		}

#ifdef __MTAES__
		objc_draw (tree, root, MAX_DEPTH, &box);
#else
		objc_draw (tree, root, MAX_DEPTH, box.g_x, box.g_y, box.g_w,
			   box.g_h);
#endif

		olditem = -1;
		do
		{
			item = objc_find (tree, root, MAX_DEPTH, m_x, m_y);
			if ((item == root) || !popup_valid_item (tree, item))
				item = -1;

			if (item != olditem)
			{
				if (olditem != -1)
#ifdef __MTAES__
					objc_change (tree, olditem, 0, &box,
						     tree[olditem].
						     ob_state & (~SELECTED),
						     TRUE);
#else
					objc_change (tree, olditem, 0,
						     box.g_x, box.g_y,
						     box.g_w, box.g_h,
						     tree[olditem].
						     ob_state & (~SELECTED),
						     TRUE);
#endif

				if (item != -1)
#ifdef __MTAES__
					objc_change (tree, item, 0, &box,
						     tree[item].
						     ob_state | SELECTED,
						     TRUE);
#else
					objc_change (tree, item, 0, box.g_x,
						     box.g_y, box.g_w,
						     box.g_h,
						     tree[item].
						     ob_state | SELECTED,
						     TRUE);
#endif
			}
			if (item != -1)
			{
				objc_offset (tree, item, &r.g_x, &r.g_y);
				r.g_w = tree[item].ob_width;
				r.g_h = tree[item].ob_height;
			}
			else
			{
				r.g_x = m_x;
				r.g_y = m_y;
				r.g_w = 1;
				r.g_h = 1;
			}

#ifdef __MTAES__
			ev.bstate = 0;
			event = evnt_multi ((MU_BUTTON | MU_M1),
					    clicks, mask, 0,
					    1, &r, 0, &n,
					    msg, 0L, &ev, &d, &d);
			m_x = ev.x;
			m_y = ev.y;
			kstate = ev.kstate;
#else
			d = 0;
			event = evnt_multi ((MU_BUTTON | MU_M1),
					    clicks, mask, 0,
					    1, r.g_x, r.g_y, r.g_w, r.g_h,
					    0, 0, 0, 0, 0,
					    msg,
					    0L,
					    &m_x, &m_y, &d, &kstate, &d, &d);
#endif

			olditem = item;
		}
		while (!(event & MU_BUTTON));

		restore_background (&box, &save);
		wind_update (END_MCTRL);

		if (item == -1)
			item = 0;
		else
			tree[item].ob_state &= ~SELECTED;

		if (m2 != NULL)
		{
			if (m1 != m2)
				memcpy (m2, m1, sizeof (MENU));
			m2->mn_item = item;
			m2->mn_keystate = kstate;
		}
		return (item != 0);
	}
}

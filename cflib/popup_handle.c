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


short
handle_popup (OBJECT * dial, short dial_obj, OBJECT *pop, short pop_obj,
	      short mode)
{
	char active_str[50] = "", s[50];
	short first, last, item, i, first_offset;
	short x, y;
	MENU m1, m2;
	GRECT r;
	int down_pop;

	if (pop == NULL)
		return -1;

	first = pop[pop_obj].ob_head;
	while (!popup_valid_item (pop, first))
		first++;

	last = pop[pop_obj].ob_tail;
	while (!popup_valid_item (pop, last))
		last--;

	/* falls erste Spalte z.B. Farbmarke */
	first_offset = first - pop[pop_obj].ob_head;

	item = first;
	down_pop = FALSE;

	if (dial != NULL)
	{
		/* Popup-Typ ermitteln */
		down_pop = (get_obtype (dial, dial_obj, NULL) == G_BOXCHAR);

		if (!down_pop)
		{
			/* Zun„chst das aktuelle, im Dialog eingetragene Popup-Item suchen */
			get_string (dial, dial_obj, active_str);
			item = first;
			while (item <= last)
			{
				get_string (pop, item, s);
				if (strcmp (active_str, s) == 0)
					break;
				item++;
			}
			if (item > last)	/* nicht gefunden */
				item = first;
		}
	}

	switch (mode)
	{
		case POP_OPEN:
			/* Position des Popups ermitteln */
			if (dial != NULL)
			{
				objc_offset (dial, dial_obj, &x, &y);
				if (down_pop)
					x -=
						(pop[1].ob_width -
					      dial[dial_obj].ob_width);
				else
				{
					/* mehrspaltiges Popups? */
					if (pop[pop_obj].ob_height <=
					    ((item - first) * gl_hchar))
					{
						get_objframe (pop, item, &r);
						x -= r.g_w;
						item -=
							(pop[pop_obj].
							 ob_height /
							 gl_hchar);
					}
				}

				/* aužerhalb des Bildschirms? */
				get_objframe (pop, pop_obj, &r);

				if (x < gl_desk.g_x)
					x = gl_desk.g_x;
				if ((x + r.g_w) > (gl_desk.g_x + gl_desk.g_w))
					x =
						(gl_desk.g_x + gl_desk.g_w) -
						r.g_w;

				i = (last - item + 1) * gl_hchar;
				if ((y + i) > (gl_desk.g_y + gl_desk.g_h))
					y = (gl_desk.g_y + gl_desk.g_h) - i;

				i = (item - first) * gl_hchar;
				if (y - i < gl_desk.g_y)
					y = gl_desk.g_y + i;

			}
			else
			{
				graf_mkstate (&x, &y, &i, &i);
				get_objframe (pop, item, &r);
				x -= r.g_w / 2;
				y -= r.g_h / 2;
				if (first_offset > 0)
					y -= (first_offset * gl_hchar);
			}
			m1.mn_tree = pop;
			m1.mn_menu = pop_obj;
			m1.mn_item = item;
			i = cf_menu_popup (&m1, x, y, &m2, 1, first_offset);
			if (i != 0)
				item = m2.mn_item;
			else
				item = 0;
			break;

		case POP_CYCLE:
			i = 0;
			do
			{
				item++;
				i++;
				if (item > last)
					item = first;
			}
			while (((pop[item].ob_state & OS_DISABLED) ||
				!(pop[item].ob_flags & OF_SELECTABLE)) &&
			       i <= last - first);

			if (i > last - first)
				item = 0;
			break;

		default:
			debug ("\ahandle_popup: unbekannter Modus %d.\n",
			       mode);
	}

	/* Text des neuen Popup-Items in den Dialog eintragen und neu zeichnen */
	if ((!down_pop) && (item > 0) && (dial != NULL))
	{
		get_string (pop, item, s);
		set_string (dial, dial_obj, s);
		get_objframe (dial, dial_obj, &r);
		objc_draw (dial, dial_obj, 1, r.g_x, r.g_y, r.g_w, r.g_h);
	}

	return item;
}

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

#include "wdial.h"


/*
 * Dialog-Fenster îffnen.
 */
void
open_wdial (WDIALOG *wd, short pos_x, short pos_y)
{
	GRECT r1, r2;
	short d;

	if (wd != NULL)
	{
		if (wd->mode == WD_OPEN)	/* ist schon offen */
		{
			wind_set (wd->win_handle, WF_TOP, 0, 0, 0, 0);
			return;
		}
		if (wd->mode & WD_ICON)	/* ist iconified */
		{
			uniconify_wdial (wd, -1, 0, 0, 0);
			return;
		}
		if (wd->mode & WD_SHADE)	/* ist shaded */
		{
			wind_set (wd->win_handle, WF_SHADE, 0, 0, 0, 0);
			wd->mode &= ~WD_SHADE;
			return;
		}
		else if (wd->win_handle > 0)	/* war schon mal offen */
		{
			if (wd->open_cb != NULL)
				(wd->open_cb) (wd);
			wind_calc_grect (WC_BORDER, wd->win_kind, &wd->work,
					 &r1);
			wind_open_grect (wd->win_handle, &r1);
			wd->mode = WD_OPEN;
			return;
		}
		else		/* alles neu */
		{
			/* Rahmen abschalten */
			wd->tree[0].ob_spec.obspec.framesize = 0;

			if ((pos_x == -1) || (pos_y == -1))	/* Zentrieren */
				form_center (wd->tree, &r1.g_x, &r1.g_y,
					     &r1.g_w, &r1.g_h);
			else
			{
				wd->tree[0].ob_x = pos_x;
				wd->tree[0].ob_y = pos_y;
			}

			r1.g_x = wd->tree[0].ob_x;
			r1.g_y = wd->tree[0].ob_y;

			/* Titel nicht mitzeichnen */
			if (wd->title_obj != -1)
			{
				wd->delta_y =
					(wd->tree[wd->title_obj].ob_y +
					 wd->tree[wd->title_obj].ob_height);
				wd->tree[0].ob_y -= wd->delta_y;
				set_flag (wd->tree, wd->title_obj, OF_HIDETREE,
					  TRUE);
			}
			else
				wd->delta_y = 0;

			r1.g_w = wd->tree[0].ob_width;
			r1.g_h = wd->tree[0].ob_height - wd->delta_y;

			wind_calc_grect (WC_BORDER, wd->win_kind, &r1, &r2);

			/* Fenster neu zentrieren */
			d = (r2.g_h - r1.g_h) / 2 + wd->delta_y / 2;
			r2.g_y += d;
			wd->tree[0].ob_y += d;
			/* herausragen ins MenÅ verhindern */
			if (r2.g_y < gl_desk.g_y)
			{
				wd->tree[0].ob_y += (gl_desk.g_y - r2.g_y);
				r2.g_y = gl_desk.g_y;
			}

			wd->win_handle =
				wind_create_grect (wd->win_kind, &r2);
			if (wd->win_handle > 0)
			{
				wind_set_str (wd->win_handle, WF_NAME,
					      wd->win_name);
				if (wd->open_cb != NULL)
					(wd->open_cb) (wd);
				wind_open_grect (wd->win_handle, &r2);
				wind_calc_grect (WC_WORK, wd->win_kind, &r2,
						 &wd->work);
				wd->mode = WD_OPEN;
			}
			else
				form_alert (1,
					    "[3][wdial.Open:|Kein Fenster mehr frei!][oops]");
		}
	}
}

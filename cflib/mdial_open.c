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

#include "mdial.h"


MDIAL *
open_mdial (OBJECT *tree, short edit_start)
{
	GRECT r1, r2;
	MDIAL *dial;
	short center = FALSE;

	dial = cf_malloc (sizeof (MDIAL), "open_mdial", FALSE);
	if (dial)
	{
		memset (dial, 0, sizeof (MDIAL));
		dial->tree = tree;

		dial->next = __mdial_md_list;
		__mdial_md_list = dial;

		/* Rahmen abschalten */
		dial->save_frame = tree[0].ob_spec.obspec.framesize;
		tree[0].ob_spec.obspec.framesize = 0;

		/* Zentrieren, nur beim ersten Mal */
		if (tree[0].ob_x == 0 && tree[0].ob_y == 0)
		{
			form_center (tree, &r1.g_x, &r1.g_y, &r1.g_w, &r1.g_h);
			center = TRUE;
		}

		/* Fenstertitel holen und ausblenden */
		if (get_magx_obj (tree, 1) == MX_UNDERLINE)
		{
			dial->win_name = (char *) get_obspec (tree, 1);
			dial->delta_y = (tree[1].ob_y + tree[1].ob_height);
			dial->tree[0].ob_y -= dial->delta_y;
			set_flag (tree, 1, OF_HIDETREE, TRUE);
		}
		else
			dial->win_name = NULL;

		/* Editfeld */
		if ((edit_start <= 0) || !edit_valid (dial->tree, edit_start))
			dial->edit_obj =
				find_edit (dial->tree, 0, FMD_FORWARD);
		else
			dial->edit_obj = edit_start;

		r1.g_x = tree[0].ob_x;
		r1.g_y = tree[0].ob_y + dial->delta_y;
		r1.g_w = tree[0].ob_width;
		r1.g_h = tree[0].ob_height - dial->delta_y;
		wind_calc_grect (WC_BORDER, KIND, &r1, &r2);

		/* Fenster neu zentrieren */
		if (center)
		{
			int d;

			d = (r2.g_h - r1.g_h) / 2 + dial->delta_y / 2;
			r2.g_y += d;
			tree[0].ob_y += d;
			/* herausragen ins MenÅ verhindern */
			if (r2.g_y < gl_desk.g_y)
			{
				tree[0].ob_y += (gl_desk.g_y - r2.g_y);
				r2.g_y = gl_desk.g_y;
			}
		}

		dial->win_handle = wind_create_grect (KIND, &r2);
		if (dial->win_handle > 0)
		{
			short msg[8];

			/* MenÅ abschalten */
			disable_menu ();

			if (dial->win_name)
				wind_set_str (dial->win_handle, WF_NAME,
					      dial->win_name);
			wind_open_grect (dial->win_handle, &r2);

			/* den REDRAW noch abholen */
			while (TRUE)
			{
				evnt_mesag (msg);
				handle_mdial_msg (msg);
				if ((msg[0] == WM_REDRAW)
				    && (msg[3] == dial->win_handle))
					break;
			}
		}
		else
		{
			close_mdial (dial);
			dial = NULL;
		}
	}

	return dial;
}

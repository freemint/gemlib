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


void
get_objframe (OBJECT *tree, short obj, GRECT *r)
{
	short d, i;
	short type, shadow = 0, outline = 0, line = 0;

	objc_offset (tree, obj, &r->g_x, &r->g_y);
	r->g_w = tree[obj].ob_width;
	r->g_h = tree[obj].ob_height;

	type = get_obtype (tree, obj, NULL);
	switch (type)
	{
		case G_STRING:
#ifdef G_SHORTCUT
		case G_SHORTCUT:
#endif
		case G_ICON:
		case G_CICON:
			/* nichts mehr zu tun */
			return;

		case G_BUTTON:
			line = 1;
			if (tree[obj].ob_flags & OF_DEFAULT)
				line++;
			if (tree[obj].ob_flags & OF_EXIT)
				line++;
			if (line && tree[obj].ob_state & OS_SHADOWED)
				shadow = 2 * line;
			break;

		case G_TEXT:
		case G_FTEXT:
			line = -(tree[obj].ob_spec.tedinfo->te_thickness);
			if (line && (tree[obj].ob_state & OS_SHADOWED))
				shadow = abs (line * 2);
			else
				line = 0;
			break;

		case G_BOXTEXT:
		case G_FBOXTEXT:
			line = -(tree[obj].ob_spec.tedinfo->te_thickness);
			if (line && (tree[obj].ob_state & OS_SHADOWED))
				shadow = abs (line * 2);
			break;

		case G_BOX:
		case G_IBOX:
		case G_BOXCHAR:
			line = -(tree[obj].ob_spec.obspec.framesize);
			if (line && tree[obj].ob_state & OS_SHADOWED)
				shadow = abs (line * 2);
			break;

		default:
			/*
			 * {
			 * char s[80];
			 * sprintf(s, "[3][CF-Lib Hinweis: get_objframe()!|Objekt %d hat unbekannten Typ %d|!][soso]", obj, type);
			 * form_alert(1, s);
			 * }
			 */
			return;
	}

	if (tree[obj].ob_state & OS_OUTLINED)
		outline = 3;

	if (line > 0)
	{
		outline = max (outline, line);
		shadow += line;
	}

	if (outline)
	{
		r->g_x -= outline;
		r->g_y -= outline;
		r->g_w += outline;
		r->g_h += outline;
	}

	if (shadow)
	{
		r->g_w += max (outline, shadow);
		r->g_h += max (outline, shadow);
	}
	else
	{
		r->g_w += outline;
		r->g_h += outline;
	}

	if ((appl_xgetinfo (13, &d, &i, &d, &d) && i == 1) &&
	    (tree[obj].ob_flags & OF_FL3DACT))
	{
		short hinc = 0, vinc = 0;

		objc_sysvar (0, 6, 0, 0, &hinc, &vinc);
		r->g_x -= hinc;
		r->g_y -= vinc;
		r->g_w += 2 * hinc;
		r->g_h += 2 * vinc;
	}
}

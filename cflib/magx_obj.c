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

#include <ctype.h>
#include <stddef.h>

#include "intern.h"
#include "magx.h"


short
get_magx_obj (OBJECT *tree, short obj)
{
	unsigned short typ, state, flags, us;
	short ret;

	flags = tree[obj].ob_flags;
	state = tree[obj].ob_state & 0x00ff;
	us = (tree[obj].ob_state & 0xff00) >> 8;

	typ = tree[obj].ob_type & 0x00ff;
	if (typ == G_USERDEF)
		typ = (tree[obj].ob_type & 0xff00) >> 8;

	if (state & OS_WHITEBAK)
	{
		ret = MX_UNKNOWN;
		switch (typ)
		{
			case G_STRING:
				if (us == 0xff)	/* komplett unterstrichen */
					ret = MX_UNDERLINE;
				else if ((us & 0xf0) == 0)	/* String mit Shortcut */
					ret = MX_SCSTRING;
				break;

			case G_BUTTON:
				if (us == 0xfe)	/* Gruppenrahmen */
				{
					if (state & OS_CHECKED)
						ret = MX_GROUPBOX2;	/* - kleine Schrift */
					else
						ret = MX_GROUPBOX;	/* - normal */
				}
				else if (us & 0x80)	/* bit15 -> MagiC-Knopf */
				{
					if (flags & OF_RBUTTON)	/* Radio */
					{
						if (us == 0xff)
							ret = MX_RADIO;	/* ohne */
						else
							ret = MX_SCRADIO;	/* mit Shortcut */
					}
					else	/* Kreuz */
					{
						if (us == 0xff)
							ret = MX_CHECK;	/* ohne */
						else
							ret = MX_SCCHECK;	/* mit ShortCut */
					}
				}
				else if (flags & OF_EXIT)	/* Exit-Knopf */
					ret = MX_SCEXIT;
				break;
		}
	}
	else if ((typ == G_FTEXT) && (flags & OF_FL3DBAK) &&
		 (tree[obj].ob_spec.tedinfo->te_thickness == -2))
		ret = MX_EDIT3D;
	else
		ret = MX_NOTXOBJ;
	
	return ret;
}

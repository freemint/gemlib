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


void
cf_objc_edit (OBJECT * tree, int obj, int kreturn, int *idx, int mode,
	      int kstate, int *ctrl)
{
	if (!(tree[obj].ob_flags & EDITABLE))
		return;

	if (mode == ED_CHAR)
	{
		int scan, i;
		long l;
		TEDINFO *ted;
		char *ptext;
		char buf[80];

		*ctrl = FALSE;

		ted = (TEDINFO *) get_obspec (tree, obj);
		ptext = ted->te_ptext;

		scan = (kreturn & 0xff00) >> 8;
		if (kstate & K_CTRL)
		{
			switch (scan)
			{
				case 0x2D:	/* ^X -> Cut */
					scrap_wtxt (ptext);
					objc_edit (tree, obj, 0x11B, idx, ED_CHAR);	/* ESC: l”schen */
					*ctrl = TRUE;
					break;

				case 0x2E:	/* ^C -> Copy */
					scrap_wtxt (ptext);
					*ctrl = TRUE;
					break;

				case 0x2F:	/* ^V -> Paste */
					objc_edit (tree, obj, 0x11B, idx, ED_CHAR);	/* ESC: l”schen */
					scrap_rtxt (buf, &l, 80);
					for (i = 0;
					     i < min (l, ted->te_txtlen - 1);
					     i++)
						objc_edit (tree, obj, buf[i],
							   idx, ED_CHAR);
					*ctrl = TRUE;
					break;
			}
		}
		else
		{
			switch (scan)
			{
				case 0x52:	/* INS -> ASCII-Tabelle */
					/* i = ascii_table(1, 13); */
					i = ascii_table (sys_big_id,
							     sys_big_pts);
					if (i > 0)
						kreturn = i & 0xff;
					break;
			}
		}
	}
	if (!(kstate & K_CTRL))	/* keine Ctrl-Codes durchlassen */
		objc_edit (tree, obj, kreturn, idx, mode);
}

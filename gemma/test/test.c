/* The gemma library test program (for multidialog support)
 */

/*  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

# include <string.h>
# include "../include/mint/slb.h"
# include "../include/gemma/gemma.h"

# include "test.h"

# ifndef ulong
#  define ulong unsigned long
# endif
# ifndef ushort
#  define ushort unsigned short
# endif
# ifndef uchar
#  define uchar unsigned char
# endif

static void
deselect(WINDIAL *wd, short obj)
{
	OBJECT *ob = wd->wb_treeptr;

	if ((!(ob[obj].ob_state & OS_WHITEBAK) && !(ob[obj].ob_flags & OF_RBUTTON)))
		objc_xchange(wd, obj, ob[obj].ob_state & ~OS_SELECTED, 1);
}

long
newkey(WINDIAL *wd, short vec, short ks, short kc)
{
	if ((kc & 0x007f) == 0x0011)
		windial_longjmp(wd, vec);
	return 0;
}

long
newmsg(WINDIAL *wd, short vec, short *msg)
{
	if (msg[0] == AP_TERM)
		windial_longjmp(wd, vec);

	return 0;
}

static void
do_windows()
{
	WINDIAL *win_1, *win_2, *current;
	OBJECT *ob;

	/* Create both windows */
	win_1 = (WINDIAL *)windial_create(0, WINDOW1, 0, 0, (char *)WTITLE1);
	win_2 = (WINDIAL *)windial_create(0, WINDOW2, 0, 0, (char *)WTITLE2);

	current = win_1;
	ob = win_1->wb_treeptr;

	/* Link them to one list */
	windial_link(win_1, win_2);

	/* Open the first one */
	windial_open(win_1);

	if (windial_setjmp(win_1, WD_MSGVEC, newmsg))
		goto exit;
	if (windial_setjmp(win_1, WD_KEYVEC, newkey))
		goto exit;
	if (windial_setjmp(win_2, WD_MSGVEC, newmsg))
		goto exit;
	if (windial_setjmp(win_2, WD_KEYVEC, newkey))
		goto exit;

	for (;;)
	{
		ulong m;
		ushort tree, obj;

		m = windial_formdo(current);

		tree = (ushort)(m >> 16);
		obj = (ushort)(m & 0x0000ffffL);

		if (tree == WINDOW1)
			current = win_1;
		else
			current = win_2;

		if (obj == 0xffff)
		{
			windial_close(current);
			continue;
		}
		else
		{
			obj &= 0x7fff;
			deselect(current, obj);
		}

		if (tree == WINDOW1)
		{
			switch (obj)
			{
				case	OPENBLUE:
				{
					objc_xchange(win_1, OPENBLUE, ob[OPENBLUE].ob_state | OS_DISABLED, 1);
					windial_open(win_2);
					break;
				}
				case	CLOSEGREY:
				{
					windial_close(win_1);
					break;
				}
			}
		}
		else
		{
			switch (obj)
			{
				case	CLOSEBLUE:
				{
					objc_xchange(win_1, OPENBLUE, ob[OPENBLUE].ob_state & ~OS_DISABLED, 1);
					windial_close(win_2);
					break;
				}
				case	MAKEALERT:
				{
					windial_alert(1, ALERT1);
					break;
				}
			}
		}
	}
exit:
	windial_close(win_1);
	windial_close(win_2);
	windial_delete(win_1);
	windial_delete(win_2);

	return;
}

int
main(void)
{
	long r;

	r = appl_open("test.rsc", 0, (char *)PNAME);
	if (r < 0)
		return r;

# if 0
	(gemma.exec)(gemma.handle, 34L, 2, 0, 1);	/* enable debug support */
	(gemma.exec)(gemma.handle, 34L, 2, 0, 0);	/* disable debug support */
# endif

	do_windows();

	return appl_close();
}

/* EOF */

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
make_shortpath (char *path, char *shortpath, int maxlen)
{
	char help[256];
	int path_len;
	char *p1, *p2;

	strcpy (help, path);
	path_len = (int) strlen (help);
	if (maxlen < 18)
		split_filename (path, NULL, help);
	else if (path_len > maxlen)
	{
		p1 = strchr (help, '\\');
		p2 = p1;
		path_len += 2;	/* zwei Punkte neu */
		while (*p2 != '\0' && path_len > maxlen)
		{
			p2++;
			while (*p2 != '\\' && *p2 != '\0')
			{
				p2++;
				path_len--;
			}
		}
		if (*p2 != '\0')
		{
			memmove (p1 + 3, p2, strlen (p2) + 1);
			p1[1] = '.';
			p1[2] = '.';
		}
		else
		{
			p2 = strrchr (help, '\\');
			memmove (help, p2, strlen (p2) + 1);
		}
	}
	strcpy (shortpath, help);
}

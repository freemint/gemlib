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

#ifdef __MINT__
#include <sys/stat.h>
#else
#include <ext.h>
#define S_IFMT		0170000
#define S_IFDIR		0040000
#define S_ISDIR(m)	((m & S_IFMT) == S_IFDIR)
#endif

#include <ctype.h>
#include "intern.h"


int
path_exists (char *pathname)
{
	struct stat s;
	int r = FALSE;

	if (pathname[0] != '\0')
	{
		if ((stat (pathname, &s) == 0) && S_ISDIR (s.st_mode))
			r = TRUE;

		/* Work-around fÅr MagiCPC, wo der stat(<Laufwerk>) nicht funkt! */
		if (cf_magxPC && !r)
		{
			int len = (int) strlen (pathname);

			if (pathname[1] == ':' && len <= 3)	/* nur Laufwerk 'X:' oder 'X:\' */
			{
				char p[80];

				/* Laufwerk existiert, wenn man das akt. Verzeichnis ermitteln kann */
				if (Dgetpath (p, toupper (pathname[0]) - 64)
				    == 0)
					r = TRUE;
			}
		}
	}
	return r;
}

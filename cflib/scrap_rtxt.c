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
 * GEM clipbrd
 */

#ifdef __MINT__
  #include <osbind.h>
#else
  #include <tos.h>
#endif
#include "intern.h"


char *
scrap_rtxt (char *buf, long *len, long maxlen)
{
	char path[80];
	int datei;

	if (get_scrapdir (path))
	{
		strcat (path, "scrap.txt");
		if ((datei = (int) Fopen (path, 0)) >= 0)
		{
			*len = Fread (datei, maxlen, buf);
			Fclose (datei);
			buf[*len] = '\0';
			return buf;
		}
	}
	return NULL;
}

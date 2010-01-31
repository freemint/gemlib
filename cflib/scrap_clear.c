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


void
scrap_clear (void)
{
	char scrap[80], path[80];
	DTA dta, *old_dta;
	int ok;

	if (get_scrapdir (scrap))
	{
		strcpy (path, scrap);
		strcat (path, "scrap.*");
		old_dta = (DTA *) Fgetdta ();
		Fsetdta (&dta);

		ok = (Fsfirst (path, 0) == 0);
		while (ok)
		{
			strcpy (path, scrap);
#ifdef __MINT__
			strcat (path, dta.dta_name);
#else
			strcat (path, dta.d_fname);
#endif
			Fdelete (path);
			ok = (Fsnext () == 0);
		}
		Fsetdta (old_dta);
	}
}

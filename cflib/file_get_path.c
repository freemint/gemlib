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

#include <osbind.h>

#include <ctype.h>
#include "intern.h"


int
get_path (char *path, char drive)
{
	int ret, drive_nr;

	if (drive == 0)
	{
		drive = 'A' + Dgetdrv ();	/* Aktuelles Laufwerk */
		if (drive > 'Z')
			drive = drive - 'Z' + '0';
	}
	else
		drive = toupper (drive);
	if (drive >= '1' && drive <= '6')	/* Laufwerk nach Z mit Big-DOS oder MetaDOS > 2.60 */
		drive_nr = drive - '1' + 26;
	else
		drive_nr = drive - 'A';
	path[0] = drive;
	path[1] = ':';
	ret = Dgetpath (path + 2, drive_nr + 1);
	strcat (path, "\\");

	if (fs_case_sens (path) == NO_CASE)
		str_toupper (path);

	return (ret == 0);
}

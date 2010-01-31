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
  #include <osbind.h>
#else
  #include <tos.h>
#endif

#include <ctype.h>
#include "intern.h"


int
make_normalpath (char *path)
{
	int i;
	char p[256];
	char *f, drv;
	int ret;

	if (path[0] == '\0')
		return FALSE;

#ifdef __MINT__
	if (path[0] == '/')	/* UNIX-Pfad */
	{
		unx2dos (path, p);
		strcpy (path, p);
	}
#endif

	/* Laufwerk bestimmen */
	if (path[1] != ':')	/* Kein Laufwerk */
	{
		drv = 'A' + Dgetdrv ();	/* aktuelles Laufwerk */
		if (drv > 'Z')
			drv = drv - 'Z' + '0';	/* A..Z 1..6 */
		f = path;
	}
	else
	{
		path[0] = toupper (path[0]);
		drv = path[0];
		if (drv > 'Z')
			drv = drv - 'Z' + '0';	/* A..Z 1..6 */
		f = path + 2;
	}
	/* Pfad mit Laufwerk bestimmen */
	if (f[0] == '.' && (f[1] == '\\' || f[1] == '\0'))
	{
		get_path (p, drv);	/* aktuellen Pfad nehmen */
		if (f[1] == '\\')
			strcat (p, f + 2);
	}
	else if (f[0] != '\\')	/* Keine Root */
	{
		get_path (p, drv);
		strcat (p, f);
	}
	else
	{
		p[0] = drv;
		p[1] = ':';
		p[2] = '\0';
		strcat (p, f);
	}

	i = (int) strlen (p);
	if (p[i - 1] != '\\')
	{
		p[i] = '\\';
		p[i + 1] = '\0';
	}

	ret = path_exists (p);
	if (!ret)
		p[i] = '\0';

	strcpy (path, p);
	return ret;
}

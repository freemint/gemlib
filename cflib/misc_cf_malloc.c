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


void *
cf_malloc (long size, char *who, int global)
{
	void *r = NULL;

	if (global &&getcookie ("MiNT", NULL))
		r = (void *) Mxalloc (size, 0x23);
	else
		r = (void *) Malloc (size);

	if (r == NULL)
	{
		char msg[80];

		if (gl_gem > 0)
		{
			sprintf (msg,
				 "[3][CF-Lib (%s)|Can't allocate RAM!][Ignore|Exit]",
				 who);
			if (form_alert (2, msg) == 2)
			{
				appl_exit ();
				exit (-39);
			}
		}
		else
		{
			fprintf (stderr, "CF-Lib (%s)\nCan't allocate RAM!\n",
				 who);
			exit (-39);
		}
	}
	return r;
}

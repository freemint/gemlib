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


#ifdef __MINT__

#include <mint/cookie.h>

int
getcookie (char *cookie, long *p_value)
{
	long v;
	int i;
	union
	{
		long as_long;
		char as_char[4];
	}
	cast;

	/* genialer Cast, oder? :-)) */
	cast.as_char[0] = cookie[0];
	cast.as_char[1] = cookie[1];
	cast.as_char[2] = cookie[2];
	cast.as_char[3] = cookie[3];

	i = Getcookie (cast.as_long, &v);
	if (p_value)
		*p_value = v;

	return (i == C_FOUND);
}

#else

#include <tos.h>

static long *my_cookiejar = NULL;

static long
get_cookie_adr (void)
{
	my_cookiejar = *((long **) 0x5A0L);
	return 0L;
}

int
getcookie (char *cookie, long *p_value)
{
	long *cookiejar, c;
	int i;
	union
	{
		long as_long;
		char as_char[3];
	}
	cast;

	if (my_cookiejar == NULL)
		Supexec (get_cookie_adr);

	cookiejar = my_cookiejar;

	if (!cookiejar || !cookiejar[0])
		return FALSE;

	/* Ein einfacherer Cast fiel mir nicht ein :-)) */
	for (i = 0; i < 4; i++)
		cast.as_char[i] = cookie[i];
	c = cast.as_long;

	do
	{
		if (cookiejar[0] == c)
		{
			if (p_value)
				*p_value = cookiejar[1];
			return TRUE;
		}
		else
			cookiejar = &(cookiejar[2]);
	}
	while (cookiejar[0] || !cookie);

	if (p_value)
		*p_value = 0;

	return FALSE;
}

#endif

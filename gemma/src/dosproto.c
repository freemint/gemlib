/* GEMDOS function gateway
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

# include <errno.h>
# include <string.h>
# include <mintbind.h>

# include "gemma.h"
# include "dosproto.h"

/* BIOS function calls
 */

short
_kbshift(long wh)
{
	return (short)Kbshift(wh);
}

/* These below are only used in appl_getinfo() emulation code
 */

# ifdef _EMULATE_APPL_GETINFO

long
_getexc(long vec)
{
	return (long)Setexc(vec >> 2, (void *)-1L);
}

/* XBIOS function calls
 */

short
_getrez(void)
{
	short r = Getrez();

	if ((r < 0) || (r == 4))
		return 2;

	return r;
}

# endif

/* GEMDOS function calls
 */

void
_conws(char *string)
{
	short x = 0;

	while(string[x])
	{
		if (string[x] == '\n')
			Cconws("\r\n");
		else
			Cconout(string[x]);
		x++;
	}
}

static void
u2d(const char *in, char *out)
{
	if ((in[1] != ':') && ((in[0] == '\\') || (in[0] == '/')))
	{
		strcpy(out, "u:");
		strcat(out, in);
	}
	else
		strcpy(out, in);
}

static long
__alloc(long size, short mode)
{
	long r;

	sema_request(sema_fork);
	r = (long)Mxalloc(size, mode);
	if (r < 0)
		r = (long)Malloc(size);	/* No Mxalloc()? Incredible... */
	sema_release(sema_fork);
	if (!r)
		r = -ENOMEM;
	return r;
}

long
_alloc(long size)	/* alloc `size' bytes of private memory */
{
	return __alloc(size, 0x0013);
}

long
_rdalloc(long size)	/* alloc `size' bytes of globally readable memory */
{
	return __alloc(size, 0x0043);
}

long
_getdrv(void)
{
	return Dgetdrv();
}

long
_setpath(const char *p)
{
	char temp[1024];

	u2d(p, temp);
	return Dsetpath(temp);
}

long
_getcwd(void *p, short drv, short len)
{
	long r;

	r = Dgetcwd(p, drv, len);
	if (r < 0)
		r = Dgetpath(p, drv);

	return r;
}

long
_semaphore(short mode, long sema, long time)
{
	return Psemaphore(mode, sema, time);
}

long
_sgeteuid(void)
{
# ifdef _HAVE_MINT_GEMDOS
	return Pgeteuid();
# else
	return 0;
# endif
}

/* EOF */

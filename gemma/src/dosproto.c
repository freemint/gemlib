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
# include <mint/ostruct.h>
# include <sys/stat.h>

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

# ifndef _HAVE_APPL_GETINFO

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

long
_cntl(short file, void *arg, short cmd)
{
	return Fcntl(file, arg, cmd);
}

long
_stat(short flag, const char *name, void *out)
{
	char temp[1024];

	u2d(name, temp);
	return Fxattr(flag, temp, out);
}

long
_delete(char *fspec)
{
	return Fdelete(fspec);
}

static long
__alloc(long size, short mode)
{
	long r;

	sema_request(sema_fork);
	r = Mxalloc(size, mode);
	if (r < 0)
		r = Malloc(size);	/* No Mxalloc()? Incredible... */
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

void
_shrink(void *base, long newsize)
{
	(void)Mshrink(base, newsize);
}

void
_free(long adr)
{
	(void)Mfree(adr);
}

long
_getdrv(void)
{
	return Dgetdrv();
}

long
_setdrv(long drv)
{
	return Dsetdrv(drv);
}

long
_dfree(long *mem, short drv)
{
	return Dfree(mem, drv);
}

long
_getpath(void *p, short drv)
{
	return Dgetpath(p, drv);
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
	return Dgetcwd(p, drv, len);
}

short
_dup(short file)
{
	return Fdup(file);
}

void
_force(short f1, short f2)
{
	(void)Fforce(f1, f2);
}

long
_semaphore(short mode, long sema, long time)
{
	return Psemaphore(mode, sema, time);
}

long
_kill(long pid, long sig)
{
# ifdef _HAVE_MINT_GEMDOS
	return Pkill((short)pid, (short)sig);
# else
	if ((pid == 0) || (pid == 1))
		return 0;
	else
		return -33;
# endif
}

long
_sgetppid(void)
{
# ifdef _HAVE_MINT_GEMDOS
	return Pgetppid();
# else
	return 0;		/* fake parent pid 0 */
# endif
}

long
_sgetpid(void)
{
# ifdef _HAVE_MINT_GEMDOS
	return Pgetpid();
# else
	return 1;		/* fake own pid 1 */
# endif
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

long
_wait3(short flag, long *rus)
{
	return Pwait3(flag, rus);
}

long
_signal(short sig, void *hnd)
{
	return Psignal(sig, hnd);
}

/* EOF */

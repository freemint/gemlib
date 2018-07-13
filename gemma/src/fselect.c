/* File selector functions */

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

# include "gemma.h"
# include "dosproto.h"
# include "gemproto.h"
# include "appl.h"
# include "fselect.h"

static void
fsel_init(PROC_ARRAY *proc, ushort flag)
{
	const char *home;
	long r;
	short x;

	home = dos_getenv(proc, "HOME=");

	if ((flag & 1) || !home)
	{
		short drv = _getdrv();
		char *p = proc->fsel_path;

		drv += 'A';
		*p++ = (char)drv;
		*p++ = ':';

		r = _getcwd(p, 0, sizeof(proc->fsel_path) - 2);
		if (r < 0)
		{
			*p++ = '\\';
			*p++ = 0;
		}
	} else
		strcpy(proc->fsel_path, home);

	r = strlen(proc->fsel_path);

	for (x = 0; x < r; x++)
	{
		if (proc->fsel_path[x] == '/')
			proc->fsel_path[x] = '\\';
	}

	if (proc->fsel_path[r - 1] != '\\')
		strcat(proc->fsel_path, "\\");

	proc->fsel_file[0] = 0;

	DEBUGMSG("path is:");
	DEBUGMSG(proc->fsel_path);

	proc->fsel_init_done = 1;
}

long
file_select(BASEPAGE *bp, long fn, short nargs, const char *title, const char *mask, ushort flag, PROC_ARRAY *p)
{
	PROC_ARRAY *proc = 0;
	char *tit, *msk = 0;
	long r;

	if (nargs < 3) return -EINVAL;
	if (nargs >= 4) proc = p;
	if ((nargs < 4) || !proc) proc = get_contrl(bp);

	if (!proc->gem.global[0])
		return -EACCES;

	DEBUGMSG("enter");

	if (!proc->fsel_init_done || flag&0x8000)
		fsel_init(proc, flag);

	if ((long)mask >= 0)
		msk = (char *)obj2addr(proc, R_STRING, (ulong)mask);
	if ((long)msk <= 0)
		msk = "*.*";
	strcat(proc->fsel_path, msk);

	tit = (char *)obj2addr(proc, R_STRING, (ulong)title);
	if ((long)tit <= 0)
		return -EBADARG;

	DEBUGMSG("calling fsel_exinput() with:");
	DEBUGMSG(proc->fsel_path);
	DEBUGMSG(proc->fsel_file);
	DEBUGMSG(tit);

	r = _fsel_exinput(proc, proc->fsel_path, proc->fsel_file, tit);

	appl_top(bp, AP_TOP, 0, proc);

	if (r)
	{
		strcpy(proc->fsel_outname, proc->fsel_path);
		tit = strrchr(proc->fsel_outname, '\\');
		if (tit)
			tit[1] = 0;
		strcat(proc->fsel_outname, proc->fsel_file);

		DEBUGMSG("OK, returning:");
		DEBUGMSG(proc->fsel_outname);

		return (long)proc->fsel_outname;
	}

	DEBUGMSG("Cancel, returning NULL");

	return 0;
}

/* EOF */

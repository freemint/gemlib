/* Resource file related functions
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
# include <fcntl.h>
# include <string.h>

# include "dosproto.h"
# include "gemma.h"
# include "gemproto.h"
# include "user.h"

/* BUG: does not recognize the xrsrc extension of Interface
 */

long
rsrc_xload(BASEPAGE *bp, long fn, short nargs, char *name, PROC_ARRAY *p)
{
	PROC_ARRAY *proc = 0;
	long r, len, file;
	short ap[4];

	if (nargs < 1) return -EINVAL;
	if (nargs >= 2) proc = p;
	if ((nargs < 2) || !proc) proc = get_contrl(bp);

	if (!proc->gem.global[0])
		return -EACCES;

	DEBUGMSG("enter");
	DEBUGMSG(name);

	len = _size(name);
	if (len < 0)
		return len;
	if (!len)
		return -EFTYPE;

	DEBUGMSG("size OK");

	/* Set size here, so that it is valid even after
	 * rsrc_load() below. Fixes the problems with XaAES.
	 */
	proc->rsclength = LROUND(len);

	_appl_getinfo(proc, AES_PROCESS, ap);
	if (ap[3])
	{
		ushort *wrsc;
		ulong *lrsc;

		DEBUGMSG("custom load");

		r = _alloc(proc->rsclength);
		if (r <= 0)
			goto fault;
		wrsc = (ushort *)proc->rawrscaddr = (char *)r;

		DEBUGMSG("open()");

		r = file = _open(name, O_RDONLY|O_DENYW);
		if (file < 0)
			r = file = _open(name, O_RDONLY);
		if (file < 0)
			goto error;

		DEBUGMSG("read()");

		r = _read(file, len, wrsc);
		_close(file);

		DEBUGMSG("loaded OK");

		if ((wrsc[0] & ~1) == 0)
		{
			DEBUGMSG("standard RSC file");
			if (wrsc[17] != len)
			{
				r = -EFTYPE;
				goto error;
			}
			DEBUGMSG("format accepted");
		}
		else
		{
			char *tmp;

			DEBUGMSG("non-standard RSC file");
			_appl_getinfo(proc, AES_SYSTEM, ap);
			if (!ap[3] || !(wrsc[0] & 4))
			{
				DEBUGMSG("format rejected");
				r = -EFTYPE;
				goto error;
			}
			DEBUGMSG("extended RSC file");

			tmp = (char *)wrsc;
			tmp += wrsc[17];
			lrsc = (ulong *)tmp;

			if (lrsc[0] != len)
			{
				DEBUGMSG("long offset mismatch");
				r = -EFTYPE;
				goto error;
			}
		}

		DEBUGMSG("complete");

		return 0;
	}

	DEBUGMSG("TOS method");

	if (!_rsrc_load(proc, name))
	{
		r = -ENOENT;
		goto fault;
	}

	/* Record the filename pointer for later */
	proc->rscname = name;

	DEBUGMSG("loaded OK");

	return 0;

error:	_free((long)proc->rawrscaddr);
	proc->rawrscaddr = 0;

	DEBUGMSG("exit on error");

fault:	proc->rsclength = 0;

	DEBUGMSG("exit on fault");

	return r;
}

long
rsrc_xalloc(BASEPAGE *bp, long fn, short nargs, PROC_ARRAY *p)
{
	PROC_ARRAY *proc = 0;
	short ap[4], free = 0;
	long ppid, r;

	if (nargs >= 1) proc = p;
	if ((nargs < 1) || !proc) proc = get_contrl(bp);

	if (!proc->gem.global[0])
		return -EACCES;

	DEBUGMSG("enter");

	if (!proc->rsclength)
	{
		PROC_ARRAY *pproc;

		ppid = _sgetppid();
		if (ppid < 0)
			return -EACCES;
		pproc = pidtable[ppid];
		if (!pproc)
			return -EACCES;
		if (!pproc->rsclength)
			return -EACCES;
		proc->rsclength = pproc->rsclength;
		proc->rscname = pproc->rscname;
		if (pproc->rscname)
		{
			/* If we get here, we are a thread, our parent
			 * loaded an RSC, and the AES does not support
			 * rsrc_rcfix(). So...
			 */
			if (!_rsrc_load(proc, pproc->rscname))
				return -ENOENT;
			return 0;
		}
		proc->rawrscaddr = pproc->rawrscaddr;
		free = 1;
	}

	/* Pretend success on systems without rsrc_rcfix()
	 */
	_appl_getinfo(proc, AES_PROCESS, ap);
	if (!ap[3])
		return 0;

	r = _alloc(proc->rsclength);
	if (r <= 0)
		goto fault;

	proc->rscaddr = (char *)r;
	memcpy(proc->rscaddr, proc->rawrscaddr, proc->rsclength);

	_rsrc_rcfix(proc, proc->rscaddr);

	if (free)
		proc->rawrscaddr = 0;

	DEBUGMSG("complete");

	return 0;

fault:	if (free)
	{
		proc->rawrscaddr = 0;
		proc->rsclength = 0;
	}
	if (!r)
		r = -EINTERNAL;

	DEBUGMSG("exit on error");

	return r;
}

long
rsrc_xfree(BASEPAGE *bp, long fn, short nargs, PROC_ARRAY *p)
{
	PROC_ARRAY *proc = 0;

	if (nargs >= 1) proc = p;
	if ((nargs < 1) || !proc) proc = get_contrl(bp);

	if (!proc->gem.global[0])
		return -EACCES;
	if (!proc->rsclength)
		return -EACCES;

	_rsrc_free(proc);

	if (proc->rscaddr)
	{
		_free((long)proc->rscaddr);
		proc->rscaddr = 0;
	}
	if (proc->rawrscaddr)
	{
		_free((long)proc->rawrscaddr);
		proc->rawrscaddr = 0;
	}
	proc->rsclength = 0;

	return 0;
}

long
rsrc_xgaddr(BASEPAGE *bp, long fn, short nargs, \
		short type, short obj, PROC_ARRAY *p)
{
	PROC_ARRAY *proc = 0;

	if (nargs < 2) return -EINVAL;
	if (nargs >= 3) proc = p;
	if ((nargs < 3) || !proc) proc = get_contrl(bp);

	if (!proc->gem.global[0])
		return -EACCES;
	if (!proc->rsclength)
		return -EACCES;

	DEBUGMSG("enter");

	proc->gem.int_in[0] = type;
	proc->gem.int_in[1] = obj;

	if (!call_aes(bp, 1L, 2, proc, 112))
		return -EFAULT;

	DEBUGMSG("complete");

	return proc->gem.addr_out[0];
}

/* EOF */

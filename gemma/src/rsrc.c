/* Resource file related functions
 */

# include <fcntl.h>
# include <string.h>
# include <sys/stat.h>
# include <mint/dcntl.h>
# include <mint/mintbind.h>
# include <errno.h>

# include "gemma.h"
# include "gemproto.h"
# include "user.h"
# include "xattr.h"

extern PROC_ARRAY *pidtable[];

static inline long
getsize(char *name)
{
	typedef struct _dta DTABUF;
	DTABUF dta, *olddta;
	struct xattr xa;
	struct stat st;
	long r;

	DEBUGMSG("Fstat64()\n");

	r = Fstat64(0, name, &st);	/* MiNT 1.15 has real stat() */
	if (r == 0)
		return st.st_size;

	DEBUGMSG("Fxattr()\n");

	r = Fxattr(0, name, &xa);	/* 32-bit stat() from older MiNTs */
	if (r == 0)
		return xa.size;

	DEBUGMSG("Fsfirst()\n");

	olddta = (DTABUF *)Fgetdta();	/* TOS? ups... */
	Fsetdta(&dta);
	r = Fsfirst(name, 0);
	Fsetdta(olddta);
	if (r == 0)
		return dta.dta_size;

	return r;
}

/* BUG: does not recognize the xrsrc extension of Interface
 */

long
rsrc_xload(BASEPAGE *bp, long fn, short nargs, char *name, PROC_ARRAY *p)
{
	PROC_ARRAY *proc = 0;
	long r, len, file;
	short ap[4];

	DEBUGMSG("rsrc_xload(): begin, filename: ");
	DEBUGMSG(name);
	DEBUGMSG("\n");

	if (nargs < 1) return -EINVAL;
	if (nargs >= 2) proc = p;
	if ((nargs < 2) || ((long)proc == 0)) proc = get_contrl(bp);

	if (!proc->gem.global[0])
		return -EACCES;

	DEBUGMSG("rsrc_xload(): enter\n");

	len = getsize(name);
	if (len < 0)
		return len;
	if (!len)
		return -EFTYPE;

	DEBUGMSG("rsrc_xload(): size OK\n");

	/* Set size here, so that it is valid even after
	 * rsrc_load() below. Fixes the problems with XaAES.
	 */
	proc->rsclength = LROUND(len);

	if (aes40(proc))
	{
		_appl_getinfo(proc, AES_PROCESS, ap);
		if (ap[3])
		{
			ushort *wrsc;
			ulong *lrsc;

			DEBUGMSG("rsrc_xload(): custom load\n");

			r = _malloc(proc->rsclength);
			if (r <= 0)
				goto fault;
			lrsc = (ulong *)wrsc = \
				(ushort *)proc->rawrscaddr = (char *)r;
			r = file = Fopen(name, O_RDONLY|O_DENYW);
			if (file < 0)
				r = file = Fopen(name, O_RDONLY);
			if (file < 0)
				goto error;
			r = Fread(file, len, wrsc);
			(void)Fclose(file);

			if ((wrsc[0] & ~1) == 0)
			{
				if (wrsc[17] != len)
				{
					r = -EFTYPE;
					goto error;
				}
			}
			else
			{
				_appl_getinfo(proc, AES_SYSTEM, ap);
				if (!ap[3] || !(wrsc[0] & 4))
				{
					r = -EFTYPE;
					goto error;
				}
				if (lrsc[wrsc[17]] != len)
				{
					r = -EFTYPE;
					goto error;
				}
			}

			DEBUGMSG("rsrc_xload() complete\n");

			return 0;
		}
	}

	DEBUGMSG("rsrc_xload(): TOS method\n");

	if (!_rsrc_load(proc, name))
	{
		r = -ENOENT;
		goto fault;
	}

	/* Record the filename pointer for later */
	proc->rscname = name;

	DEBUGMSG("rsrc_xload(): loaded OK\n");

	return 0;

error:	_mfree((long)proc->rawrscaddr);
	proc->rawrscaddr = 0;

	DEBUGMSG("rsrc_xload(): exit on error\n");

fault:	proc->rsclength = 0;

	DEBUGMSG("rsrc_xload(): exit on fault\n");

	return r;
}

long
rsrc_xalloc(BASEPAGE *bp, long fn, short nargs, PROC_ARRAY *p)
{
	PROC_ARRAY *proc = 0;
	short ap[4], free = 0;
	long ppid, r;

	DEBUGMSG("rsrc_xalloc: begin\n");

	if (nargs >= 1) proc = p;
	if ((nargs < 1) || ((long)proc == 0)) proc = get_contrl(bp);

	if (!proc->gem.global[0])
		return -EACCES;

	if (!proc->rsclength)
	{
		PROC_ARRAY *pproc;

		ppid = Pgetppid();
		if (ppid < 0)
			return -EACCES;
		pproc = pidtable[ppid];
		if (!pproc)
			return -EACCES;
		if (!pproc->rsclength)
			return -EACCES;
		proc->rsclength = pproc->rsclength;
		proc->rscname = pproc->rscname;
		if ((long)pproc->rscname)
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
	if (!aes40(proc))
		return 0;
	_appl_getinfo(proc, AES_PROCESS, ap);
	if (!ap[3])
		return 0;

	r = _malloc(proc->rsclength);
	if (r <= 0)
		goto fault;

	proc->rscaddr = (char *)r;
	memcpy(proc->rscaddr, proc->rawrscaddr, proc->rsclength);

	_rsrc_rcfix(proc, proc->rscaddr);

	if (free)
		proc->rawrscaddr = 0;

	DEBUGMSG("rsrc_xalloc: complete\n");

	return 0;

fault:	if (free)
	{
		proc->rawrscaddr = 0;
		proc->rsclength = 0;
	}
	if (!r)
		r = -EINTERNAL;

	DEBUGMSG("rsrc_xalloc: exit on error\n");

	return r;
}

long
rsrc_xfree(BASEPAGE *bp, long fn, short nargs, PROC_ARRAY *p)
{
	PROC_ARRAY *proc = 0;

	if (nargs >= 1) proc = p;
	if ((nargs < 1) || ((long)proc == 0)) proc = get_contrl(bp);

	if (!proc->gem.global[0])
		return -EACCES;
	if (!proc->rsclength)
		return -EACCES;

	_rsrc_free(proc);

	if ((long)proc->rscaddr)
	{
		_mfree((long)proc->rscaddr);
		proc->rscaddr = 0;
	}
	if ((long)proc->rawrscaddr)
	{
		_mfree((long)proc->rawrscaddr);
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

	DEBUGMSG("rsrc_xgaddr(): begin\n");

	if (nargs < 2) return -EINVAL;
	if (nargs >= 3) proc = p;
	if ((nargs < 3) || ((long)proc == 0)) proc = get_contrl(bp);

	if (!proc->gem.global[0])
		return -EACCES;
	if (!proc->rsclength)
		return -EACCES;

	DEBUGMSG("rsrc_xgaddr(): enter\n");

	proc->gem.int_in[0] = type;
	proc->gem.int_in[1] = obj;

	if (!_aes(proc, 112))
		return -EFAULT;

	DEBUGMSG("rsrc_xgaddr(): complete\n");

	return proc->gem.addr_out[0];
}

/* EOF */

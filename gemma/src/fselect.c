/* File selector functions */

# include <mintbind.h>
# include <errno.h>
# include <string.h>

# include "gemma.h"
# include "gemproto.h"
# include "user.h"

static inline void
fsel_init(PROC_ARRAY *proc, unsigned short flag)
{
	char *home;
	long r;
	short x;

	home = getenv(proc->base, "HOME=");

	if ((flag & 1) || !(long)home)
	{
		short drv = Dgetdrv();
		char *p = proc->fsel_path;

		drv += 'A';
		*p++ = (char)drv;
		*p++ = ':';

		r = Dgetcwd(p, 0, sizeof(proc->fsel_path) - 2);
		if (r < 0)
			r = Dgetpath(p, 0);
		if (r < 0) {
			*p++ = '\\';
			*p++ = 0;
		}
	} else
		strcpy(proc->fsel_path, home);

	r = strlen(proc->fsel_path);

	for (x = 0; x < r; x++) {
		if (proc->fsel_path[x] == '/')
			proc->fsel_path[x] = '\\';
	}

	if (proc->fsel_path[r - 1] != '\\')
		strcat(proc->fsel_path, "\\");

	proc->fsel_file[0] = 0;

	DEBUGMSG("fsel_init: path is ");
	DEBUGMSG(proc->fsel_path);
	DEBUGMSG("\n");

	proc->fsel_init_done = 1;
}

long
file_select(BASEPAGE *bp, long fn, short nargs, \
		char *title, char *mask, unsigned short flag, PROC_ARRAY *p)
{
	PROC_ARRAY *proc = 0;
	char *tit, *msk = 0;
	long r;

	DEBUGMSG("file_select: begin\n");

	if (nargs < 3) return -EINVAL;
	if (nargs >= 4) proc = p;
	if (nargs < 4 || !(long)proc) proc = get_contrl(bp);

	if (!proc->gem.global[0])
		return -EACCES;

	if (!proc->fsel_init_done || flag&0x8000)
		fsel_init(proc, flag);

	if ((long)mask >= 0)
		msk = (char *)obj2addr(proc, R_STRING, (unsigned long)mask);
	if ((long)msk <= 0)
		msk = "*.*";
	strcat(proc->fsel_path, msk);

	tit = (char *)obj2addr(proc, R_STRING, (unsigned long)title);
	if ((long)tit <= 0)
		return -EBADARG;
	TOUCH(tit);

	DEBUGMSG("fsel_init: calling fsel_exinput() with:\n");
	DEBUGMSG(proc->fsel_path);
	DEBUGMSG("\n");
	DEBUGMSG(proc->fsel_file);
	DEBUGMSG("\n");
	DEBUGMSG(tit);
	DEBUGMSG("\n");

	r = _fsel_exinput(proc, proc->fsel_path, proc->fsel_file, tit);

	appl_top(bp, fn, 0, proc);

	if (r) {
		strcpy(proc->fsel_outname, proc->fsel_path);
		tit = strrchr(proc->fsel_outname, '\\');
		if ((long)tit)
			tit[1] = 0;
		strcat(proc->fsel_outname, proc->fsel_file);

		DEBUGMSG("fsel_init: OK, returning ");
		DEBUGMSG(proc->fsel_outname);
		DEBUGMSG("\n");

		return (long)proc->fsel_outname;
	}

	DEBUGMSG("fsel_init: Cancel, returning NULL\n");

	return 0;
}

/* EOF */


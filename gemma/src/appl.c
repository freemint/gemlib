# include <mintbind.h>
# include <errno.h>

# include "gemma.h"
# include "gemproto.h"
# include "user.h"

extern short whitebak;

static inline void
_v_opnvwk(PROC_ARRAY *proc)
{
	proc->gem.contrl[0] = 100;
	proc->gem.contrl[1] = 0;
	proc->gem.contrl[3] = 11;

	gemsys(VDISYS, proc->gem.vdiparams);
}

static inline void
_v_clsvwk(PROC_ARRAY *proc)
{
	proc->gem.contrl[0] = 101;
	proc->gem.contrl[1] = 0;
	proc->gem.contrl[2] = 0;

	gemsys(VDISYS, proc->gem.vdiparams);
}

static inline void
open_vdi(PROC_ARRAY *proc)
{
	short x;

	proc->gem.contrl[6] = _graf_handle(proc);
	for (x = 0; x < 10; x++)
		proc->gem.intin[x] = 1;
	proc->gem.intin[10] = 2;
	_v_opnvwk(proc);
	proc->gem.vwk_handle = proc->gem.contrl[6];
	proc->gem.vwk_colors = proc->gem.intout[13] ? \
				(long)proc->gem.intout[13] : 65536L;
}

static inline void
close_vdi(PROC_ARRAY *proc)
{
	proc->gem.contrl[6] = proc->gem.vwk_handle;
	_v_clsvwk(proc);
}

long
appl_close(BASEPAGE *bp, long fn, short nargs, PROC_ARRAY *p)
{
	PROC_ARRAY *proc = 0;

	DEBUGMSG("appl_close: begin\n");

	if (nargs >= 1) proc = p;
	if ((nargs < 1) || ((long)proc == 0)) proc = get_contrl(bp);

	if (!proc->gem.global[0])
		return -EACCES;

	close_vdi(proc);

	if (proc->rsclength)
		rsrc_xfree(bp, fn, 1, proc);
	_appl_exit(proc);

	proc->gem.global[0] = 0;	/* invalidate until next init */

	DEBUGMSG("appl_close: complete\n");

	return 0;
}

/* flag extension:
 * 0 - don't load RSC, only alloc (if possible)
 * 1 - don't shel_write(SWM_NEWMSG)
 * 2 - set $HOME as default directory
 */

long
appl_open(BASEPAGE *bp, long fn, short nargs, \
		char *name, short flag, char *desk, PROC_ARRAY *p)
{
	PROC_ARRAY *proc = 0;
	long apid, r;
	char *lname;
	short x, ap[4];

	DEBUGMSG("appl_open() begin\n");

	if (nargs < 3) return -EINVAL;
	if (nargs >= 4) proc = p;
	if ((nargs < 4) || !proc) proc = get_contrl(bp);

	DEBUGMSG("appl_open() enter\n");

	for (x = 0; x < 16; x++)
		proc->gem.global[x] = 0;	/* safe sex */

	apid = _appl_init(proc);

	if (!apid || !proc->gem.global[0])
		apid = -ENXIO;
	if (apid < 0) {
		Cconws("This program requires GEM\r\n\n");
		return apid;
	}

	(void)Pdomain(1);	/* ... obviously */

	DEBUGMSG("appl_open(): RSC stage\n");

	if (flag) {
		r = rsrc_xalloc(bp, fn, 1, proc);
		if (r < 0)
			goto error;
	} else {
		if ((long)name) {
			r = rsrc_xload(bp, fn, 2, name, proc);
			if (r < 0)
				goto error;
			r = rsrc_xalloc(bp, fn, 1, proc);
			if (r < 0)
				goto error;
		}
	}

	DEBUGMSG("appl_open(): shel_write()\n");

	_shel_write(proc, SWM_NEWMSG, 1, 0, 0, 0);

	DEBUGMSG("appl_open(): menu_register()\n");

	if (aes40(proc)) {
		if ((long)desk >= 0) {
			lname = (char *)obj2addr(proc, R_STRING, (long)desk);
			if ((long)lname > 0) {
				TOUCH(lname);
				_menu_register(proc, apid, lname);
			}
		}
		_appl_getinfo(proc, 13, ap);
		if (ap[3] & 4)
			whitebak = 1;
	}

	DEBUGMSG("appl_open(): VDI stage\n");

	open_vdi(proc);

	DEBUGMSG("appl_open() complete\n");

	return apid;

error:	_appl_exit(proc);

	DEBUGMSG("appl_open(): exit on error\n");

	return r;
}

long
appl_top(BASEPAGE *bp, long fn, short nargs, PROC_ARRAY *p)
{
	PROC_ARRAY *proc = 0;
	short ap[4];

	DEBUGMSG("appl_top: begin\n");

	if (nargs >= 1) proc = p;
	if (!nargs || !proc) proc = get_contrl(bp);

	if (!proc->gem.global[0])
		return -EACCES;
	if (!aes40(proc))
		return -ENOSYS;
	_appl_getinfo(proc, 65, ap);
	if (!ap[0] || ap[1] < 12)
		return -ENOSYS;
	if (!_appl_control(proc, 12, 0))
		return -EERROR;

	DEBUGMSG("appl_top: done\n");

	return 0;
}

/* EOF */

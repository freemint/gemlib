/* Application functions
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
# include "gemproto.h"
# include "dosproto.h"
# include "appl.h"
# include "callout.h"
# include "rsrc.h"

short whitebak;

static const long long poweroftwo[] =
{
	0x0000000000000002, 0x0000000000000004, 0x0000000000000008, 0x0000000000000010,
	0x0000000000000020, 0x0000000000000040, 0x0000000000000080, 0x0000000000000100,
	0x0000000000000200, 0x0000000000000400, 0x0000000000000800, 0x0000000000001000,
	0x0000000000002000, 0x0000000000004000, 0x0000000000008000, 0x0000000000010000,
	0x0000000000020000, 0x0000000000040000, 0x0000000000080000, 0x0000000000100000,
	0x0000000000200000, 0x0000000000400000, 0x0000000000800000, 0x0000000001000000,
	0x0000000002000000, 0x0000000004000000, 0x0000000008000000, 0x0000000010000000,
	0x0000000020000000, 0x0000000040000000, 0x0000000080000000, 0x0000000100000000
};

static long long
pwr2(unsigned short what)
{
	if (!what)
		what = 1;
	else if (what > 32)
		what = 32;

	return poweroftwo[what-1];
}

static void
_v_opnvwk(PROC_ARRAY *proc)
{
	proc->gem.contrl[0] = 100;
	proc->gem.contrl[1] = 0;
	proc->gem.contrl[3] = 11;

	gemsys(VDISYS, proc->gem.vdiparams);
}

static void
_vq_extnd(PROC_ARRAY *proc)
{
	proc->gem.contrl[0] = 102;
	proc->gem.contrl[1] = 0;
	proc->gem.contrl[3] = 1;
	proc->gem.contrl[6] = proc->gem.vwk_handle;

	proc->gem.intin[0] = 1;		/* VQ_EXTENDED */

	gemsys(VDISYS, proc->gem.vdiparams);
}

static void
_v_clsvwk(PROC_ARRAY *proc)
{
	proc->gem.contrl[0] = 101;
	proc->gem.contrl[1] = 0;
	proc->gem.contrl[2] = 0;

	gemsys(VDISYS, proc->gem.vdiparams);
}

static void
open_vdi(PROC_ARRAY *proc)
{
	short x;

	proc->gem.contrl[6] = _graf_handle(proc);

	proc->fontw = proc->gem.int_out[1];
	proc->fonth = proc->gem.int_out[2];
	proc->cellw = proc->gem.int_out[3];
	proc->cellh = proc->gem.int_out[4];

	for (x = 0; x < 10; x++)
		proc->gem.intin[x] = 1;
	proc->gem.intin[10] = 2;
	_v_opnvwk(proc);
	if (proc->gem.contrl[6])
	{
		proc->gem.vwk_handle = proc->gem.contrl[6];
		_vq_extnd(proc);
		if (proc->gem.intout[4] <= 24)
		{
			proc->gem.vwk_colors = pwr2(proc->gem.intout[4]);
			proc->gem.vwk_xcolors = (unsigned long long)proc->gem.vwk_colors;
		}
		else
		{
			proc->gem.vwk_colors = 16777216L;
			proc->gem.vwk_xcolors = pwr2(proc->gem.intout[4]);
		}
	}
}

static void
close_vdi(PROC_ARRAY *proc)
{
	if (proc->gem.vwk_handle >= 0)
	{
		proc->gem.contrl[6] = proc->gem.vwk_handle;
		_v_clsvwk(proc);
	}
}

long
appl_close(BASEPAGE *bp, long fn, short nargs, PROC_ARRAY *p)
{
	PROC_ARRAY *proc = 0;

	if (nargs >= 1) proc = p;
	if ((nargs < 1) || !proc) proc = get_contrl(bp);

	DEBUGMSG("enter");

	if (!proc->gem.global[0])
		return -EACCES;

	if (proc->fsel.exec)
	{
		Slbclose(proc->fsel.handle);
		proc->fsel.exec = 0;
		proc->fsel.handle = 0;
	}

	close_vdi(proc);

	if (proc->rsclength)
		rsrc_xfree(bp, RSRC_XFREE, 1, proc);

	_appl_exit(proc);

	Slbclose(proc->kern.handle);
	proc->kern.exec = 0;
	proc->kern.handle = 0;

	DEBUGMSG("complete");

	return 0;
}

/* flag extension (bits):
 * 0 - don't load RSC, only alloc (if possible)
 * 1 - don't shel_write(SWM_NEWMSG)
 * 2 - set $HOME as default directory
 * 3 - don't touch the VDI
 */

long
appl_open(BASEPAGE *bp, long fn, short nargs, \
		char *name, short flag, char *desk, PROC_ARRAY *p)
{
	PROC_ARRAY *proc = 0;
	long apid, r;
	char *lname;
	const char *home;
	short ap[4];

	if (nargs < 3) return -EINVAL;
	if (nargs >= 4) proc = p;
	if ((nargs < 4) || !proc) proc = get_contrl(bp);

	DEBUGMSG("enter");

	/* When appl_open() was already done, just return the apid */
	if (proc->gem.global[0])
		return proc->gem.global[2];

	r = Slbopen("kernel32.slb", 0L, 0x0100L, &proc->kern.handle, &proc->kern.exec);

	if (r < 0)
		return r;

	apid = _appl_init(proc);

	if (!apid || !proc->gem.global[0])
		apid = -ENXIO;
	if (apid < 0)
	{
		_conws("This program requires GEM\n");

		r = (long)apid;
		goto error;
	}

	dos_pdomain(proc, 1);		/* ... obviously */

	home = dos_getenv(proc, "HOME=");
	if (home && (flag & 4))
		_setpath(home);

	DEBUGMSG("RSC stage");

	if (flag & 1)
	{
		r = rsrc_xalloc(bp, RSRC_XALLOC, 1, proc);
		if (r < 0)
			goto error;
	}
	else
	{
		if ((long)name)
		{
			char rscname[1024];

			if (home)
			{
				strcpy(rscname, home);
				strcat(rscname, "\\");
				strcat(rscname, name);

				if (dos_fsize(proc, rscname) > 0)
					name = rscname;
			}

			r = rsrc_xload(bp, RSRC_XLOAD, 2, name, proc);
			if (r < 0)
				goto error;
			r = rsrc_xalloc(bp, RSRC_XALLOC, 1, proc);
			if (r < 0)
				goto error;
# if 0
			{
				char dout[128];
				ulong lo, hi, gad;
				ushort hdr;

				bin2asc((long)proc->gem.global[5], dout);
				_conws(dout);
				_conws("\n");
				bin2asc((long)proc->gem.global[6], dout);
				_conws(dout);
				_conws("\n");

				hi = proc->gem.global[5];
				lo = proc->gem.global[6];
				gad = (hi << 16) + lo;
				bin2asc(gad, dout);
				_conws(dout);
				_conws("\n");

				hdr = *(ushort *)gad;
				bin2asc((long)hdr, dout);
				_conws(dout);
				_conws("\n");
			}
# endif
		}
	}

	DEBUGMSG("shel_write()");

	if ((flag & 2) == 0)
		_shel_write(proc, SWM_NEWMSG, 1, 0, 0, 0);

	DEBUGMSG("menu_register()");

	if (aes40(proc))
	{
		if ((long)desk >= 0)
		{
			lname = (char *)obj2addr(proc, R_STRING, (long)desk);
			if ((long)lname > 0)
				_menu_register(proc, apid, lname);
		}
	}

	_appl_getinfo(proc, AES_OBJECT, ap);
	if (ap[3] & 4)
		whitebak = 1;

	if ((flag & 8) == 0)
	{
		DEBUGMSG("VDI stage");
		open_vdi(proc);
	}

	if (sflags.xfselect)
	{
		char fullname[1024];

		/* Search through the SLBPATH */
		r = dos_fsearch(proc, "fileselector.slb", fullname, "SLBPATH=");

		if (r == 0)
			(void)Slbopen("fileselector.slb", 0L, 0x0100L, &proc->fsel.handle, &proc->fsel.exec);
		else
			sflags.xfselect = 0;
	}

	_graf_mouse(proc, ARROW, 0);

	DEBUGMSG("complete");

	return apid;

error:	_appl_exit(proc);

	Slbclose(proc->kern.handle);
	proc->kern.exec = 0;
	proc->kern.handle = 0;

	DEBUGMSG("error");

	return r;
}

long
appl_top(BASEPAGE *bp, long fn, short nargs, PROC_ARRAY *p)
{
	PROC_ARRAY *proc = 0;
	short ap[4];

	if (nargs >= 1) proc = p;
	if (!nargs || !proc) proc = get_contrl(bp);

	DEBUGMSG("enter");

	if (!proc->gem.global[0])
		return -EACCES;
	_appl_getinfo(proc, 65, ap);
	if (!ap[0] || ap[1] < 12)
		return -ENOSYS;
	if (!aes40(proc))
		return -ENOSYS;
	if (!_appl_control(proc, 12, 0))
		return -EERROR;

	DEBUGMSG("complete");

	return 0;
}

/* EOF */

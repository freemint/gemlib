/* Miscellaneous user functions */

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
# include <mintbind.h>

# include "gemma.h"
# include "dosproto.h"
# include "gemproto.h"
# include "misc.h"
# include "rsrc.h"

long
gem_control(BASEPAGE *bp, long fn, short nargs)
{
	return (long)get_contrl(bp);
}

long
get_users(BASEPAGE *bp, long fn, short nargs, PROC_ARRAY *p)
{
	PROC_ARRAY *proc = 0;
	ushort x;
	long users = 0, r;

	if (nargs >= 1) proc = p;
	if ((nargs < 1) || !proc) proc = get_contrl(bp);

	sema_request(sema_users);

	for (x = 0; x <= MAX_PID; x++)
	{
		if (pidtable[x])
		{
			r = dos_kill(proc, x, 0);	/* SIGNULL */
			if (r < 0)
				pidtable[x] = 0;
			else
				users++;
		}
	}

	sema_release(sema_users);

	return users;
}

long
lib_control(BASEPAGE *bp, long fn, short nargs, \
		short function, long enable, PROC_ARRAY *p)
{
	PROC_ARRAY *proc = 0;
	short val;

	if (nargs < 2) return -EINVAL;
	if (nargs >= 3) proc = p;
	if ((nargs < 3) || !proc) proc = get_contrl(bp);

	if (enable < 0)
		val = -1;
	else
		val = enable ? 1 : 0;

	/* Only root may manipulate global settings */
	if ((val != -1) && (function & 0x4000) && _sgeteuid())
		return -EPERM;

	switch (function)
	{
		/* $0000-$3fff are local for process */
		case	0x0000:	/* debugging */
		{
			if (val == -1)
				return (long)proc->debug;
			proc->debug = val;
			break;
		}
		case	0x0001:	/* get kern */
		{
			return (long)&proc->kern;
		}
		case	0x0002:	/* get version */
		{
			return (long)
			"Gemma shared library version 1.11, "
			"compiled " __DATE__ ". "
			"Copyright (c) 1999-2003 Draco/YC. "
			"Dedicated with love to Magda.";		
		}
		case	0x0003: /* set gemma SLB pointer */
		{
			if (enable > 0)
				proc->ego = (SLB *)enable;
			else
				return -EACCES;
			break;
		} 

		/* $4000-$7fff are global */
		case	0x4000:	/* sflags manipulation */
		{
			if (val == -1)
				return sflags.button_delay;
			sflags.button_delay = enable;
			break;
		}
		case	0x4001:
		{
			if (val == -1)
				return sflags.release_delay;
			sflags.release_delay = enable;
			break;
		}
		case	0x4002:
		{
			if (val == -1)
				return sflags.access_check;
			sflags.access_check = (long)val;
			break;
		}
		case	0x4003:
		{
			if (val == -1)
				return sflags.zoomboxes;
			sflags.zoomboxes = (long)val;
			break;
		}
		case	0x4004:
		{
			if (val == -1)
				return sflags.moveboxes;
			sflags.moveboxes = (long)val;
			break;
		}
		case	0x4005:
		{
			if (val == -1)
				return sflags.screen_comp;
			sflags.screen_comp = (long)val;
			break;
		}
		case	0x4006:
		{
			if (val == -1)
				return sflags.system_alerts;
			sflags.system_alerts = (long)val;
			break;
		}
		case	0x4007:
		{
			if (val == -1)
				return sflags.blocking_alerts;
			sflags.blocking_alerts = (long)val;
			break;
		}
		case	0x4008:
		{
			if (val == -1)
				return sflags.debug;
			sflags.debug = (long)val;
			break;
		}
		case	0x4009:
		{
			if (val == -1)
				return sflags.xfselect;
			sflags.xfselect = (long)val;
			break;
		}
		default:
			return -EBADARG;
	}

	return 0;
}

const char *
get_version(BASEPAGE *bp, long fn, short nargs, PROC_ARRAY *p)
{
	PROC_ARRAY *proc = 0;

	if (nargs >= 1)
		proc = p;
	else
		proc = get_contrl(bp);

	return (const char *)lib_control(bp, LIB_CTRL, 3, 0x0002, 0L, proc);
}

long
ftext_fix(BASEPAGE *bp, long fn, short nargs, \
		short tree, short obj, PROC_ARRAY *p)
{
	PROC_ARRAY *proc = 0;
	OBJECT *blurp;
	TEDINFO *ted;
	long r;
	short ap[4];

	if (nargs < 2) return -EINVAL;
	if (nargs >= 3) proc = p;
	if ((nargs < 3) || !proc) proc = get_contrl(bp);

	if (!proc->gem.global[0])
		return -EACCES;

	r = rsrc_xgaddr(bp, RSRC_XGADDR, 3, R_TREE, tree, proc);
	if (r <= 0)
		return -EINVAL;

	blurp = (OBJECT *)r;
	ted = blurp[obj].ob_spec.tedinfo;

	ted->te_txtlen = ted->te_tmplen;

	_appl_getinfo(proc, AES_LARGEFONT, ap);
	if (ap[2])
	{
		ted->te_font = GDOS_BITM;
		ted->te_fontid = 1;
		ted->te_fontsize = 10;
	}

	return 0;
}

long
objc_xchange(BASEPAGE *bp, long fn, short nargs, \
		WINDIAL *wd, short obj, short newstate, short redraw, PROC_ARRAY *p)
{
	PROC_ARRAY *proc = 0;
	OBJECT *tree;

	if (nargs < 4) return -EINVAL;
	if (nargs >= 5) proc = p;
	if ((nargs < 5) || !proc) proc = get_contrl(bp);

	if (!proc->gem.global[0])
		return -EACCES;
	if (wd->wb_magic != WINDIAL_MAGIC)
		return -EFAULT;

	if (wd->wb_iconified)
	{
		tree = wd->wb_icontree;
		if (redraw && obj)
			redraw = 0;
	}
	else
		tree = wd->wb_treeptr;

	if (redraw && ((wd->wb_ontop & 0x0002) == 0))
		redraw = 0;

	_objc_change(proc, tree, obj, &wd->wb_work_x, newstate, redraw);

	return 0;
}

long
objc_xdraw(BASEPAGE *bp, long fn, short nargs, \
		WINDIAL *wd, short obj, PROC_ARRAY *p)
{
	PROC_ARRAY *proc = 0;

	if (nargs < 2) return -EINVAL;
	if (nargs >= 3) proc = p;
	if ((nargs < 3) || !proc) proc = get_contrl(bp);

	if (!proc->gem.global[0])
		return -EACCES;
	if (wd->wb_magic != WINDIAL_MAGIC)
		return -EFAULT;

	return _objc_draw(proc, wd->wb_treeptr, obj, 7, &wd->wb_work_x);
}

long
menu_xpop(BASEPAGE *bp, long fn, short nargs, \
		WINDIAL *wd, short obj, MENU *menu, PROC_ARRAY *p)
{
	PROC_ARRAY *proc = 0;
	short x, y, ot;

	if (nargs < 3) return -EINVAL;
	if (nargs >= 4) proc = p;
	if ((nargs < 4) || !proc) proc = get_contrl(bp);

	if (!proc->gem.global[0])
		return -EACCES;
	if (wd->wb_magic != WINDIAL_MAGIC)
		return -EFAULT;

	if (!_objc_offset(proc, wd->wb_treeptr, obj))
		return 0;

	x = proc->gem.int_out[1];
	y = proc->gem.int_out[2];

	if (!_menu_popup(proc, menu, x, y, menu))
		return 0;

	ot = wd->wb_treeptr[obj].ob_type;
	if ((ot == G_BUTTON) || (ot == G_STRING) || (ot == G_TITLE))
	{
		ot = menu->mn_tree[menu->mn_item].ob_type;
		if ((ot == G_BUTTON) || (ot == G_STRING) || (ot == G_TITLE))
		{
			wd->wb_treeptr[obj].ob_spec.free_string = \
				menu->mn_tree[menu->mn_item].ob_spec.free_string;
			_objc_draw(proc, wd->wb_treeptr, obj, 1, &wd->wb_work_x);
		}
	}

	return 1;
}

/* EOF */

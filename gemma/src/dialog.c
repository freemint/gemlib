/* Windowed dialog boxes */

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

# include <macros.h>
# include <errno.h>
# include <string.h>

# include "dosproto.h"
# include "gemma.h"
# include "gemproto.h"
# include "user.h"
# include "alert.h"

/* Internal functions */

static long
__rc_intersect(GRECT *r1, GRECT *r2)
{
	short tx, ty, tw, th, ret;

	tx = max(r2->g_x, r1->g_x);
	tw = min(r2->g_x + r2->g_w, r1->g_x + r1->g_w) - tx;
	ret = (0 < tw);
	if (ret)
	{
		ty = max(r2->g_y, r1->g_y);
		th = min(r2->g_y + r2->g_h, r1->g_y + r1->g_h) - ty;
		ret = (0 < th);
		if (ret)
		{
			r2->g_x = tx;
			r2->g_y = ty;
			r2->g_w = tw;
			r2->g_h = th;
		}
	}

	return ret;
}

static long
ret(void)
{
	return 0;
}

static WINDIAL *
find_window(short handle, PROC_ARRAY *proc)
{
	WINDIAL *wd = proc->wchain;

	DEBUGMSG("entering loop");

	do
	{
		if (wd->wb_handle == handle)
		{
			DEBUGMSG("found, exit");
			return wd;
		}
		wd = wd->wb_next;
	} while (wd);

	DEBUGMSG("NULL wd");

	/* Something bad happened, we didn't find the window! */
	_alert(proc, 1, "[1][find_window():|cannot find window!][ Cancel ]");

	return 0;
}

static void
objcedit(PROC_ARRAY *proc, WINDIAL *wd, short mode)
{
	if (!wd->wb_startob)
		return;
	if (wd->wb_iconified)
		return;

	if (mode == ED_INIT)
	{
		TEDINFO *ted;
		short ob = wd->wb_startob;
		OBJECT *tree = wd->wb_treeptr;

		if (wd->wb_fieldinit)
			return;
		ted = tree[ob].ob_spec.tedinfo;
		wd->wb_edindex = strlen(ted->te_ptext);
		wd->wb_fieldinit = 1;
	}

	if (mode == ED_END)
	{
		if (wd->wb_fieldinit)
			wd->wb_fieldinit = 0;
		else
			return;
	}

	_objc_edit(proc, wd->wb_treeptr, wd->wb_startob, R_TREE, wd->wb_edindex, mode);
}

INLINE long
mclick(PROC_ARRAY *proc, WINDIAL *wd)
{
	long r;

	if (wd->wb_iconified)
		return 0;

	r = _objc_find(proc, wd->wb_treeptr, R_TREE, 7, wd->wb_mouse_x, wd->wb_mouse_y);
	if (r < 0)
		return 0;
	wd->wb_object = (short)r;

	if (wd->wb_treeptr[r].ob_flags & OF_EDITABLE)
	{
		objcedit(proc, wd, ED_END);
		wd->wb_startob = wd->wb_object;
		objcedit(proc, wd, ED_INIT);
	}

	if (wd->wb_treeptr[r].ob_flags & (OF_EXIT|OF_TOUCHEXIT))
	{
		r = _form_button(proc, wd->wb_treeptr, wd->wb_object, wd->wb_bclicks);
		if (!r)
		{
			if (sflags.button_delay)
				_evnt_timer(proc, sflags.button_delay);
			return (long)wd->wb_object;
		}
	}

	return 0;
}

INLINE long
kstroke(PROC_ARRAY *proc, WINDIAL *wd, short key)
{
	long r;

	DEBUGMSG("calling form_keybd()");

	if (wd->wb_iconified)
		return 0;

	r = _kbshift(-1);

	if (whitebak && (r & 0x08))
	{
		r = _form_keybd(proc, wd->wb_treeptr, 0x8765, 1, key);
		if (r == 1)
		{
			short oldst, newst;
			OBJECT *o = wd->wb_treeptr;
			ushort so;

			wd->wb_object = proc->gem.int_out[1];
			wd->wb_key = proc->gem.int_out[2];
			oldst = wd->wb_treeptr[wd->wb_object].ob_state;

			if (o[wd->wb_object].ob_flags & OF_RBUTTON)
			{
				if (o[wd->wb_object].ob_state & OS_SELECTED)
					return 0;
				else
				{
					so = wd->wb_object;
					do
					{
						if ((o[so].ob_state & OS_WHITEBAK) && (o[so].ob_flags & OF_RBUTTON))
						{
							newst = o[so].ob_state & ~OS_SELECTED;
							objc_xchange(proc->base, 15L, 5, wd, so, newst, 1, proc);
						}
						if (o[so].ob_head != -1)
							so = o[so].ob_head;
						else
							so = o[so].ob_next;
					} while (so != wd->wb_object);

					newst = oldst | OS_SELECTED;
				}
			}
			else
			{
				if (oldst & OS_SELECTED)
					newst = oldst & ~OS_SELECTED;
				else
					newst = oldst | OS_SELECTED;
			}

			objc_xchange(proc->base, 15L, 5, wd, wd->wb_object, newst, 1, proc);

			return 0;
		}
	}

	r = _form_keybd(proc, wd->wb_treeptr, wd->wb_startob, 1, key);

	wd->wb_object = proc->gem.int_out[1];
	wd->wb_key = proc->gem.int_out[2];

# ifdef DEBUG
	{
		char tmp[32];

		bin2asc((long)key, tmp);
		DEBUGMSG("- passed key is:");
		DEBUGMSG(tmp);

		bin2asc(r, tmp);
		DEBUGMSG("- return value is:");
		DEBUGMSG(tmp);

		bin2asc((long)wd->wb_object, tmp);
		DEBUGMSG("- new object index is:");
		DEBUGMSG(tmp);

		bin2asc((long)wd->wb_key, tmp);
		DEBUGMSG("- new key is:");
		DEBUGMSG(tmp);
	}
# endif

	if (!r)
		return 0;

	/* Don't bother doing anything further if the box
	 * has no edit fields
	 */
	if (!wd->wb_startob)
		return 1;

	if (!wd->wb_key && (wd->wb_object != wd->wb_startob))
	{
		DEBUGMSG("field switch");

		objcedit(proc, wd, ED_END);
		wd->wb_startob = wd->wb_object;
		objcedit(proc, wd, ED_INIT);

		DEBUGMSG("switch OK");

		return 1;
	}

	DEBUGMSG("doing ED_CHAR");

	_objc_edit(proc, wd->wb_treeptr, wd->wb_startob, wd->wb_key, wd->wb_edindex, ED_CHAR);
	wd->wb_edindex = proc->gem.int_out[1];

	DEBUGMSG("complete");

	return r;
}

/* XXX: check if the first window in the chain can be unlinked correctly!! */

static void
wd_struct_unlink(WINDIAL *wd)
{
	WINDIAL *prev, *next;

	prev = wd->wb_prev;
	next = wd->wb_next;

	if (!prev && !next)
		return;					/* nothing to do */
	if (!prev)
		next->wb_prev = 0;
	else if (!next)
		prev->wb_next = 0;
	else
	{
		prev->wb_next = next;
		next->wb_prev = prev;
	}
}

static void
obj_update(WINDIAL *wd)
{
	OBJECT *tree;

	if (wd->wb_iconified)
		tree = wd->wb_icontree;
	else
		tree = wd->wb_treeptr;

	tree->ob_x = wd->wb_work_x;
	tree->ob_y = wd->wb_work_y;
}

static void
calc_center(WINDIAL *wd)
{
	wd->wb_center_x = (wd->wb_border_x + wd->wb_border_w) >> 1;
	wd->wb_center_y = (wd->wb_border_y + wd->wb_border_h) >> 1;
}

static void
reset_form(PROC_ARRAY *proc, WINDIAL *wd)
{
	OBJECT *tree;
	short comp = 0;

	if (wd->wb_iconified)
		tree = wd->wb_icontree;
	else
		tree = wd->wb_treeptr;

	wd->wb_work_x = tree->ob_x;
	wd->wb_work_y = tree->ob_y;
	wd->wb_work_w = tree->ob_width;
	wd->wb_work_h = tree->ob_height;

	_wind_calc(proc, WC_BORDER, wd->wb_gadgets, &wd->wb_work_x);
	wd->wb_border_x = proc->gem.int_out[1];
	wd->wb_border_y = proc->gem.int_out[2];
	wd->wb_border_w = proc->gem.int_out[3];
	wd->wb_border_h = proc->gem.int_out[4];

	if (sflags.screen_comp)
		comp = proc->cellh + 2;
	wd->wb_border_x = (wd->wb_desk_w - wd->wb_border_w) >> 1;
	wd->wb_border_y = (((wd->wb_desk_h - comp) - wd->wb_border_h) >> 1) + comp;

	_wind_calc(proc, WC_WORK, wd->wb_gadgets, &wd->wb_border_x);
	wd->wb_work_x = proc->gem.int_out[1];
	wd->wb_work_y = proc->gem.int_out[2];
	wd->wb_work_w = proc->gem.int_out[3];
	wd->wb_work_h = proc->gem.int_out[4];

	obj_update(wd);
	calc_center(wd);
}

/* User functions */

long
_rc_intersect(BASEPAGE *bp, long fn, short nargs, GRECT *rc1, GRECT *rc2)
{
	return __rc_intersect(rc1, rc2);
}

long
windial_size(void)
{
	return sizeof(WINDIAL);
}

long
windial_center(BASEPAGE *bp, long fn, short nargs, WINDIAL *wd, PROC_ARRAY *p)
{
	PROC_ARRAY *proc = 0;

	if (!nargs)
		return -EINVAL;
	if (nargs > 1) proc = p;
	if ((nargs < 2) || !proc) proc = get_contrl(bp);

	if (!proc->gem.global[0])
		return -EACCES;
	if (wd->wb_magic != WINDIAL_MAGIC)
		return -EFAULT;

	reset_form(proc, wd);

	proc->gem.int_in[2] = wd->wb_border_x;
	proc->gem.int_in[3] = wd->wb_border_y;
	proc->gem.int_in[4] = wd->wb_border_w;
	proc->gem.int_in[5] = wd->wb_border_h;
	_wind_set(proc, wd->wb_handle, WF_CURRXYWH);

	return 0;
}

/* Initialize the WINDIAL structure for the window
 */
long
windial_create(BASEPAGE *bp, long fn, short nargs, \
		WINDIAL *wd, short obj, short icon, short field, \
		char *title, short gadgets, PROC_ARRAY *p)
{
	PROC_ARRAY *proc = 0;
	short m = 0, g;
	long r;

	if (nargs < 5) return -EINVAL;
	if (nargs == 5)
		g = NAME|MOVER|CLOSER|FULLER;
	else
		g = gadgets;
	if (nargs > 6) proc = p;
	if ((nargs < 7) || !proc) proc = get_contrl(bp);

	if (!proc->gem.global[0])
		return -EACCES;

	DEBUGMSG("enter");

	if (!wd)
	{
		if (proc->window.wb_magic == WINDIAL_MAGIC)
		{
			wd = (WINDIAL *)_alloc(sizeof(WINDIAL));
			m = 1;
		} else
			wd = (WINDIAL *)&proc->window.wb_treeptr;
	}

	if (!wd)
		return -ENOMEM;

	if ((long)wd < 0)
		return (long)wd;

	if (!proc->wchain)
		proc->wchain = wd;

	bzero(wd, sizeof(WINDIAL));

	DEBUGMSG("init handlers");

	r = (long)ret;
	wd->wb_exthandler = r;
	wd->wb_keyhandler = r;
	wd->wb_buthandler = r;
	wd->wb_rc1handler = r;
	wd->wb_rc2handler = r;
	wd->wb_timhandler = r;

	DEBUGMSG("init title");

	wd->wb_title = (char *)obj2addr(proc, R_STRING, (ulong)title);
	wd->wb_startob = field;
	wd->wb_gadgets = g;

	DEBUGMSG("init icon");

	if (icon)
	{
		wd->wb_icon = icon;
		r = rsrc_xgaddr(bp, 16L, 3, R_TREE, icon, proc);
		if (r > 0)
		{
			short ap[4];

			TOUCH(r);
			wd->wb_icontree = (OBJECT *)r;
			_appl_getinfo(proc, 11, ap);
			if (ap[2] & 1)
				wd->wb_gadgets |= SMALLER;
		}
	}
	if (!wd->wb_icontree)
		wd->wb_gadgets &= ~SMALLER;

	DEBUGMSG("init tree");

	wd->wb_box = obj;
	r = rsrc_xgaddr(bp, 16L, 3, R_TREE, obj, proc);
	if (r <= 0)
	{
		_alert(proc, 1, "[1][windial_create():|cannot find root object|requested by apid %a!][ Cancel ]\n");
		goto fatal;
	}
	TOUCH(r);
	wd->wb_treeptr = (OBJECT *)r;

	DEBUGMSG("init textfields");
	{
		OBJECT *o = wd->wb_treeptr;
		ushort so;

		for (so = 0; so < 0xffff; so++)
		{
			if (o[so].ob_flags & OF_EDITABLE)
			{
				r = ftext_fix(bp, 29L, 3, wd->wb_box, so, proc);
				if (r) break;
			}
			if (o[so].ob_flags & OF_LASTOB)
				break;
		}
	}

	DEBUGMSG("init fillpatterns");
	if (proc->gem.vwk_colors < 16)
	{
		OBJECT *o = wd->wb_treeptr;
		ushort so, ot;

		for (so = 0; so < 0xffff; so++)
		{
			ot = o[so].ob_type;
			if ((ot == G_BOX) || (ot == G_IBOX))
				o[so].ob_spec.obspec.fillpattern = 0;
			if (o[so].ob_flags & OF_LASTOB)
				break;
		}
	}

	DEBUGMSG("get desk size");
	_wind_get(proc, 0, WF_WORKXYWH);
	wd->wb_desk_x = proc->gem.int_out[1];
	wd->wb_desk_y = proc->gem.int_out[2];
	wd->wb_desk_w = proc->gem.int_out[3];
	wd->wb_desk_h = proc->gem.int_out[4];

	DEBUGMSG("reset form");
	reset_form(proc, wd);

	DEBUGMSG("create window");
	r = _wind_create(proc, wd->wb_gadgets, &wd->wb_border_x);
	if (r <= 0)
	{
		_alert(proc, 1, "[1][windial_create():|cannot create new window|requested by apid %a!][ Cancel ]\n");
		goto fatal;
	}
	wd->wb_handle = r;

	DEBUGMSG("set title");
	r = (long)wd->wb_title;
	if (r <= 0)
		r = (long)"";
	proc->gem.int_in[2] = (short)(r >> 16);
	proc->gem.int_in[3] = (short)r;
	_wind_set(proc, wd->wb_handle, WF_NAME);

	DEBUGMSG("init events");
	wd->wb_eventmask = MU_MESAG|MU_KEYBD|MU_BUTTON;
	wd->wb_bclicks = 1;
	wd->wb_bmask = 0x0001;
	wd->wb_bstate = 1;

	wd->wb_autofree = m;
	wd->wb_magic = WINDIAL_MAGIC;

	DEBUGMSG("complete");

	return (long)wd;

fatal:	if (m)
		_free((long)wd);

	DEBUGMSG("exit on error");

	return -EINVAL;
}

long
windial_open(BASEPAGE *bp, long fn, short nargs, WINDIAL *wd, PROC_ARRAY *p)
{
	PROC_ARRAY *proc = 0;

	if (!nargs) return -EINVAL;
	if (nargs > 1) proc = p;
	if ((nargs < 2) || !proc) proc = get_contrl(bp);

	if (!proc->gem.global[0])
		return -EACCES;
	if (wd->wb_magic != WINDIAL_MAGIC)
		return -EFAULT;

	DEBUGMSG("enter");

	if (!wd->wb_ontop)
	{
		_graf_mkstate(proc);
		wd->wb_start_x = proc->gem.int_out[1];
		wd->wb_start_y = proc->gem.int_out[2];

		_graf_movebox(proc, 16, 16, wd->wb_start_x, wd->wb_start_y, wd->wb_center_x, wd->wb_center_y);
		_graf_growbox(proc, wd->wb_center_x, wd->wb_center_y, 1, 1, &wd->wb_border_x);

		_wind_open(proc, wd->wb_handle, &wd->wb_border_x);

		wd->wb_ontop = 0x0003;	/* bit 0 is 'ontop', bit 1 is 'opened' */
	}

	DEBUGMSG("complete");

	return 0;
}

long
windial_close(BASEPAGE *bp, long fn, short nargs, WINDIAL *wd, PROC_ARRAY *p)
{
	PROC_ARRAY *proc = 0;

	if (!nargs) return -EINVAL;
	if (nargs > 1) proc = p;
	if ((nargs < 2) || !proc) proc = get_contrl(bp);

	if (!proc->gem.global[0])
		return -EACCES;
	if (wd->wb_magic != WINDIAL_MAGIC)
		return -EFAULT;

	DEBUGMSG("enter");

	if (wd->wb_ontop)
	{
		if (wd->wb_startob && !wd->wb_iconified)
			_objc_edit(proc, wd->wb_treeptr, wd->wb_startob, 0, wd->wb_edindex, ED_END);

		_wind_close(proc, wd->wb_handle);

		_graf_shrinkbox(proc, wd->wb_center_x, wd->wb_center_y, 1, 1, &wd->wb_border_x);
		_graf_movebox(proc, 16, 16, wd->wb_center_x, wd->wb_center_y, wd->wb_start_x, wd->wb_start_y);

		wd->wb_ontop = 0;
	}
	
	DEBUGMSG("complete");

	return 0;
}

long
windial_delete(BASEPAGE *bp, long fn, short nargs, WINDIAL *wd, PROC_ARRAY *p)
{
	PROC_ARRAY *proc = 0;

	if (!nargs) return -EINVAL;
	if (nargs > 1) proc = p;
	if ((nargs < 2) || !proc) proc = get_contrl(bp);

	if (!proc->gem.global[0])
		return -EACCES;
	if (wd->wb_magic != WINDIAL_MAGIC)
		return -EFAULT;

	DEBUGMSG("enter");

	if (wd->wb_ontop)
		windial_close(bp, 6L, 2, wd, proc);

	_wind_delete(proc, wd->wb_handle);

	/* If this is the last window, its wb_next pointer is NULL
	 */
	if (wd == proc->wchain)
		proc->wchain = wd->wb_next;
	else
		wd_struct_unlink(wd);

	wd->wb_magic = 0;		/* invalidate the struct */

	if (wd->wb_autofree)
		_free((long)wd);

	DEBUGMSG("complete");

	return 0;
}

long
windial_formdo(BASEPAGE *bp, long fn, short nargs, WINDIAL *wd, PROC_ARRAY *p)
{
	PROC_ARRAY *proc = 0;
	long retval;

	if (!nargs) return -EINVAL;
	if (nargs > 1) proc = p;
	if ((nargs < 2) || !proc) proc = get_contrl(bp);

	if (!proc->gem.global[0])
		return -EACCES;
	if (wd->wb_magic != WINDIAL_MAGIC)
		return -EFAULT;

	DEBUGMSG("enter");

	for(;;)
	{
		long m;

		/* Timer events are asynchronous and can be enabled at any time
		 */
		if (wd->wb_eventmask & MU_TIMER)
		{
			long timer = wd->wb_timer;
			long timhandler = wd->wb_timhandler;
			long timstack = wd->wb_timstack;
			WINDIAL *chain = proc->wchain;

			DEBUGMSG("updating timers");

			do
			{
				chain->wb_timer = timer;
				chain->wb_timhandler = timhandler;
				chain->wb_timstack = timstack;
				chain = chain->wb_next;
			} while (chain);

			DEBUGMSG("timers complete");
		}

		DEBUGMSG("entering event loop");

		m = _evnt_multi(proc, wd->wb_eventmask, wd->wb_bclicks, wd->wb_bmask, \
			wd->wb_bstate, wd->wb_m1flag, wd->wb_m1x, wd->wb_m1y, \
			wd->wb_m1w, wd->wb_m1h, wd->wb_m2flag, wd->wb_m2x, \
			wd->wb_m2y, wd->wb_m2w, wd->wb_m2h, \
			wd->wb_aesmessage, wd->wb_timer);

		DEBUGMSG("exiting event loop");

		if (m & MU_TIMER)
		{
			typedef void (*EXEC)(WINDIAL *wd, short vec, ulong count);
			EXEC hnd = (EXEC)wd->wb_timhandler;

			if (hnd)
			{
				DEBUGMSG("calling timer handler");
				(hnd)(wd, WD_TIMVEC, wd->wb_timer);
				DEBUGMSG("returning from timer handler");
			}
		}

		if (m & MU_BUTTON)
		{
			typedef void (*EXEC)(WINDIAL *wd, short vec);
			EXEC hnd = (EXEC)wd->wb_buthandler;
			short newhandle;

			wd->wb_mouse_x = proc->gem.int_out[1];
			wd->wb_mouse_y = proc->gem.int_out[2];

			newhandle = _wind_find(proc, wd->wb_mouse_x, wd->wb_mouse_y);

			if (wd->wb_handle != newhandle)
			{
				WINDIAL *oldwd = wd;

				DEBUGMSG("switch windows");

				wd = find_window(newhandle, proc);
				if (!wd)
				{
					wd = oldwd;			/* hope this never happens! */
					DEBUGMSG("switch error");
					continue;
				}
				else if (wd != oldwd)
				{
					DEBUGMSG("copying mouse coordinates");
					wd->wb_mouse_x = oldwd->wb_mouse_x;
					wd->wb_mouse_y = oldwd->wb_mouse_y;
				}
				DEBUGMSG("windows switched");
			}

			if (hnd)
			{
				DEBUGMSG("calling button handler");
				(hnd)(wd, WD_BUTVEC);
				DEBUGMSG("returning from button handler");
			}

			if (mclick(proc, wd))
				break;
		}

		if (m & MU_KEYBD)
		{
			typedef long (*EXEC)(WINDIAL *wd, short vec, short ks, short kc);
			EXEC hnd = (EXEC)wd->wb_keyhandler;
			long r = 0;
			short key, kst;

			kst = proc->gem.int_out[4];
			key = proc->gem.int_out[5];
			if (hnd)
			{
				DEBUGMSG("calling keyboard handler");
				r = (hnd)(wd, WD_KEYVEC, kst, key);
				DEBUGMSG("returned from keyboard handler");
				if (r > 0)
					key = (short)r;
			}
			if (r >= 0)
			{
				r = kstroke(proc, wd, key);
				if (!r)
					break;
			}
		}
		if (m & MU_MESAG)
		{
			long r = 0;

			switch(wd->wb_aesmessage[0])
			{
				case	WM_REDRAW:
				case	WM_TOPPED:
				case	WM_CLOSED:
				case	WM_FULLED:
				case	WM_SIZED:
				case	WM_MOVED:
				case	WM_UNTOPPED:
				case	WM_ONTOP:
				case	WM_BOTTOMED:
				case	WM_ICONIFY:
				case	WM_UNICONIFY:
				case	WM_ALLICONIFY:
				{
					if (wd->wb_handle != wd->wb_aesmessage[3])
					{
						WINDIAL *oldwd = wd;
						short x;

						DEBUGMSG("switch windows");

						wd = find_window(wd->wb_aesmessage[3], proc);
						if (!wd)
						{
							wd = oldwd;
							DEBUGMSG("switch error");
							continue;
						}
						else if (wd != oldwd)
						{
							DEBUGMSG("copying message buffer");
							for (x = 0; x < 8; x++)
								wd->wb_aesmessage[x] = oldwd->wb_aesmessage[x];
						}
						DEBUGMSG("windows switched");
					}
				}
			}

			{
				typedef long (*EXEC)(WINDIAL *wd, short vec, short *aesmsg);
				EXEC hnd = (EXEC)wd->wb_exthandler;

				if (hnd)
				{
					DEBUGMSG("calling message handler");
					r = (hnd)(wd, WD_MSGVEC, wd->wb_aesmessage);
					DEBUGMSG("returning from message handler");
				}
			}

			if (r >= 0)
			{
				short msg = wd->wb_aesmessage[0];

				switch (msg)
				{
					case WM_CLOSED:
						{
							DEBUGMSG("WM_CLOSED");
							retval = wd->wb_box;
							retval <<= 16;
							retval |= 0x0000ffffL;
							return retval;
						}
					case WM_TOPPED:
					case WM_ONTOP:
						if ((wd->wb_ontop & 0x0001) == 0)
						{
							DEBUGMSG("WM_TOPPED/WM_ONTOP");
							_wind_set(proc, wd->wb_handle, WF_TOP);
							wd->wb_ontop |= 1;
							objcedit(proc, wd, ED_INIT);
						}
						break;
					case WM_BOTTOMED:
						if (wd->wb_ontop & 0x0001)
						{
							DEBUGMSG("WM_BOTTOMED");
							objcedit(proc, wd, ED_END);
							_wind_set(proc, wd->wb_handle, WF_BOTTOM);
							wd->wb_ontop &= ~0x0001;
						}
						break;
					case WM_UNTOPPED:
						DEBUGMSG("WM_UNTOPPED");
						wd->wb_ontop &= ~0x0001;
						break;
					case WM_FULLED:
					case WM_MOVED:
						if (msg == WM_MOVED)
						{
							DEBUGMSG("WM_MOVED, enter");
							if (sflags.moveboxes)
								_graf_movebox(proc, wd->wb_border_w, wd->wb_border_h, \
										wd->wb_border_x, wd->wb_border_y, \
										wd->wb_aesmessage[4], wd->wb_aesmessage[5]);
							wd->wb_border_x = wd->wb_aesmessage[4];
							wd->wb_border_y = wd->wb_aesmessage[5];
							wd->wb_border_w = wd->wb_aesmessage[6];
							wd->wb_border_h = wd->wb_aesmessage[7];
						}
						else
						{
							DEBUGMSG("WM_FULLED");
							reset_form(proc, wd);
						}
						proc->gem.int_in[2] = wd->wb_border_x;
						proc->gem.int_in[3] = wd->wb_border_y;
						proc->gem.int_in[4] = wd->wb_border_w;
						proc->gem.int_in[5] = wd->wb_border_h;
						_wind_set(proc, wd->wb_aesmessage[3], WF_CURRXYWH);
						if (msg == WM_MOVED)
						{
							DEBUGMSG("WM_MOVED, exit");
							calc_center(wd);
							_wind_calc(proc, WC_WORK, wd->wb_gadgets, &wd->wb_border_x);
							wd->wb_work_x = proc->gem.int_out[1];
							wd->wb_work_y = proc->gem.int_out[2];
							wd->wb_work_w = proc->gem.int_out[3];
							wd->wb_work_h = proc->gem.int_out[4];
							obj_update(wd);
						}
						break;
					case WM_ICONIFY:
					case WM_UNICONIFY:
						{
							short wset;

							if (msg == WM_ICONIFY)
							{
								DEBUGMSG("WM_ICONIFY");
								_form_dial(proc, FMD_SHRINK, &wd->wb_aesmessage[4], &wd->wb_work_x);
								wset = WF_ICONIFY;
								wd->wb_iconified = 1;
							}
							else
							{
								DEBUGMSG("WM_UNICONIFY");
								_form_dial(proc, FMD_GROW, &wd->wb_work_x, &wd->wb_aesmessage[4]);
								wset = WF_UNICONIFY;
								wd->wb_iconified = 0;
							}
							proc->gem.int_in[2] = wd->wb_aesmessage[4];
							proc->gem.int_in[3] = wd->wb_aesmessage[5];
							proc->gem.int_in[4] = wd->wb_aesmessage[6];
							proc->gem.int_in[5] = wd->wb_aesmessage[7];
							_wind_set(proc, wd->wb_handle, wset);
							_wind_get(proc, wd->wb_handle, WF_WORKXYWH);
							wd->wb_work_x = proc->gem.int_out[1];
							wd->wb_work_y = proc->gem.int_out[2];
							wd->wb_work_w = proc->gem.int_out[3];
							wd->wb_work_h = proc->gem.int_out[4];
							obj_update(wd);
						}
						break;
					case WM_REDRAW:
						{
							short md;

							DEBUGMSG("WM_REDRAW enter");
							if (wd->wb_ontop & 0x0001)
								objcedit(proc, wd, ED_END);
							md = WF_FIRSTXYWH;
							_wind_update(proc, BEG_UPDATE);
							for(;;)
							{
								_wind_get(proc, wd->wb_aesmessage[3], md);
								if ((proc->gem.int_out[3] == 0) && (proc->gem.int_out[4] == 0))
									break;
								wd->wb_rcdraw_x = wd->wb_aesmessage[4];
								wd->wb_rcdraw_y = wd->wb_aesmessage[5];
								wd->wb_rcdraw_w = wd->wb_aesmessage[6];
								wd->wb_rcdraw_h = wd->wb_aesmessage[7];
								if (__rc_intersect((GRECT *)&proc->gem.int_out[1], (GRECT *)&wd->wb_rcdraw_x))
								{
									if (wd->wb_iconified)
										_objc_draw(proc, wd->wb_icontree, R_TREE, 1, &wd->wb_rcdraw_x);
									else
										_objc_draw(proc, wd->wb_treeptr, R_TREE, 7, &wd->wb_rcdraw_x);
								}
								md = WF_NEXTXYWH;
							}
							_wind_update(proc, END_UPDATE);
							if (wd->wb_ontop & 0x0001)
								objcedit(proc, wd, ED_INIT);
							DEBUGMSG("WM_REDRAW complete");
						}
						break;
				}
			}
		}
	}

	retval = wd->wb_box;
	retval <<= 16;
	retval |= (ushort)wd->wb_object;

	DEBUGMSG("exit");

	return retval;
}

long
windial_link(BASEPAGE *bp, long fn, short nargs, WINDIAL *old, WINDIAL *new, PROC_ARRAY *p)
{
	WINDIAL *newhandle = new, *w = old;

	if (nargs < 2) return -EINVAL;

	if (old->wb_magic != WINDIAL_MAGIC)
		return -EFAULT;

	for(;;)
	{
		if (!w->wb_next)
			break;
		if (w->wb_next == old)
			return -EINTERNAL;
		w = w->wb_next;
	}

	w->wb_next = newhandle;
	newhandle->wb_prev = w;

	return (long)newhandle;
}

long
windial_unlink(BASEPAGE *bp, long fn, short nargs, WINDIAL *wd, PROC_ARRAY *p)
{
	PROC_ARRAY *proc = 0;

	if (!nargs) return -EINVAL;
	if (nargs > 1) proc = p;
	if ((nargs < 2) || !proc) proc = get_contrl(bp);

	if (wd->wb_magic != WINDIAL_MAGIC)
		return -EFAULT;

	if (wd != proc->wchain)
		wd_struct_unlink(wd);

	return 0;
}

/* EOF */

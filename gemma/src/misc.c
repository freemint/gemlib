/* Miscellaneous user functions */

# include <macros.h>
# include <errno.h>

# include "gemma.h"
# include "gemproto.h"
# include "user.h"

long
__rc_intersect(GRECT *r1, GRECT *r2)
{
	short tx, ty, tw, th, ret;

	tx = max(r2->g_x, r1->g_x);
	tw = min(r2->g_x + r2->g_w, r1->g_x + r1->g_w) - tx;
	ret = (0 < tw);
	if (ret)
	{
		ty = max (r2->g_y, r1->g_y);
		th = min (r2->g_y + r2->g_h, r1->g_y + r1->g_h) - ty;
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

long
_rc_intersect(BASEPAGE *bp, long fn, short nargs, \
		GRECT *rc1, GRECT *rc2)
{
	return __rc_intersect(rc1, rc2);
}

long
get_users(void)
{
	extern long users;	/* in gemma.c */

	return users;
}

char *
get_version(void)
{
	extern const char Version[];	/* in version.c */

	return (char *)Version;
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
	if ((nargs < 3) || ((long)proc == 0)) proc = get_contrl(bp);

	if (!proc->gem.global[0])
		return -EACCES;

	r = rsrc_xgaddr(bp, fn, 3, R_TREE, tree, proc);
	if (r <= 0)
		return -EINVAL;

	blurp = (OBJECT *)r;
	ted = blurp[obj].ob_spec.tedinfo;

	ted->te_txtlen = ted->te_tmplen;

	if (aes40(proc))
	{
		r = _appl_getinfo(proc, AES_LARGEFONT, ap);
		if (ap[2])
		{
			ted->te_font = GDOS_BITM;
			ted->te_fontid = 1;
			ted->te_fontsize = 10;
		}
	}

	return 0;
}

long
gem_control(BASEPAGE *bp, long fn, short nargs)
{
	return (long)get_contrl(bp);
}

long
call_aes(BASEPAGE *bp, long fn, short nargs, PROC_ARRAY *proc, short opcode)
{
	if (nargs < 2) return -EINVAL;
	if (opcode > MAX_AES_OP) return -ENOSYS;
	if ((long)proc == 0) proc = get_contrl(bp);

	/* Fixes section */
	switch(opcode)
	{
		case 12:	/* appl_write(), round length up to 16 byte boundary */
		{
			short r;

			r = proc->gem.int_in[1];
			if (r & 0x000f)
			{
				r += 0xf;
				r &= ~0xf;
				proc->gem.int_in[1] = r;
			}
		}
	}

	return _aes(proc, opcode);
}

long
objc_xchange(BASEPAGE *bp, long fn, short nargs, \
		WINDIAL *wd, short obj, short newstate, short redraw, PROC_ARRAY *p)
{
	PROC_ARRAY *proc = 0;

	if (nargs < 4) return -EINVAL;
	if (nargs >= 5) proc = p;
	if ((nargs < 5) || ((long)proc == 0)) proc = get_contrl(bp);

	if (!proc->gem.global[0])
		return -EACCES;
	if (wd->wb_magic != WINDIAL_MAGIC)
		return -EFAULT;

	if (wd->wb_iconified)
		_objc_change(proc, wd->wb_icontree, obj, &wd->wb_work_x, newstate, redraw);
	else
		_objc_change(proc, wd->wb_treeptr, obj, &wd->wb_work_x, newstate, redraw);

	return 0;
}

long
menu_xpop(BASEPAGE *bp, long fn, short nargs, \
		WINDIAL *wd, short obj, MENU *menu, PROC_ARRAY *p)
{
	PROC_ARRAY *proc = 0;
	short x, y, ot;

	if (nargs < 3) return -EINVAL;
	if (nargs >= 4) proc = p;
	if ((nargs < 4) || ((long)proc == 0)) proc = get_contrl(bp);

	if (!proc->gem.global[0])
		return -EACCES;
	if (wd->wb_magic != WINDIAL_MAGIC)
		return -EFAULT;

	if (!_objc_offset(proc, wd->wb_treeptr, obj))
		return 0;

	x = proc->gem.int_out[1];
	y = proc->gem.int_out[2];

	TOUCH(menu);			/* access test */

	if (!_menu_popup(proc, menu, x, y, menu))
		return 0;

	ot = wd->wb_treeptr[obj].ob_type;
	if ((ot == G_BUTTON) || (ot == G_STRING) || (ot == G_TITLE)) {
		ot = menu->mn_tree[menu->mn_item].ob_type;
		if ((ot == G_BUTTON) || (ot == G_STRING) || (ot == G_TITLE)) {
			wd->wb_treeptr[obj].ob_spec.free_string = \
				menu->mn_tree[menu->mn_item].ob_spec.free_string;
			_objc_draw(proc, wd->wb_treeptr, obj, 1, &wd->wb_work_x);
		}
	}

	return 1;
}

/* EOF */

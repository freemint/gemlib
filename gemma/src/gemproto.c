/* Internally used GEM calls */

# include "gemma.h"
# include "gemproto.h"

/* The AES calling routine */

long
_aes(PROC_ARRAY *proc, short opcode)
{
	extern const ulong ctrl_list[];
	ulong ctrl;
	ushort c12, c34;

	ctrl = ctrl_list[opcode];
	c34 = (ushort)ctrl;
	c12 = (ushort)(ctrl >> 16);

	proc->gem.control[4] = c34&0x00ff;
	proc->gem.control[3] = c34>>8;
	proc->gem.control[2] = c12&0x00ff;
	proc->gem.control[1] = c12>>8;
	proc->gem.control[0] = opcode;

	gemsys(AESSYS, proc->gem.aesparams);

	return (long)proc->gem.int_out[0];
}

long
_appl_control(PROC_ARRAY *proc, short opcode, void *out)
{
	proc->gem.int_in[0] = proc->gem.global[2];	/* apid */
	proc->gem.int_in[1] = opcode;
	proc->gem.addr_in[0] = (long)out;

	return _aes(proc, 129);
}

long
_appl_find(PROC_ARRAY *proc, char *name)
{
	proc->gem.addr_in[0] = (long)name;

	return _aes(proc, 13);
}

long
_appl_getinfo(PROC_ARRAY *proc, short fn, short *out)
{
	long r;

	out[0] = out[1] = out[2] = out[3] = 0;
	proc->gem.int_in[0] = fn;
	r = _aes(proc, 130);
	if (r == 1) {
		out[0] = proc->gem.int_out[1];
		out[1] = proc->gem.int_out[2];
		out[2] = proc->gem.int_out[3];
		out[3] = proc->gem.int_out[4];
	}
	return r;
}

long
_appl_write(PROC_ARRAY *proc, short id, short len, short *buf)
{
	proc->gem.int_in[0] = id;
	proc->gem.int_in[1] = len;
	proc->gem.addr_in[0] = (long)buf;

	return _aes(proc, 12);
}

long
_evnt_multi(PROC_ARRAY *proc, short fl, short cl, short mask, short state, \
			short m1f, short m1x, short m1y, short m1w, short m1h, \
			short m2f, short m2x, short m2y, short m2w, short m2h, \
			short *msg, unsigned long timer)
{
	proc->gem.int_in[0] = fl;
	proc->gem.int_in[1] = cl;
	proc->gem.int_in[2] = mask;
	proc->gem.int_in[3] = state;
	proc->gem.int_in[4] = m1f;
	proc->gem.int_in[5] = m1x;
	proc->gem.int_in[6] = m1y;
	proc->gem.int_in[7] = m1w;
	proc->gem.int_in[8] = m1h;
	proc->gem.int_in[9] = m2f;
	proc->gem.int_in[10] = m2x;
	proc->gem.int_in[11] = m2y;
	proc->gem.int_in[12] = m2w;
	proc->gem.int_in[13] = m2h;
	proc->gem.int_in[14] = (short)timer;
	proc->gem.int_in[15] = (short)(timer>>16);

	proc->gem.addr_in[0] = (long)msg;

	return _aes(proc, 25);
}

long
_evnt_timer(PROC_ARRAY *proc, unsigned long timer)
{
	proc->gem.int_in[0] = (short)timer;
	proc->gem.int_in[1] = timer>>16;

	return _aes(proc, 24);
}

long
_fsel_exinput(PROC_ARRAY *proc, char *path, char *name, char *title)
{
	short op = 90 + (proc->gem.global[0] >= 0x0104);

	proc->gem.addr_in[0] = (long)path;
	proc->gem.addr_in[1] = (long)name;
	proc->gem.addr_in[2] = (long)title;

	if (_aes(proc, op))
		return (long)proc->gem.int_out[1];

	return 0;
}

long
_form_alert(PROC_ARRAY *proc, short button, char *msg)
{
	proc->gem.int_in[0] = button;
	proc->gem.addr_in[0] = (long)msg;

	return _aes(proc, 52);
}

long
_form_button(PROC_ARRAY *proc, OBJECT *tree, short obj, short clk)
{
	proc->gem.int_in[0] = obj;
	proc->gem.int_in[1] = clk;
	proc->gem.addr_in[0] = (long)tree;

	return _aes(proc, 56);
}

long
_form_dial(PROC_ARRAY *proc, short flag, short *dxywh, short *cxywh)
{
	proc->gem.int_in[0] = flag;
	proc->gem.int_in[1] = dxywh[0];
	proc->gem.int_in[2] = dxywh[1];
	proc->gem.int_in[3] = dxywh[2];
	proc->gem.int_in[4] = dxywh[3];
	proc->gem.int_in[5] = cxywh[0];
	proc->gem.int_in[6] = cxywh[1];
	proc->gem.int_in[7] = cxywh[2];
	proc->gem.int_in[8] = cxywh[3];

	return _aes(proc, 51);
}

long
_form_keybd(PROC_ARRAY *proc, OBJECT *tree, short obj, short nobj, short tch)
{
	proc->gem.int_in[0] = obj;
	proc->gem.int_in[1] = tch;
	proc->gem.int_in[2] = nobj;
	proc->gem.addr_in[0] = (long)tree;

	return _aes(proc, 55);
}

long
_graf_movebox(PROC_ARRAY *proc, short w, short h, short x, short y, short dx, short dy)
{
	proc->gem.int_in[0] = w;
	proc->gem.int_in[1] = h;
	proc->gem.int_in[2] = x;
	proc->gem.int_in[3] = y;
	proc->gem.int_in[4] = dx;
	proc->gem.int_in[5] = dy;

	return _aes(proc, 72);
}

long
_graf_growbox(PROC_ARRAY *proc, short x, short y, short w, short h, short *xywh)
{
	proc->gem.int_in[0] = x;
	proc->gem.int_in[1] = y;
	proc->gem.int_in[2] = w;
	proc->gem.int_in[3] = h;
	proc->gem.int_in[4] = xywh[0];
	proc->gem.int_in[5] = xywh[1];
	proc->gem.int_in[6] = xywh[2];
	proc->gem.int_in[7] = xywh[3];

	return _aes(proc, 73);
}

long
_graf_shrinkbox(PROC_ARRAY *proc, short x, short y, short w, short h, short *xywh)
{
	proc->gem.int_in[0] = x;
	proc->gem.int_in[1] = y;
	proc->gem.int_in[2] = w;
	proc->gem.int_in[3] = h;
	proc->gem.int_in[4] = xywh[0];
	proc->gem.int_in[5] = xywh[1];
	proc->gem.int_in[6] = xywh[2];
	proc->gem.int_in[7] = xywh[3];

	return _aes(proc, 74);
}

long
_menu_popup(PROC_ARRAY *proc, MENU *m1, short x, short y, MENU *m2)
{
	proc->gem.addr_in[0] = (long)m1;
	proc->gem.addr_in[1] = (long)m2;
	proc->gem.int_in[0] = x;
	proc->gem.int_in[1] = y;

	return _aes(proc, 36);
}

long
_menu_register(PROC_ARRAY *proc, short id, char *name)
{
	proc->gem.int_in[0] = id;
	proc->gem.addr_in[0] = (long)name;

	return _aes(proc, 35);
}

long
_objc_edit(PROC_ARRAY *proc, OBJECT *tree, short edob, short edchar, short idx, short mode)
{
	proc->gem.addr_in[0] = (long)tree;
	proc->gem.int_in[0] = edob;
	proc->gem.int_in[1] = edchar;
	proc->gem.int_in[2] = idx;
	proc->gem.int_in[3] = mode;

	return _aes(proc, 46);
}

long
_objc_change(PROC_ARRAY *proc, OBJECT *tree, short ob, short *xywh, short nw, short rd)
{
	proc->gem.addr_in[0] = (long)tree;
	proc->gem.int_in[0] = ob;
	proc->gem.int_in[1] = 0;
	proc->gem.int_in[2] = xywh[0];
	proc->gem.int_in[3] = xywh[1];
	proc->gem.int_in[4] = xywh[2];
	proc->gem.int_in[5] = xywh[3];
	proc->gem.int_in[6] = nw;
	proc->gem.int_in[7] = rd;

	return _aes(proc, 47);
}

long
_objc_find(PROC_ARRAY *proc, OBJECT *tree, short ob, short depth, short mx, short my)
{
	proc->gem.addr_in[0] = (long)tree;
	proc->gem.int_in[0] = ob;
	proc->gem.int_in[1] = depth;
	proc->gem.int_in[2] = mx;
	proc->gem.int_in[3] = my;

	return _aes(proc, 43);
}

long
_objc_draw(PROC_ARRAY *proc, OBJECT *tree, short ob, short dp, short *xywh)
{
	proc->gem.addr_in[0] = (long)tree;
	proc->gem.int_in[0] = ob;
	proc->gem.int_in[1] = dp;
	proc->gem.int_in[2] = xywh[0];
	proc->gem.int_in[3] = xywh[1];
	proc->gem.int_in[4] = xywh[2];
	proc->gem.int_in[5] = xywh[3];

	return _aes(proc, 42);
}

long
_objc_offset(PROC_ARRAY *proc, OBJECT *tree, short obj)
{
	proc->gem.int_in[0] = obj;
	proc->gem.addr_in[0] = (long)tree;

	return _aes(proc, 44);
}

long
_rsrc_load(PROC_ARRAY *proc, char *name)
{
	proc->gem.addr_in[0] = (long)name;

	return _aes(proc, 110);
}

long
_rsrc_rcfix(PROC_ARRAY *proc, char *buf)
{
	proc->gem.addr_in[0] = (long)buf;

	return _aes(proc, 115);
}

long
_shel_help(PROC_ARRAY *proc, short mode, char *file, char *key)
{
	proc->gem.int_in[0] = mode;
	proc->gem.addr_in[0] = (long)file;
	proc->gem.addr_in[1] = (long)key;

	return _aes(proc, 128);
}

long
_shel_write(PROC_ARRAY *proc, short wd, short wg, short wc, char *cmd, char *tail)
{
	proc->gem.int_in[0] = wd;
	proc->gem.int_in[1] = wg;
	proc->gem.int_in[2] = wc;

	proc->gem.addr_in[0] = (long)cmd;
	proc->gem.addr_in[1] = (long)tail;

	return _aes(proc, 121);
}

long
_wind_get(PROC_ARRAY *proc, short w, short fn)
{
	proc->gem.int_in[0] = w;
	proc->gem.int_in[1] = fn;

	return _aes(proc, 104);
}

long
_wind_set(PROC_ARRAY *proc, short w, short fn)
{
	proc->gem.int_in[0] = w;
	proc->gem.int_in[1] = fn;

	return _aes(proc, 105);
}

long
_wind_calc(PROC_ARRAY *proc, short type, short gadgets, short *xywh)
{
	proc->gem.int_in[0] = type;
	proc->gem.int_in[1] = gadgets;
	proc->gem.int_in[2] = xywh[0];
	proc->gem.int_in[3] = xywh[1];
	proc->gem.int_in[4] = xywh[2];
	proc->gem.int_in[5] = xywh[3];

	return _aes(proc, 108);
}

long
_wind_create(PROC_ARRAY *proc, short gadgets, short *xywh)
{
	proc->gem.int_in[0] = gadgets;
	proc->gem.int_in[1] = xywh[0];
	proc->gem.int_in[2] = xywh[1];
	proc->gem.int_in[3] = xywh[2];
	proc->gem.int_in[4] = xywh[3];

	return _aes(proc, 100);
}

long
_wind_open(PROC_ARRAY *proc, short handle, short *xywh)
{
	proc->gem.int_in[0] = handle;
	proc->gem.int_in[1] = xywh[0];
	proc->gem.int_in[2] = xywh[1];
	proc->gem.int_in[3] = xywh[2];
	proc->gem.int_in[4] = xywh[3];

	return _aes(proc, 101);
}

long
_wind_close(PROC_ARRAY *proc, short handle)
{
	proc->gem.int_in[0] = handle;

	return _aes(proc, 102);
}

long
_wind_delete(PROC_ARRAY *proc, short handle)
{
	proc->gem.int_in[0] = handle;

	return _aes(proc, 103);
}

long
_wind_find(PROC_ARRAY *proc, short mx, short my)
{
	proc->gem.int_in[0] = mx;
	proc->gem.int_in[1] = my;

	return _aes(proc, 106);
}

long
_wind_update(PROC_ARRAY *proc, short mode)
{
	proc->gem.int_in[0] = mode;

	return _aes(proc, 107);
}

/* EOF */

/*
 *  $Id$
 */

#include "mt_gem.h"
#include "gem.h"

#ifdef appl_bvset
#undef appl_bvset
#endif
short
appl_bvset(short bvdisk, short bvhard)
{
	return(mt_appl_bvset(bvdisk, bvhard, aes_global));
}

#ifdef appl_control
#undef appl_control
#endif
short
appl_control(short ap_cid, short ap_cwhat, void *ap_cout)
{
	return(mt_appl_control(ap_cid,ap_cwhat,ap_cout, aes_global));
}

#ifdef appl_exit
#undef appl_exit
#endif
short
appl_exit(void)
{
	return(mt_appl_exit(aes_global));
}

#ifdef appl_find
#undef appl_find
#endif
short
appl_find(const char *name)
{
	return(mt_appl_find(name, aes_global));
}

#ifdef appl_getinfo
#undef appl_getinfo
#endif
short
appl_getinfo(short type, short *out1, short *out2, short *out3, short *out4)
{
	return(mt_appl_getinfo(type,out1, out2, out3, out4, aes_global));
}

/* for backward compatibility with gemlib 42 */
#ifdef appl_xgetinfo
#undef appl_xgetinfo
#endif
short 
appl_xgetinfo(short type, short *out1, short *out2, short *out3, short *out4)
{
	return(mt_appl_getinfo(type,out1, out2, out3, out4, aes_global));
}

#ifdef appl_init
#undef appl_init
#endif
short
appl_init(void)
{
	gl_apid = mt_appl_init(aes_global);
	gl_ap_version = aes_global[0];
	return gl_apid;
}

#ifdef appl_read
#undef appl_read
#endif
short
appl_read(short ap_id, short length, void *ap_pbuff)
{
	return(mt_appl_read(ap_id, length, ap_pbuff, aes_global));
}

#ifdef appl_search
#undef appl_search
#endif
short
appl_search(short mode, char *fname, short *type, short *ap_id)
{
	return(mt_appl_search( mode, fname, type, ap_id, aes_global));
}

#ifdef appl_tplay
#undef appl_tplay
#endif
short
appl_tplay(void *mem, short num, short scale)
{
	return(mt_appl_tplay(mem, num, scale, aes_global));
}

#ifdef appl_trecord
#undef appl_trecord
#endif
short
appl_trecord(void *mem, short count)
{
	return(mt_appl_trecord(mem, count, aes_global));
}

#ifdef appl_write
#undef appl_write
#endif
short
appl_write(short ap_id, short length, void *ap_pbuff)
{
	return(mt_appl_write( ap_id, length, ap_pbuff, aes_global));
}

#ifdef appl_yield
#undef appl_yield
#endif
short
appl_yield(void)
{
	return(mt_appl_yield(aes_global));
}

#ifdef evnt_button
#undef evnt_button
#endif
short
evnt_button(short clicks, short mask, short state,
				short *mx, short *my, short *mbutton, short *kmeta)
{
	return(mt_evnt_button(clicks,mask,state,
						   mx,my,mbutton,kmeta, aes_global));
}

#ifdef evnt_dclick
#undef evnt_dclick
#endif
short evnt_dclick(short value, short sflag)
{
	return(mt_evnt_dclick(value, sflag, aes_global));
}

#ifdef evnt_keybd
#undef evnt_keybd
#endif
int evnt_keybd(void)
{
	return(mt_evnt_keybd(aes_global));
}

#ifdef evnt_mesag
#undef evnt_mesag
#endif
short evnt_mesag(short msg[])
{
	return(mt_evnt_mesag(msg, aes_global));
}

#ifdef evnt_mouse
#undef evnt_mouse
#endif
short evnt_mouse(short flag, short x, short y, short w, short h,
				 short *mx, short *my, short *mbutton, short *kmeta)
{
	return(mt_evnt_mouse(flag, x, y, w, h, mx, my, mbutton, kmeta, aes_global));
}

#ifdef evnt_multi
#undef evnt_multi
#endif
short
evnt_multi(short events, short bclicks, short bmask, short bstate,
		   short m1_leave, short m1_x, short m1_y, short m1_w, short m1_h,
		   short m2_leave, short m2_x, short m2_y, short m2_w, short m2_h,
		   short msg[], unsigned long interval,
		   short *mx, short *my,
		   short *mbutton, short *kmeta, short *kreturn, short *mbclicks)
{
	return(mt_evnt_multi(events, bclicks, bmask, bstate, m1_leave, m1_x, m1_y, m1_w, m1_h, m2_leave, m2_x, m2_y, m2_w, m2_h, msg, interval, mx, my, mbutton, kmeta, kreturn, mbclicks, aes_global));
}

#ifdef evnt_multi_fast
#undef evnt_multi_fast
#endif
short
evnt_multi_fast (const EVMULT_IN * em_in, short msg[], EVMULT_OUT * em_out)
{
	return(mt_evnt_multi_fast(em_in,msg,em_out,aes_global));
}

#ifdef evnt_timer
#undef evnt_timer
#endif
short
evnt_timer(unsigned long interval)
{
	return(mt_evnt_timer(interval, aes_global));
}

#ifdef form_alert
#undef form_alert
#endif
short
form_alert(short default_button, const char *alert_string)
{
	return (mt_form_alert(default_button,alert_string, aes_global));
}

#ifdef form_button
#undef form_button
#endif
short
form_button(OBJECT *tree, short object, short clicks, short *nextobj)
{
	return(mt_form_button(tree, object, clicks, nextobj, aes_global));
}

#ifdef form_center
#undef form_center
#endif
short
form_center(OBJECT *tree, short *cx, short *cy, short *cw, short *ch)
{
	return(mt_form_center(tree, cx, cy, cw, ch, aes_global));
}

#ifdef form_dial
#undef form_dial
#endif
short
form_dial(short mode,
		  short x1, short y1, short w1, short h1,
		  short x2, short y2, short w2, short h2)
{
	return(mt_form_dial( mode, x1, y1, w1, h1, x2, y2, w2, h2, aes_global));
}

#ifdef form_do
#undef form_do
#endif
short
form_do(OBJECT *tree, short startobj)
{
	return(mt_form_do(tree, startobj, aes_global));
}

#ifdef form_error
#undef form_error
#endif
short
form_error(short error_code)
{
	return(mt_form_error(error_code, aes_global));
}

#ifdef form_keybd
#undef form_keybd
#endif
short
form_keybd(OBJECT *tree, short object, short reserved, short key, short *nextobject, short *nextchar)
{
	return(mt_form_keybd(tree, object, reserved, key, nextobject, nextchar, aes_global));
}

#ifdef fsel_exinput
#undef fsel_exinput
#endif
short
fsel_exinput(char *path, char *file, short *exit_but, const char *title)
{
	return(mt_fsel_exinput(path, file, exit_but, title, aes_global));
}

#ifdef fsel_input
#undef fsel_input
#endif
short
fsel_input(char *path, char *file, short *exit_but)
{
	return(mt_fsel_input(path, file, exit_but,aes_global));
}

#ifdef graf_dragbox
#undef graf_dragbox
#endif
short
graf_dragbox(short  w, short  h, short sx, short sy,
			 short bx, short by, short bw, short bh, short *rx, short *ry)
{
	return(mt_graf_dragbox(w, h, sx, sy, bx, by, bw, bh, rx, ry, aes_global));
}

#ifdef graf_growbox
#undef graf_growbox
#endif
short
graf_growbox(short sx, short sy, short sw, short sh,
			 short fx, short fy, short fw, short fh)
{
	return(mt_graf_growbox( sx, sy, sw, sh, fx, fy, fw, fh, aes_global));
}

#ifdef graf_handle
#undef graf_handle
#endif
short
graf_handle(short *wcell, short *hcell, short *wbox, short *hbox)
{
	return(mt_graf_handle(wcell, hcell, wbox, hbox, aes_global));
}

#ifdef graf_watchbox
#undef graf_watchbox
#endif
short
graf_watchbox(OBJECT *tree, short object, short in_state, short out_state)
{
	return(mt_graf_watchbox(tree, object, in_state, out_state, aes_global));
}

#ifdef graf_mbox
#undef graf_mbox
#endif
short
graf_mbox(short w, short h, short sx, short sy, short dx, short dy)
{
	return(mt_graf_mbox( w, h, sx, sy, dx, dy, aes_global));
}

#ifdef graf_mkstate
#undef graf_mkstate
#endif
short
graf_mkstate(short *mx, short *my, short *mbutton, short *kmeta)
{
	return(mt_graf_mkstate(mx, my, mbutton, kmeta, aes_global));
}

#ifdef graf_mouse
#undef graf_mouse
#endif
short
graf_mouse(short shape, const MFORM *shape_addr)
{
	return(mt_graf_mouse( shape, shape_addr, aes_global));
}

#ifdef graf_rubberbox
#undef graf_rubberbox
#endif
short
graf_rubberbox(short bx, short by, short mw, short mh, short *rw, short *rh)
{
	return(mt_graf_rubberbox( bx,  by, mw, mh, rw, rh, aes_global));
}

#ifdef graf_rubbbox
#undef graf_rubbbox
#endif
short
graf_rubbbox(short bx, short by, short mw, short mh, short *rw, short *rh)
{
	return(mt_graf_rubberbox( bx,  by, mw, mh, rw, rh, aes_global));
}

#ifdef graf_rubbox
#undef graf_rubbox
#endif
short
graf_rubbox(short bx, short by, short mw, short mh, short *rw, short *rh)
{
	return(mt_graf_rubberbox( bx,  by, mw, mh, rw, rh, aes_global));
}

#ifdef graf_shrinkbox
#undef graf_shrinkbox
#endif
short
graf_shrinkbox(short fx, short fy, short fw, short fh,
			   short sx, short sy, short sw, short sh)
{
	return(mt_graf_shrinkbox( fx, fy, fw, fh, sx, sy, sw, sh, aes_global));
}

#ifdef graf_slidebox
#undef graf_slidebox
#endif
short
graf_slidebox(OBJECT *tree, short parent, short object, short direction)
{
	return(mt_graf_slidebox(tree, parent, object, direction, aes_global));
}

#ifdef menu_attach
#undef menu_attach
#endif
short
menu_attach(short me_flag, OBJECT *me_tree, short me_item, MENU *me_mdata)
{
	return(mt_menu_attach( me_flag, me_tree, me_item, me_mdata, aes_global));
}

#ifdef menu_bar
#undef menu_bar
#endif
short
menu_bar(OBJECT *me_tree, int me_mode)
{
	return(mt_menu_bar(me_tree, me_mode, aes_global));
}

#ifdef menu_click
#undef menu_click
#endif
short
menu_click(short click, short setit)
{
	return(mt_menu_click( click, setit, aes_global));
}

#ifdef menu_icheck
#undef menu_icheck
#endif
short
menu_icheck(OBJECT *me_tree, short me_item, short me_check)
{
	return(mt_menu_icheck(me_tree, me_item, me_check, aes_global));
}

#ifdef menu_ienable
#undef menu_ienable
#endif
short
menu_ienable(OBJECT *me_tree, short me_item, short me_enable)
{
	return(mt_menu_ienable(me_tree, me_item, me_enable,aes_global));
}

#ifdef menu_istart
#undef menu_istart
#endif
short
menu_istart(short me_flag, OBJECT *me_tree, short me_imenu, short me_item)
{
	return(mt_menu_istart(me_flag, me_tree, me_imenu, me_item, aes_global));
}

#ifdef menu_popup
#undef menu_popup
#endif
short
menu_popup(MENU *me_menu, short me_xpos, short me_ypos, MENU *me_mdata)
{
	return(mt_menu_popup(me_menu, me_xpos, me_ypos, me_mdata, aes_global));
}

#ifdef menu_register
#undef menu_register
#endif
short
menu_register(short ap_id, char *me_text)
{
	return(mt_menu_register(ap_id, me_text, aes_global));
}

#ifdef menu_settings
#undef menu_settings
#endif
short
menu_settings(short me_flag, MN_SET *me_values)
{
	return(mt_menu_settings(me_flag, me_values, aes_global));
}

#ifdef menu_text
#undef menu_text
#endif
short
menu_text(OBJECT *me_tree, int me_item, char *me_text)
{
	return(mt_menu_text(me_tree, me_item, me_text, aes_global));
}

#ifdef menu_tnormal
#undef menu_tnormal
#endif
short
menu_tnormal(OBJECT *me_tree, short me_item, short me_normal)
{
	return(mt_menu_tnormal(me_tree, me_item, me_normal, aes_global));
}

#ifdef menu_unregister
#undef menu_unregister
#endif
short
menu_unregister(int id)
{
	return(mt_menu_unregister(id, aes_global));
}

#ifdef objc_add
#undef objc_add
#endif
short 
objc_add(OBJECT *tree, short parent, short child)
{
	return(mt_objc_add(tree,parent,child,aes_global));
}

#ifdef objc_change
#undef objc_change
#endif
short 
objc_change(OBJECT *tree, short object, short res, short cx, short cy,
            short cw, short ch,  short new_state, short redraw)
{
	return(mt_objc_change(tree, object, res, cx, cy, cw, ch, new_state, redraw, aes_global));
}

#ifdef objc_delete
#undef objc_delete
#endif
short 
objc_delete(OBJECT *tree, short object)
{
	return(mt_objc_delete(tree, object, aes_global));
}

#ifdef objc_draw
#undef objc_draw
#endif
short 
objc_draw(OBJECT *tree, short start, short depth,
          short cx, short cy, short cw, short ch)
{
	return(mt_objc_draw(tree, start, depth, cx, cy, cw, ch, aes_global));
}

#ifdef objc_edit
#undef objc_edit
#endif
short 
objc_edit(OBJECT *tree, short object, short ch, short *index, short kind)
{
	return(mt_objc_edit(tree, object, ch, index, kind, aes_global));
}

#ifdef objc_find
#undef objc_find
#endif
short 
objc_find(OBJECT *tree, short start, short depth, short mx, short my)
{
	return(mt_objc_find(tree, start, depth, mx, my, aes_global));
}

#ifdef objc_offset
#undef objc_offset
#endif
short 
objc_offset(OBJECT *tree, short object, short *x, short *y)
{
	return(mt_objc_offset(tree, object, x, y, aes_global));
}

#ifdef objc_order
#undef objc_order
#endif
short 
objc_order(OBJECT *tree, short object, short new_pos)
{
	return(mt_objc_order(tree, object, new_pos, aes_global));
}

#ifdef objc_sysvar
#undef objc_sysvar
#endif
short 
objc_sysvar(short mode, short which, short in1, short in2,
            short *out1, short *out2)
{
	return(mt_objc_sysvar(mode, which, in1, in2, out1, out2, aes_global));
}

#ifdef rsrc_free
#undef rsrc_free
#endif
short 
rsrc_free(void)
{
	return(mt_rsrc_free(aes_global));
}

#ifdef rsrc_gaddr
#undef rsrc_gaddr
#endif
short 
rsrc_gaddr(short Type, short Index, void *Address)
{
	return( mt_rsrc_gaddr( Type, Index,Address, aes_global));
}

#ifdef rsrc_load
#undef rsrc_load
#endif
short 
rsrc_load(const char *Name)
{
	return(mt_rsrc_load(Name, aes_global));
}

#ifdef rsrc_obfix
#undef rsrc_obfix
#endif
short 
rsrc_obfix(OBJECT *Tree, short Index)
{
	return(mt_rsrc_obfix(Tree, Index, aes_global));
}

#ifdef rsrc_rcfix
#undef rsrc_rcfix
#endif
short 
rsrc_rcfix(void *rc_header)
{
	return(mt_rsrc_rcfix(rc_header, aes_global));
}

#ifdef rsrc_saddr
#undef rsrc_saddr
#endif
short 
rsrc_saddr(short Type, short Index, void *Address)
{
	return(mt_rsrc_saddr(Type, Index, Address,aes_global));
}

#ifdef scrp_clear
#undef scrp_clear
#endif
short 
scrp_clear(void)
{
	return(mt_scrp_clear(aes_global));
}

#ifdef scrp_read
#undef scrp_read
#endif
short 
scrp_read(char *Scrappath)
{
	return(mt_scrp_read(Scrappath, aes_global));
}

#ifdef scrp_write
#undef scrp_write
#endif
short 
scrp_write(const char *Scrappath)
{
	return(mt_scrp_write(Scrappath, aes_global));
}


#ifdef shel_envrn
#undef shel_envrn
#endif
short 
shel_envrn(char **result, const char *param)
{
	return(mt_shel_envrn(result,param, aes_global));
}

#ifdef shel_find
#undef shel_find
#endif
short 
shel_find(char *buf)
{
	return(mt_shel_find(buf, aes_global));
}

#ifdef shel_get
#undef shel_get
#endif
short 
shel_get(char *Buf, short Len)
{
	return(mt_shel_get(Buf, Len, aes_global));
}

#ifdef shel_help
#undef shel_help
#endif
short 
shel_help(short sh_hmode, const char *sh_hfile, const char *sh_hkey)
{
	return(mt_shel_help(sh_hmode, sh_hfile, sh_hkey, aes_global));
}

#ifdef shel_put
#undef shel_put
#endif
short 
shel_put(const char *Buf, short Len)
{
	return(mt_shel_put(Buf, Len, aes_global));
}

#ifdef shel_rdef
#undef shel_rdef
#endif
short 
shel_rdef(char *lpcmd, char *lpdir)
{
	return(mt_shel_rdef(lpcmd, lpdir, aes_global));
}

#ifdef shel_read
#undef shel_read
#endif
short 
shel_read(char *Command, char *Tail)
{
	return(mt_shel_read(Command, Tail, aes_global));
}

#ifdef shel_wdef
#undef shel_wdef
#endif
short 
shel_wdef(const char *lpcmd, const char *lpdir)
{
	return(mt_shel_wdef(lpcmd, lpdir, aes_global));
}

#ifdef shel_write
#undef shel_write
#endif
short 
shel_write(short wodex, short wisgr, short wiscr, void *cmd, char *tail)
{
	return(mt_shel_write(wodex, wisgr, wiscr, cmd, tail, aes_global));
}

#ifdef wind_calc
#undef wind_calc
#endif
short 
wind_calc(short Type, short Parts, short InX,  short InY, short InW, short InH,
          short *OutX, short *OutY, short *OutW, short *OutH)
{
	return(mt_wind_calc( Type, Parts, InX, InY, InW, InH, OutX, OutY, OutW, OutH, aes_global));
}

#ifdef wind_calc_grect
#undef wind_calc_grect
#endif
short 
wind_calc_grect(short Type, short Parts, const GRECT *In, GRECT *Out)
{
	return(mt_wind_calc_grect(Type, Parts, In, Out, aes_global));
}

#ifdef wind_close
#undef wind_close
#endif
short 
wind_close(short WindowHandle)
{
	return(mt_wind_close(WindowHandle, aes_global));
}

#ifdef wind_create
#undef wind_create
#endif
short 
wind_create(short Parts, short Wx, short Wy, short Ww, short Wh)
{
	return(mt_wind_create(Parts, Wx, Wy, Ww, Wh, aes_global));
}

#ifdef wind_create_grect
#undef wind_create_grect
#endif
short 
wind_create_grect(short Parts, const GRECT *r)
{
	return(mt_wind_create_grect( Parts, r, aes_global));
}

#ifdef wind_delete
#undef wind_delete
#endif
short 
wind_delete(short WindowHandle)
{
	return(mt_wind_delete(WindowHandle, aes_global));
}

#ifdef wind_find
#undef wind_find
#endif
short 
wind_find(short X, short Y)
{
	return(mt_wind_find( X, Y, aes_global));
}

#ifdef wind_get
#undef wind_get
#endif
short 
wind_get(short WindowHandle, short What, 
         short *W1, short *W2, short *W3, short *W4)
{
	return(mt_wind_get(WindowHandle, What, W1, W2, W3, W4, aes_global));
}

#ifdef wind_get_grect
#undef wind_get_grect
#endif
short 
wind_get_grect(short WindowHandle, short What, GRECT *r)
{
	return(mt_wind_get_grect(WindowHandle, What, r, aes_global));
}

#ifdef wind_new
#undef wind_new
#endif
short 
wind_new( void)
{
	return(mt_wind_new(aes_global));
}

#ifdef wind_open
#undef wind_open
#endif
short 
wind_open(short WindowHandle, short Wx, short Wy, short Ww, short Wh)
{
	return(mt_wind_open(WindowHandle, Wx, Wy, Ww, Wh, aes_global));
}

#ifdef wind_open_grect
#undef wind_open_grect
#endif
short 
wind_open_grect(short WindowHandle, const GRECT *r)
{
	return(mt_wind_open_grect(WindowHandle, r, aes_global));
}

#ifdef wind_set
#undef wind_set
#endif
short 
wind_set(short WindowHandle, short What, short W1, short W2, short W3, short W4)
{
	return(mt_wind_set( WindowHandle, What, W1, W2, W3, W4, aes_global));
}

#ifdef wind_set_grect
#undef wind_set_grect
#endif
short 
wind_set_grect(short WindowHandle, short What, const GRECT *r)
{
	return(mt_wind_set_grect(WindowHandle, What, r, aes_global));
}

#ifdef wind_set_str
#undef wind_set_str
#endif
short 
wind_set_str(short WindowHandle, short What, const char *str)
{
	return(mt_wind_set_str(WindowHandle, What, str, aes_global));
}

#ifdef wind_update
#undef wind_update
#endif
short 
wind_update(short Code)
{
	return(mt_wind_update(Code, aes_global));
}

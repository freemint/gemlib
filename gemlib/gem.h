/*
 *  $Id$
 */

#ifndef _GEMLIB_H_
# define _GEMLIB_H_

#ifndef _MT_GEMLIB_H_
#include <mt_gem.h>
#endif

__BEGIN_DECLS

#ifdef __GEMLIB_AES

/** @addtogroup AES
 *  @{
 */

extern short gl_apid, gl_ap_version;			/* initialized in appl_init */

/** global AES array */
extern short aes_global[];

/** AES version number */
#define	_AESversion   (aes_global[0])

/** Number of concurrent applications possible (normally 1).
    MultiTOS will return -1. */
#define	_AESnumapps   (aes_global[1])

/** Application identifier (same as mt_appl_init() return value). */
#define	_AESapid 	  (aes_global[2])

/** LONG global available for use by the application */
#define	_AESappglobal (*((long *)&aes_global[3]))

/** Pointer to the base of the resource loaded via rsrc_load(). */
#define	_AESrscfile   ((OBJECT **)(*((long *)&aes_global[5])))

/** Current maximum character used by the AES to do vst_height() prior to
    writing to the screen. This entry is only present as of AES version 0x0400.*/
#define	_AESmaxchar   (aes_global[13])

/** Current minimum character used by the AES to do vst_height() prior to
    writing to the screen. This entry is only present as of AES version 0x0400.*/
#define	_AESminchar   (aes_global[14])

/**@}*/


/** @addtogroup a_appl
 *  @{
 */
#define appl_bvset(a,b) mt_appl_bvset(a,b,aes_global)
#define appl_control(a,b,c) mt_appl_control(a,b,c,aes_global)
#define appl_exit() mt_appl_exit(aes_global)
#define appl_find(a) mt_appl_find(a,aes_global)
#define appl_getinfo(a,b,c,d,e) mt_appl_getinfo(a,b,c,d,e,aes_global)
#define appl_xgetinfo(a,b,c,d,e) mt_appl_getinfo(a,b,c,d,e,aes_global)
#define appl_getinfo_str(a,b,c,d,e) mt_appl_getinfo_str(a,b,c,d,e,aes_global)
#define appl_read(a,b,c) mt_appl_read(a,b,c,aes_global)
#define appl_search(a,b,c,d) mt_appl_search(a,b,c,d,aes_global)
#define appl_tplay(a,b,c) mt_appl_tplay(a,b,c,aes_global)
#define appl_trecord(a,b) mt_appl_trecord(a,b,aes_global)
#define appl_write(a,b,c) mt_appl_write(a,b,c,aes_global)
#define appl_yield() mt_appl_yield(aes_global)
#define appl_getcicon() mt_appl_getcicon(aes_global)
#define appl_get_cicon(a,b,c,d,e,f) mt_appl_get_cicon(a,b,c,d,e,f, aes_global)

static inline short appl_init( void) {
	gl_apid = mt_appl_init(aes_global);
	gl_ap_version = aes_global[0];
	return gl_apid;
}

/**@}*/

/** @addtogroup a_evnt
 *  @{
 */
#define evnt_button(a,b,c,d,e,f,g)		mt_evnt_button(a,b,c,d,e,f,g,aes_global)
#define evnt_dclick(a,b)				mt_evnt_dclick(a,b,aes_global)
#define evnt_keybd()					mt_evnt_keybd(aes_global)
#define evnt_mesag(a)					mt_evnt_mesag(a,aes_global)
#define evnt_mouse(a,b,c,d,e,f,g,h,i)	mt_event_mouse(a,b,c,d,e,f,g,h,i,aes_global)
#define evnt_multi(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v) \
										mt_evnt_multi(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,aes_global)
#define evnt_multi_fast(a,b,c)			mt_evnt_multi_fast(a,b,c,aes_global)
#define evnt_timer(a)					mt_evnt_timer(a,aes_global)
/**@}*/

/** @addtogroup a_form
 *  @{
 */
#define form_alert(a,b) mt_form_alert(a,b,aes_global)
#define form_button(a,b,c,d) mt_form_button(a,b,c,d,aes_global)
#define form_center(a, b,c,d,e) mt_form_center(a,b,c,d,e,aes_global)
#define form_center_grect(a,b) mt_form_center_grect(a,b,aes_global)
#define form_dial(a, b,c,d,e, f,g,h,i) mt_form_dial(a,b,c,d,e,f,g,h,i,aes_global)
#define form_do(a,b) mt_form_do(a,b,aes_global)
#define form_error(a) mt_form_error(a,aes_global)
#define form_keybd(a, b,c,d,e,f) mt_form_keybd(a,b,c,d,e,f,aes_global)
/**@}*/

/** @addtogroup a_fsel
 *  @{
 */
#define fsel_exinput(a,b,c,d)		mt_fsel_exinput(a,b,c,d,aes_global)
#define fsel_input(a,b,c)			mt_fsel_input(a,b,c,aes_global)
#define fsel_boxinput(a,b,c,d,e)	mt_fsel_exinput(a,b,c,d,e,aes_global)
/**@}*/

/** @addtogroup a_graf
 *  @{
 */
#define graf_dragbox(a,b,c,d,e,f,g,h,i,j)	mt_graf_dragbox(a,b,c,d,e,f,g,h,i,j,aes_global)
#define graf_growbox(a,b,c,d, e,f,g,h)		mt_graf_growbox(a,b,c,d,e,f,g,h,aes_global)
#define graf_growbox_grect(a,b)				mt_graf_growbox_grect(a,b,aes_global)
#define graf_handle(a,b,c,d)				mt_graf_handle(a,b,c,d,aes_global)
#define graf_xhandle(a,b,c,d,e)				mt_graf_xhandle(a,b,c,d,e,aes_global)
#define graf_mbox(a,b,c,d,e,f)				mt_graf_mbox(a,b,c,d,e,f,aes_global)
#define graf_mkstate(a,b,c,d)				mt_graf_mkstate(a,b,c,d,aes_global)
#define graf_mouse(a,b)						mt_graf_mouse(a,b,aes_global)
#define graf_rubberbox(a,b,c,d,e,f)			mt_graf_rubberbox(a,b,c,d,e,f,aes_global)
#define graf_multirubber(a,b,c,d,e,f,g)		mt_graf_multirubber(a,b,c,d,e,f,g,aes_global)
#define graf_shrinkbox(a,b,c,d,e,f,g,h)		mt_graf_shrinkbox(a,b,c,d,e,f,g,h,aes_global)
#define graf_shrinkbox_grect(a,b)			mt_graf_shrinkbox_grect(a,b,aes_global)
#define graf_slidebox(a,b,c,d)				mt_graf_slidebox(a,b,c,d,aes_global)
#define graf_watchbox(a,b,c,d)				mt_graf_watchbox(a,b,c,d,aes_global)
#define graf_wwatchbox(a,b,c,d,e)			mt_graf_wwatchbox(a,b,c,d,e,aes_global)

/* the old names */
#define graf_movebox(a,b,c,d,e,f) mt_graf_mbox(a,b,c,d,e,f,aes_global)
#define graf_rubbbox(a,b,c,d,e,f) mt_graf_rubberbox(a,b,c,d,e,f,aes_global)
#define graf_rubbox(a,b,c,d,e,f)  mt_graf_rubberbox(a,b,c,d,e,f,aes_global)
/**@}*/

/** @addtogroup a_menu
 *  @{
 */
#define menu_attach(a,b,c,d)	mt_menu_attach(a,b,c,d,aes_global)
#define menu_bar(a,b)			mt_menu_bar(a,b,aes_global)
#define menu_click(a,b)			mt_menu_click(a,b,aes_global)
#define menu_icheck(a,b,c)		mt_menu_icheck(a,b,c,aes_global)
#define menu_ienable(a,b,c)		mt_menu_ienable(a,b,c,aes_global)
#define menu_istart(a,b,c,d)	mt_menu_istart(a,b,c,d,aes_global)
#define menu_popup(a,b,c,d)		mt_menu_popup(a,b,c,d,aes_global)
#define menu_register(a,b)		mt_menu_register(a,b,aes_global)
#define menu_settings(a,b)		mt_menu_settings(a,b,aes_global)
#define menu_text(a,b,c)		mt_menu_text(a,b,c,aes_global)
#define menu_tnormal(a,b,c)		mt_menu_tnormal(a,b,c,aes_global)
#define menu_unregister(a)		mt_menu_unregister(a,aes_global)
/**@}*/

/** @addtogroup a_objc
 *  @{
 */
#define objc_add(a,b,c)					mt_objc_add(a,b,c,aes_global)
#define objc_change(a,b,c,d,e,f,g,h,i)	mt_objc_change(a,b,c,d,e,f,g,h,i,aes_global)
#define objc_delete(a,b)				mt_objc_delete(a,b,aes_global)
#define objc_draw(a,b,c,d,e,f,g)		mt_objc_draw(a,b,c,d,e,f,g,aes_global)
#define objc_draw_grect(a,b,c,d)		mt_objc_draw_grect(a,b,c,d,aes_global)
#define objc_edit(a,b,c,d,e)			mt_objc_edit(a,b,c,d,e,aes_global)
#define objc_find(a,b,c,d,e)			mt_objc_find(a,b,c,d,e,aes_global)
#define objc_xfind(a,b,c,d,e)			mt_objc_xfind(a,b,c,d,e,aes_global)
#define objc_offset(a,b,c,d)			mt_objc_offset(a,b,c,d,aes_global)
#define objc_order(a,b,c)				mt_objc_order(a,b,c,aes_global)
#define objc_sysvar(a,b,c,d,e,f)		mt_objc_sysvar(a,b,c,d,e,f,aes_global)
/**@}*/

/** @addtogroup a_rsrc
 *  @{
 */
#define rsrc_free() mt_rsrc_free(aes_global)
#define rsrc_gaddr(a,b,c) mt_rsrc_gaddr(a,b,c,aes_global)
#define rsrc_load(a) mt_rsrc_load(a,aes_global)
#define rsrc_obfix(a,b) mt_rsrc_obfix(a,b,aes_global)
#define rsrc_rcfix(a) mt_rsrc_rcfix(a,aes_global)
#define rsrc_saddr(a,b,c) mt_rsrc_saddr(a,b,c,aes_global)
/**@}*/

/** @addtogroup a_scrp
 *  @{
 */
#define scrp_clear() mt_scrp_clear(aes_global)
#define scrp_read(a) mt_scrp_read(a,aes_global)
#define scrp_write(a) mt_scrp_write(a,aes_global)
/**@}*/

/** @addtogroup a_shel
 *  @{
 */
#define shel_envrn(a,b) mt_shel_envrn(a,b,aes_global)
#define shel_find(a) mt_shel_find(a,aes_global)
#define shel_get(a,b) mt_shel_get(a,b,aes_global)
#define shel_help(a,b,c) mt_shel_help(a,b,c,aes_global)
#define shel_put(a,b) mt_shel_put(a,b,aes_global)
#define shel_rdef(a,b) mt_shel_rdef(a,b,aes_global)
#define shel_read(a,b) mt_shel_read(a,b,aes_global)
#define shel_wdef(a,b) mt_shel_wdef(a,b,aes_global)
#define shel_write(a,b,c,d,e) mt_shel_write(a,b,c,d,e,aes_global)
/**@}*/

/** @addtogroup a_wind
 *  @{
 */
#define wind_calc(a,b,c,d,e,f,g,h,i,j) mt_wind_calc(a,b,c,d,e,f,g,h,i,j,aes_global)	
#define wind_close(a) mt_wind_close(a,aes_global)
#define wind_create(a,b,c,d,e) mt_wind_create(a,b,c,d,e,aes_global)
#define wind_delete(a) mt_wind_delete(a,aes_global)
#define wind_draw(a,b) mt_wind_draw(a,b,aes_global)
#define wind_find(a,b) mt_wind_find(a,b,aes_global)
#define wind_get(a,b,c,d,e,f) mt_wind_get(a,b,c,d,e,f,aes_global) 
#define wind_new() mt_wind_new(aes_global)
#define wind_open(a,b,c,d,e) mt_wind_open(a,b,c,d,e,aes_global)
#define wind_set(a,b,c,d,e,f) mt_wind_set(a,b,c,d,e,f,aes_global)
#define wind_update(a) mt_wind_update(a,aes_global)

/*
 * Some useful extensions
 */
#define wind_calc_grect(a,b,c,d) mt_wind_calc_grect(a,b,c,d,aes_global)  
#define wind_create_grect(a,b) mt_wind_create_grect(a,b,aes_global)
#define wind_xcreate_grect(a,b,c) mt_wind_xcreate_grect(a,b,c,aes_global)
#define wind_get_grect(a,b,c) mt_wind_get_grect(a,b,c,aes_global)
#define wind_xget_grect(a,b,c,d) mt_wind_xget_grect(a,b,c,d,aes_global)
#define wind_open_grect(a,b) mt_wind_open_grect(a,b,aes_global)
#define wind_set_grect(a,b,c) mt_wind_set_grect(a,b,c,aes_global)
#define wind_xset_grect(a,b,c,d) mt_wind_xset_grect(a,b,c,d,aes_global)
#define wind_set_str(a,b,c) mt_wind_set_str(a,b,c,aes_global)
/**@}*/


#endif /* AES */


__END_DECLS

#endif /* _GEMLIB_H_ */

/*
 * gemx.h - main header file for new gem-lib extensions
 *
 * This lib contains all GEM extensions of MagiC and NVDI/FSM/Speedo
 *
 */

/**@file
 * GEMlib header for non-multithread AES extended functions
 */

#ifndef _GEMLIB_X_H_
#define _GEMLIB_X_H_

#ifndef _GEMLIB_H_
#include <gem.h>
#endif

#ifndef _MT_GEMLIB_X_H_
#include <mt_gemx.h>
#endif

__BEGIN_DECLS


/** @addtogroup a_evnt
 *  @{
 */
/** single-thread version of mt_EVNT_multi() */
#define EVNT_multi(a,b,c,d,e,f,g,h)		mt_EVNT_multi(a,b,c,d,e,f,g,h,aes_global)
/**@}*/


/** @addtogroup a_form
 *  @{
 */
/** single-thread version of mt_form_popup() */
#define form_popup(a,b,c)				mt_form_popup(a,b,c,aes_global)
/** single-thread version of mt_form_wbutton() */
#define form_wbutton(a,b,c,d,e)			mt_form_wbutton(a,b,c,d,e,aes_global)
/** single-thread version of mt_form_wkeybd() */
#define form_wkeybd(a,b,c,d,e,f,g)		mt_form_wkeybd(a,b,c,d,e,f,g,aes_global)
/** single-thread version of mt_form_xdial() */
#define form_xdial(a,b,c,d,e,f,g,h,i,j)	mt_form_xdial(a,b,c,d,e,f,g,h,i,j,aes_global)
/** single-thread version of mt_form_xdial_grect() */
#define form_xdial_grect(a,b,c,d)		mt_form_xdial_grect(a,b,c,d,aes_global)
/** single-thread version of mt_form_xdo() */
#define form_xdo(a,b,c,d,e)				mt_form_xdo(a,b,c,d,e,aes_global)
/** single-thread version of mt_form_xerr() */
#define form_xerr(a,b)					mt_form_xerr(a,b,aes_global)
/** single-thread version of mt_xfrm_popup() */
#define xfrm_popup(a,b,c,d,e,f,g,h,i)	mt_xfrm_popup(a,b,c,d,e,f,g,h,i,aes_global)
/**@}*/

/** @addtogroup a_form
 *  @{
 */
/** single-thread version of mt_objc_wchange() */
#define objc_wchange(a,b,c,d,e)	mt_objc_wchange(a,b,c,d,e,aes_global)
/** single-thread version of mt_objc_wdraw() */
#define objc_wdraw(a,b,c,d,e)	mt_objc_wdraw(a,b,c,d,e,aes_global)
/** single-thread version of mt_objc_wedit() */
#define objc_wedit(a,b,c,d,e,f)	mt_objc_wedit(a,b,c,d,e,f,aes_global)
/** single-thread version of mt_objc_xedit() */
#define objc_xedit(a,b,c,d,e,f)	mt_objc_xedit(a,b,c,d,e,f,aes_global)
/**@}*/


/** @addtogroup x_fnts
 *  @{
 */
/** single-thread version of mt_fnts_add() */
#define fnts_add(a,b)				mt_fnts_add(a,b,aes_global)
/** single-thread version of mt_fnts_close() */
#define fnts_close(a,b,c)			mt_fnts_close(a,b,c,aes_global)
/** single-thread version of mt_fnts_create() */
#define fnts_create(a,b,c,d,e,f)	mt_fnts_create(a,b,c,d,e,f,aes_global)
/** single-thread version of mt_fnts_delete() */
#define fnts_delete(a,b)			mt_fnts_delete(a,b,aes_global)
/** single-thread version of mt_fnts_do() */
#define fnts_do(a,b,c,d,e,f,g,h,i)	mt_fnts_do(a,b,c,d,e,f,g,h,i,aes_global)
/** single-thread version of mt_fnts_evnt() */
#define fnts_evnt(a,b,c,d,e,f,g)	mt_fnts_evnt(a,b,c,d,e,f,g,aes_global)
/** single-thread version of mt_fnts_get_info() */
#define fnts_get_info(a,b,c,d)		mt_fnts_get_info(a,b,c,d,aes_global)
/** single-thread version of mt_fnts_get_name() */
#define fnts_get_name(a,b,c,d,e)	mt_fnts_get_name(a,b,c,d,e,aes_global)
/** single-thread version of mt_fnts_get_no_styles() */
#define fnts_get_no_styles(a,b)		mt_fnts_get_no_styles(a,b,aes_global)
/** single-thread version of mt_fnts_get_style() */
#define fnts_get_style(a,b,c)		mt_fnts_get_style(a,b,c,aes_global)
/** single-thread version of mt_fnts_open() */
#define fnts_open(a,b,c,d,e,f,g)	mt_fnts_open(a,b,c,d,e,f,g,aes_global)
/** single-thread version of mt_fnts_remove() */
#define fnts_remove(a)				mt_fnts_remove(a,aes_global)
/** single-thread version of mt_fnts_update() */
#define fnts_update(a,b,c,d,e)		mt_fnts_update(a,b,c,d,e,aes_global)
/**@}*/

/** @addtogroup x_fslx
 *  @{
 */
/** single-thread version of mt_fslx_close() */
#define fslx_close(a)							mt_fslx_close(a,aes_global)
/** single-thread version of mt_fslx_do() */
#define fslx_do(a,b,c,d,e,f,g,h,i,j,k,l,m)		mt_fslx_do(a,b,c,d,e,f,g,h,i,j,k,l,m,aes_global)
/** single-thread version of mt_fslx_evnt() */
#define fslx_evnt(a,b,c,d,e,f,g,h)				mt_fslx_evnt(a,b,c,d,e,f,g,h,aes_global)
/** single-thread version of mt_fslx_getnxtfile() */
#define fslx_getnxtfile(a,b)					mt_fslx_getnxtfile(a,b,aes_global)
/** single-thread version of mt_fslx_open() */
#define fslx_open(a,b,c,d,e,f,g,h,i,j,k,l,m)	mt_fslx_open(a,b,c,d,e,f,g,h,i,j,k,l,m,aes_global)
/** single-thread version of mt_fslx_set_flags() */
#define fslx_set_flags(a,b)						mt_fslx_set_flags(a,b,aes_global)
/**@}*/

/** @addtogroup x_pdlg
 *  @{
 */
/** single-thread version of mt_pdlg_add_printers() */
#define pdlg_add_printers(a,b)			mt_pdlg_add_printers(a,b,aes_global)
/** single-thread version of mt_pdlg_add_sub_dialogs() */
#define pdlg_add_sub_dialogs(a,b)		mt_pdlg_add_sub_dialogs(a,b,aes_global)
/** single-thread version of mt_pdlg_close() */
#define pdlg_close(a,b,c)				mt_pdlg_close(a,b,c,aes_global)
/** single-thread version of mt_pdlg_create() */
#define pdlg_create(a)					mt_pdlg_create(a,aes_global)
/** single-thread version of mt_pdlg_delete() */
#define pdlg_delete(a)					mt_pdlg_delete(a,aes_global)
/** single-thread version of mt_pdlg_dflt_settings() */
#define pdlg_dflt_settings(a,b)			mt_pdlg_dflt_settings(a,b,aes_global)
/** single-thread version of mt_pdlg_do() */
#define pdlg_do(a,b,c,d)				mt_pdlg_do(a,b,c,d,aes_global)
/** single-thread version of mt_pdlg_evnt() */
#define pdlg_evnt(a,b,c,d)				mt_pdlg_evnt(a,b,c,d,aes_global)
/** single-thread version of mt_pdlg_free_settings() */
#define pdlg_free_settings(a)			mt_pdlg_free_settings(a,aes_global)
/** single-thread version of mt_pdlg_get_setsize() */
#define pdlg_get_setsize()				mt_pdlg_get_setsize(aes_global)
/** single-thread version of mt_pdlg_new_settings() */
#define pdlg_new_settings(a)			mt_pdlg_new_settings(a,aes_global)
/** single-thread version of mt_pdlg_open() */
#define pdlg_open(a,b,c,d,e,f)			mt_pdlg_open(a,b,c,d,e,f,aes_global)
/** single-thread version of mt_pdlg_remove_printers() */
#define pdlg_remove_printers(a)			mt_pdlg_remove_printers(a,aes_global)
/** single-thread version of mt_pdlg_remove_sub_dialogs() */
#define pdlg_remove_sub_dialogs(a)		mt_pdlg_remove_sub_dialogs(a,aes_global)
/** single-thread version of mt_pdlg_save_default_settings() */
#define pdlg_save_default_settings(a,b)	mt_pdlg_save_default_settings(a,b,aes_global)
/** single-thread version of mt_pdlg_update() */
#define pdlg_update(a,b)				mt_pdlg_update(a,b,aes_global)
/** single-thread version of mt_pdlg_use_settings() */
#define pdlg_use_settings(a,b)			mt_pdlg_use_settings(a,b,aes_global)
/** single-thread version of mt_pdlg_validate_settings() */
#define pdlg_validate_settings(a,b)		mt_pdlg_validate_settings(a,b,aes_global)
/**@}*/

/** @addtogroup x_lbox
 *  @{
 */
/** single-thread version of mt_lbox_create() */
#define lbox_create(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p) \
									mt_lbox_create(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,aes_global)
/** single-thread version of mt_lbox_update() */
#define lbox_update(a,b)			mt_lbox_update(a,b,aes_global)
/** single-thread version of mt_lbox_do() */
#define lbox_do(a,b)				mt_lbox_do(a,b,aes_global)
/** single-thread version of mt_lbox_delete() */
#define lbox_delete(a)				mt_lbox_delete(a,aes_global)
/** single-thread version of mt_lbox_cnt_items() */
#define lbox_cnt_items(a)			mt_lbox_cnt_items(a,aes_global)
/** single-thread version of mt_lbox_get_tree() */
#define lbox_get_tree(a)			mt_lbox_get_tree(a,aes_global)
/** single-thread version of mt_lbox_get_visible() */
#define lbox_get_avis(a)			mt_lbox_get_visible(a,aes_global)
/** single-thread version of mt_lbox_get_udata() */
#define lbox_get_udata(a)			mt_lbox_get_udata(a,aes_global)
/** single-thread version of mt_lbox_get_afirst() */
#define lbox_get_afirst(a)			mt_lbox_get_afirst(a,aes_global)
/** single-thread version of mt_lbox_get_slct_idx() */
#define lbox_get_slct_idx(a)		mt_lbox_get_slct_idx(a,aes_global)
/** single-thread version of mt_lbox_get_items() */
#define lbox_get_items(a)			mt_lbox_get_items(a,aes_global)
/** single-thread version of mt_lbox_get_item() */
#define lbox_get_item(a,b)			mt_lbox_get_item(a,b,aes_global)
/** single-thread version of mt_lbox_get_slct_item() */
#define lbox_get_slct_item(a)		mt_lbox_get_slct_item(a,aes_global)
/** single-thread version of mt_lbox_get_idx() */
#define lbox_get_idx(a,b)			mt_lbox_get_idx(a,b,aes_global)
/** single-thread version of mt_lbox_get_bvis() */
#define lbox_get_bvis(a)			mt_lbox_get_bvis(a,aes_global)
/** single-thread version of mt_lbox_get_bentries() */
#define lbox_get_bentries(a)		mt_lbox_get_bentries(a,aes_global)
/** single-thread version of mt_lbox_get_bfirst() */
#define lbox_get_bfirst(a)			mt_lbox_get_bfirst(a,aes_global)
/** single-thread version of mt_lbox_set_asldr() */
#define lbox_set_asldr(a,b,c)		mt_lbox_set_asldr(a,b,c,aes_global)
/** single-thread version of mt_lbox_set_items() */
#define lbox_set_items(a,b)			mt_lbox_set_items(a,b,aes_global)
/** single-thread version of mt_lbox_free_items() */
#define lbox_free_items(a)			mt_lbox_free_items(a,aes_global)
/** single-thread version of mt_lbox_free_list() */
#define lbox_free_list(a)			mt_lbox_free_list(a,aes_global)
/** single-thread version of mt_lbox_ascroll_to() */
#define lbox_ascroll_to(a,b,c,d)	mt_lbox_ascroll_to(a,b,c,d,aes_global)
/** single-thread version of mt_lbox_set_bsldr() */
#define lbox_set_bsldr(a,b,c)		mt_lbox_set_bsldr(a,b,c,aes_global)
/** single-thread version of mt_lbox_set_bentries() */
#define lbox_set_bentries(a,b)		mt_lbox_set_bentries(a,b,aes_global)
/** single-thread version of mt_lbox_bscroll_to() */
#define lbox_bscroll_to(a,b,c,d)	mt_lbox_bscroll_to(a,b,c,d,aes_global)
/* #defines for listboxes with only one slider */
/** single-thread version of mt_lbox_get_visible() */
#define	lbox_get_visible(a)			mt_lbox_get_visible(a,aes_global)
/** single-thread version of mt_lbox_get_afirst() */
#define	lbox_get_first(a)			mt_lbox_get_afirst(a,aes_global)
/** single-thread version of mt_lbox_set_asldr() */
#define	lbox_set_slider(a,b,c)		mt_lbox_set_asldr(a,b,c,aes_global)
/** single-thread version of mt_lbox_ascroll_to() */
#define	lbox_scroll_to(a,b,c,d)		mt_lbox_ascroll_to(a,b,c,d,aes_global)
/**@}*/

/** @addtogroup x_wdlg
 *  @{
 */
/** single-thread version of mt_wdlg_create() */
#define wdlg_create(a,b,c,d,e,f)	mt_wdlg_create(a,b,c,d,e,f,aes_global)
/** single-thread version of mt_wdlg_open() */
#define wdlg_open(a,b,c,d,e,f,g)	mt_wdlg_open(a,b,c,d,e,f,g,aes_global)
/** single-thread version of mt_wdlg_close() */
#define wdlg_close(a,b,c)			mt_wdlg_close(a,b,c,aes_global)
/** single-thread version of mt_wdlg_delete() */
#define wdlg_delete(a)				mt_wdlg_delete(a,aes_global)
/** single-thread version of mt_wdlg_get_tree() */
#define wdlg_get_tree(a,b,c)		mt_wdlg_get_tree(a,b,c,aes_global)
/** single-thread version of mt_wdlg_get_edit() */
#define wdlg_get_edit(a,b)			mt_wdlg_get_edit(a,b,aes_global)
/** single-thread version of mt_wdlg_get_udata() */
#define wdlg_get_udata(a)			mt_wdlg_get_udata(a,aes_global)
/** single-thread version of mt_wdlg_get_handle() */
#define wdlg_get_handle(a)			mt_wdlg_get_handle(a,aes_global)
/** single-thread version of mt_wdlg_set_edit() */
#define wdlg_set_edit(a,b)			mt_wdlg_set_edit(a,b,aes_global)
/** single-thread version of mt_wdlg_set_tree() */
#define wdlg_set_tree(a,b)			mt_wdlg_set_tree(a,b,aes_global)
/** single-thread version of mt_wdlg_set_size() */
#define wdlg_set_size(a,b)			mt_wdlg_set_size(a,b,aes_global)
/** single-thread version of mt_wdlg_set_iconify() */
#define wdlg_set_iconify(a,b,c,d,e)	mt_wdlg_set_iconify(a,b,c,d,e,aes_global)
/** single-thread version of mt_wdlg_set_uniconify() */
#define wdlg_set_uniconify(a,b,c,d)	mt_wdlg_set_uniconify(a,b,c,d,aes_global)
/** single-thread version of mt_wdlg_evnt() */
#define wdlg_evnt(a,b)				mt_wdlg_evnt(a,b,aes_global)
/** single-thread version of mt_wdlg_redraw() */
#define wdlg_redraw(a,b,c,d)		mt_wdlg_redraw(a,b,c,d,aes_global)
/**@}*/


/** @addtogroup x_edit
 *  @{
 */
/** single-thread version of mt_edit_create() */
#define edit_create()							mt_edit_create(aes_global)
/** single-thread version of mt_edit_open() */
#define edit_open(a,b)							mt_edit_open(a,b,aes_global)
/** single-thread version of mt_edit_close() */
#define edit_close(a,b) 						mt_edit_close(a,b,aes_global)
/** single-thread version of mt_edit_delete() */
#define edit_delete(a)							mt_edit_delete(a,aes_global)
/** single-thread version of mt_edit_cursor() */
#define edit_cursor(a,b,c,d)					mt_edit_cursor(a,b,c,d,aes_global)
/** single-thread version of mt_edit_evnt() */
#define edit_evnt(a,b,c,d,e)					mt_edit_evnt(a,b,c,d,e,aes_global)
/** single-thread version of mt_edit_get_buf() */
#define edit_get_buf(a,b,c,d,e) 				mt_edit_get_buf(a,b,c,d,e,aes_global)
/** single-thread version of mt_edit_set_buf() */
#define edit_set_buf(a,b,c,d)					mt_edit_set_buf(a,b,c,d,aes_global)
/** single-thread version of mt_edit_set_format() */
#define edit_set_format(a,b,c,d)				mt_edit_set_format(a,b,c,d,aes_global)
/** single-thread version of mt_edit_get_format() */
#define edit_get_format(a,b,c,d)				mt_edit_get_format(a,b,c,d,aes_global)
/** single-thread version of mt_edit_set_font() */
#define edit_set_font(a,b,c,d,e,f)				mt_edit_set_font(a,b,c,d,e,f,aes_global)
/** single-thread version of mt_edit_get_font() */
#define edit_get_font(a,b,c,d,e,f)				mt_edit_get_font(a,b,c,d,e,f,aes_global)
/** single-thread version of mt_edit_set_colour() */
#define edit_set_colour(a,b,c,d)				mt_edit_set_colour(a,b,c,d,aes_global)
/** single-thread version of mt_edit_resized() */
#define edit_resized(a,b,c,d)					mt_edit_resized(a,b,c,d,aes_global)
/** single-thread version of mt_edit_get_dirty() */
#define edit_get_dirty(a,b) 					mt_edit_get_dirty(a,b,aes_global)
/** single-thread version of mt_edit_set_dirty() */
#define edit_set_dirty(a,b,c)					mt_edit_set_dirty(a,b,c,aes_global)
/** single-thread version of mt_edit_get_sel() */
#define edit_get_sel(a,b,c,d)					mt_edit_get_sel(a,b,c,d,aes_global)
/** single-thread version of mt_edit_get_pos() */
#define edit_get_pos(a,b,c,d,e,f,g,h)			mt_edit_get_pos(a,b,c,d,e,f,g,h,aes_global)
/** single-thread version of mt_edit_set_pos() */
#define edit_set_pos(a,b,c,d,e,f,g,h)			mt_edit_set_pos(a,b,c,d,e,f,g,h,aes_global)
/** single-thread version of mt_edit_get_scrollinfo() */
#define edit_get_scrollinfo(a,b,c,d,e,f,g,h,i)	mt_edit_get_scrollinfo(a,b,c,d,e,f,g,h,i,aes_global)
/** single-thread version of mt_edit_scroll() */
#define edit_scroll(a,b,c,d,e)					mt_edit_scroll(a,b,c,d,e,aes_global)
/**@}*/

/** @addtogroup geneva
 *  @{
 */
/** single-thread version of mt_x_settings() */
#define x_settings(a,b,c) mt_x_settings(a,b,c,aes_global)
/** single-thread version of mt_x_shel_get() */
#define x_shel_get(a,b,c) mt_x_shel_get(a,b,c,aes_global)
/** single-thread version of mt_x_shel_put() */
#define x_shel_put(a,b,c) mt_x_shel_put(a,b,c,aes_global)
/** single-thread version of mt_x_wind_create() */
#define x_wind_create(a,b,c,d,e,f) mt_x_wind_create(a,b,c,d,e,f,aes_global)
/** single-thread version of mt_x_wind_calc() */
#define x_wind_calc(a,b,c,d,e,f,g,h,i,j,k) mt_x_wind_calc(a,b,c,d,e,f,g,h,i,j,k,aes_global)
/** single-thread version of mt_x_wind_tree() */
#define x_wind_tree(a,b) mt_x_wind_tree(a,b,aes_global)
/** single-thread version of mt_x_appl_flags() */
#define x_appl_flags(a,b,c) mt_x_appl_flags(a,b,c,aes_global)
/** single-thread version of mt_x_appl_font() */
#define x_appl_font(a,b,c) mt_x_appl_font(a,b,c,aes_global)
/** single-thread version of mt_x_appl_term() */
#define x_appl_term(a,b,c) mt_x_appl_term(a,b,c,aes_global)
/** single-thread version of mt_x_appl_trecord() */
#define x_appl_trecord(a,b,c,d) mt_x_appl_trecord(a,b,c,d,aes_global)
/** single-thread version of mt_x_appl_tplay() */
#define x_appl_tplay(a,b,c,d) mt_x_appl_tplay(a,b,c,d,aes_global)
/** single-thread version of mt_x_appl_sleep() */
#define x_appl_sleep(a,b) mt_x_appl_sleep(a,b,aes_global)
/** single-thread version of mt_x_form_center() */
#define x_form_center(a,b,c,d,e) mt_x_form_center(a,b,c,d,e,aes_global)
/** single-thread version of mt_x_form_error() */
#define x_form_error(a,b) mt_x_form_error(a,b,aes_global)
/** single-thread version of mt_x_form_filename() */
#define x_form_filename(a,b,c,d) mt_x_form_filename(a,b,c,d,aes_global)
/** single-thread version of mt_x_form_mouse() */
#define x_form_mouse(a,b,c,d,e,f,g) mt_x_form_mouse(a,b,c,d,e,f,g,aes_global)
/** single-thread version of mt_x_fsel_input() */
#define x_fsel_input(a,b,c,d,e,f) mt_x_fsel_input(a,b,c,d,e,f,aes_global)
/** single-thread version of mt_x_graf_blit() */
#define x_graf_blit(a,b) mt_x_graf_blit(a,b,aes_global)
/** single-thread version of mt_x_graf_rubberbox() */
#define x_graf_rubberbox(a,b,c,d,e,f,g,h) mt_x_graf_rubberbox(a,b,c,d,e,f,g,h,aes_global)
/** single-thread version of mt_x_graf_rast2rez() */
#define x_graf_rast2rez(a,b,c,d,e) mt_x_graf_rast2rez(a,b,c,d,e,aes_global)
/** single-thread version of mt_x_help() */
#define x_help(a,b,c) mt_x_help(a,b,c,aes_global)
/** single-thread version of mt_x_malloc() */
#define x_malloc(a,b) mt_x_malloc(a,b,aes_global)
/** single-thread version of mt_x_mfree() */
#define x_mfree(a) mt_x_mfree(a,aes_global)
/** single-thread version of mt_x_shrink() */
#define x_mshrink(a,b) mt_x_mshrink(a,b,aes_global)
/** single-thread version of mt_x_realloc() */
#define x_realloc(a,b) mt_x_realloc(a,b,aes_global)
/** single-thread version of mt_x_objc_edit() */
#define x_objc_edit(a,b,c,d,e,f) mt_x_objc_edit(a,b,c,d,e,f,aes_global)
/** single-thread version of mt_x_scrp_get() */
#define x_scrp_get(a,b) mt_x_scrp_get(a,b,aes_global)
/** single-thread version of mt_x_wdial_draw() */
#define x_wdial_draw(a,b,c) mt_x_wdial_draw(a,b,c,aes_global)
/** single-thread version of mt_x_wdial_change() */
#define x_wdial_change(a,b,c) mt_x_wdial_change(a,b,c,aes_global)
#ifdef __MSHORT__
/** single-thread version of mt_x_sprint() */
#define x_sprintf mt_x_x_sprintf
/** single-thread version of mt_x_sscanf() */
#define x_sscanf mt_x_sscanf
#endif

/**@}*/

__END_DECLS

#endif /* _GEMLIB_X_H_ */

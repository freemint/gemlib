/*
 *  $Id$
 *
 * gemx.h - main header file for new gem-lib extensions
 *
 * This lib contains all GEM extensions of MagiC and NVDI/FSM/Speedo
 *
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


/** @addtogroup a_form
 *  @{
 */
#define form_popup(a,b,c)				mt_form_popup(a,b,c,aes_global)
#define form_wbutton(a,b,c,d,e)			mt_form_wbutton(a,b,c,d,e,aes_global)
#define form_wkeybd(a,b,c,d,e,f,g)		mt_form_wkeybd(a,b,c,d,e,f,g,aes_global)
#define form_xdial(a,b,c,d,e,f,g,h,i,j)	mt_form_xdial(a,b,c,d,e,f,g,h,i,j,aes_global)
#define form_xdial_grect(a,b,c,d)		mt_form_xdial_grect(a,b,c,d,aes_global)
#define form_xdo(a,b,c,d,e)				mt_form_xdo(a,b,c,d,e,aes_global)
#define form_xerr(a,b)					mt_form_xerr(a,b,aes_global)
#define xfrm_popup(a,b,c,d,e,f,g,h,i)	mt_xfrm_popup(a,b,c,d,e,f,g,h,i,aes_global)
/**@}*/

/** @addtogroup a_form
 *  @{
 */
#define objc_wchange(a,b,c,d,e)	mt_objc_wchange(a,b,c,d,e,aes_global)
#define objc_wdraw(a,b,c,d,e)	mt_objc_wdraw(a,b,c,d,e,aes_global)
#define objc_wedit(a,b,c,d,e,f)	mt_objc_wedit(a,b,c,d,e,f,aes_global)
#define objc_xedit(a,b,c,d,e,f)	mt_objc_xedit(a,b,c,d,e,f,aes_global)
/**@}*/


/** @addtogroup x_fnts
 *  @{
 */
#define fnts_add(a,b)				mt_fnts_add(a,b,aes_global)
#define fnts_close(a,b,c)			mt_fnts_close(a,b,c,aes_global)
#define fnts_create(a,b,c,d,e,f)	mt_fnts_create(a,b,c,d,e,f,aes_global)
#define fnts_delete(a,b)			mt_fnts_delete(a,b,aes_global)
#define fnts_do(a,b,c,d,e,f,g,h,i)	mt_fnts_do(a,b,c,d,e,f,g,h,i,aes_global)
#define fnts_evnt(a,b,c,d,e,f,g)	mt_fnts_evnt(a,b,c,d,e,f,g,aes_global)
#define fnts_get_info(a,b,c,d)		mt_fnts_get_info(a,b,c,d,aes_global)
#define fnts_get_name(a,b,c,d,e)	mt_fnts_get_name(a,b,c,d,e,aes_global)
#define fnts_get_no_styles(a,b)		mt_fnts_get_no_styles(a,b,aes_global)
#define fnts_get_style(a,b,c)		mt_fnts_get_style(a,b,c,aes_global)
#define fnts_open(a,b,c,d,e,f,g)	mt_fnts_open(a,b,c,d,e,f,g,aes_global)
#define fnts_remove(a)				mt_fnts_remove(a,aes_global)
#define fnts_update(a,b,c,d,e)		mt_fnts_update(a,b,c,d,e,aes_global)
/**@}*/

/** @addtogroup x_fslx
 *  @{
 */
#define fslx_close(a)							mt_fslx_close(a,aes_global)
#define fslx_do(a,b,c,d,e,f,g,h,i,j,k,l,m)		mt_fslx_do(a,b,c,d,e,f,g,h,i,j,k,l,m,aes_global)
#define fslx_evnt(a,b,c,d,e,f,g,h)				mt_fslx_evnt(a,b,c,d,e,f,g,h,aes_global)
#define fslx_getnxtfile(a,b)					mt_fslx_getnxtfile(a,b,aes_global)
#define fslx_open(a,b,c,d,e,f,g,h,i,j,k,l,m)	mt_fslx_open(a,b,c,d,e,f,g,h,i,j,k,l,m,aes_global)
#define fslx_set_flags(a,b)						mt_fslx_set_flags(a,b,aes_global)
/**@}*/

/** @addtogroup x_pdlg
 *  @{
 */
#define pdlg_add_printers(a,b)			mt_pdlg_add_printers(a,b,aes_global)
#define pdlg_add_sub_dialogs(a,b)		mt_pdlg_add_sub_dialogs(a,b,aes_global)
#define pdlg_close(a,b,c)				mt_pdlg_close(a,b,c,aes_global)
#define pdlg_create(a)					mt_pdlg_create(a,aes_global)
#define pdlg_delete(a)					mt_pdlg_delete(a,aes_global)
#define pdlg_dflt_settings(a,b)			mt_pdlg_dflt_settings(a,b,aes_global)
#define pdlg_do(a,b,c,d)				mt_pdlg_do(a,b,c,d,aes_global)
#define pdlg_evnt(a,b,c,d)				mt_pdlg_evnt(a,b,c,d,aes_global)
#define pdlg_free_settings(a)			mt_pdlg_free_settings(a,aes_global)
#define pdlg_get_setsize()				mt_pdlg_get_setsize(aes_global)
#define pdlg_new_settings(a)			mt_pdlg_new_settings(a,aes_global)
#define pdlg_open(a,b,c,d,e,f)			mt_pdlg_open(a,b,c,d,e,f,aes_global)
#define pdlg_remove_printers(a)			mt_pdlg_remove_printers(a,aes_global)
#define pdlg_remove_sub_dialogs(a)		mt_pdlg_remove_sub_dialogs(a,aes_global)
#define pdlg_save_default_settings(a,b)	mt_pdlg_save_default_settings(a,b,aes_global)
#define pdlg_update(a,b)				mt_pdlg_update(a,b,aes_global)
#define pdlg_use_settings(a,b)			mt_pdlg_use_settings(a,b,aes_global)
#define pdlg_validate_settings(a,b)		mt_pdlg_validate_settings(a,b,aes_global)
/**@}*/

/** @addtogroup x_lbox
 *  @{
 */
#define lbox_create(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p) \
									mt_lbox_create(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,aes_global)
#define lbox_update(a,b)			mt_lbox_update(a,b,aes_global)
#define lbox_do(a,b)				mt_lbox_do(a,b,aes_global)
#define lbox_delete(a)				mt_lbox_delete(a,aes_global)
#define lbox_cnt_items(a)			mt_lbox_cnt_items(a,aes_global)
#define lbox_get_tree(a)			mt_lbox_get_tree(a,aes_global)
#define lbox_get_avis(a)			mt_lbox_get_visible(a,aes_global)
#define lbox_get_udata(a)			mt_lbox_get_udata(a,aes_global)
#define lbox_get_afirst(a)			mt_lbox_get_afirst(a,aes_global)
#define lbox_get_slct_idx(a)		mt_lbox_get_slct_idx(a,aes_global)
#define lbox_get_items(a)			mt_lbox_get_items(a,aes_global)
#define lbox_get_item(a,b)			mt_lbox_get_item(a,b,aes_global)
#define lbox_get_slct_item(a)		mt_lbox_get_slct_item(a,aes_global)
#define lbox_get_idx(a,b)			mt_lbox_get_idx(a,b,aes_global)
#define lbox_get_bvis(a)			mt_lbox_get_bvis(a,aes_global)
#define lbox_get_bentries(a)		mt_lbox_get_bentries(a,aes_global)
#define lbox_get_bfirst(a)			mt_lbox_get_bfirst(a,aes_global)
#define lbox_set_asldr(a,b,c)		mt_lbox_set_asldr(a,b,c,aes_global)
#define lbox_set_items(a,b)			mt_lbox_set_items(a,b,aes_global)
#define lbox_free_items(a)			mt_lbox_free_items(a,aes_global)
#define lbox_free_list(a)			mt_lbox_free_list(a,aes_global)
#define lbox_ascroll_to(a,b,c,d)	mt_lbox_ascroll_to(a,b,c,d,aes_global)
#define lbox_set_bsldr(a,b,c)		mt_lbox_set_bsldr(a,b,c,aes_global)
#define lbox_set_bentries(a,b)		mt_lbox_set_bentries(a,b,aes_global)
#define lbox_bscroll_to(a,b,c,d)	mt_lbox_bscroll_to(a,b,c,d,aes_global)
/* #defines for listboxes with only one slider */
#define	lbox_get_visible(a)			mt_lbox_get_visible(a,aes_global)
#define	lbox_get_first(a)			mt_lbox_get_afirst(a,aes_global)
#define	lbox_set_slider(a,b,c)		mt_lbox_set_asldr(a,b,c,aes_global)
#define	lbox_scroll_to(a,b,c,d)		mt_lbox_ascroll_to(a,b,c,d,aes_global)
/**@}*/

/** @addtogroup x_wdlg
 *  @{
 */
#define wdlg_create(a,b,c,d,e,f)	mt_wdlg_create(a,b,c,d,e,f,aes_global)
#define wdlg_open(a,b,c,d,e,f,g)	mt_wdlg_open(a,b,c,d,e,f,g,aes_global)
#define wdlg_close(a,b,c)			mt_wdlg_close(a,b,c,aes_global)
#define wdlg_delete(a)				mt_wdlg_delete(a,aes_global)
#define wdlg_get_tree(a,b,c)		mt_wdlg_get_tree(a,b,c,aes_global)
#define wdlg_get_edit(a,b)			mt_wdlg_get_edit(a,b,aes_global)
#define wdlg_get_udata(a)			mt_wdlg_get_udata(a,aes_global)
#define wdlg_get_handle(a)			mt_wdlg_get_handle(a,aes_global)
#define wdlg_set_edit(a,b)			mt_wdlg_set_edit(a,b,aes_global)
#define wdlg_set_tree(a,b)			mt_wdlg_set_tree(a,b,aes_global)
#define wdlg_set_size(a,b)			mt_wdlg_set_size(a,b,aes_global)
#define wdlg_set_iconify(a,b,c,d,e)	mt_wdlg_set_iconify(a,b,c,d,e,aes_global)
#define wdlg_set_uniconify(a,b,c,d)	mt_wdlg_set_uniconify(a,b,c,d,aes_global)
#define wdlg_evnt(a,b)				mt_wdlg_evnt(a,b,aes_global)
#define wdlg_redraw(a,b,c,d)		mt_wdlg_redraw(a,b,c,d,aes_global)
/**@}*/


/** @addtogroup x_edit
 *  @{
 */
#define edit_create()							mt_edit_create(aes_global)
#define edit_open(a,b)							mt_edit_open(a,b,aes_global)
#define edit_close(a,b) 						mt_edit_close(a,b,aes_global)
#define edit_delete(a)							mt_edit_delete(a,aes_global)
#define edit_cursor(a,b,c,d)					mt_edit_cursor(a,b,c,d,aes_global)
#define edit_evnt(a,b,c,d,e)					mt_edit_evnt(a,b,c,d,e,aes_global)
#define edit_get_buf(a,b,c,d,e) 				mt_edit_get_buf(a,b,c,d,e,aes_global)
#define edit_set_buf(a,b,c,d)					mt_edit_set_buf(a,b,c,d,aes_global)
#define edit_set_format(a,b,c,d)				mt_edit_set_format(a,b,c,d,aes_global)
#define edit_get_format(a,b,c,d)				mt_edit_get_format(a,b,c,d,aes_global)
#define edit_set_font(a,b,c,d,e,f)				mt_edit_set_font(a,b,c,d,e,f,aes_global)
#define edit_get_font(a,b,c,d,e,f)				mt_edit_get_font(a,b,c,d,e,f,aes_global)
#define edit_set_colour(a,b,c,d)				mt_edit_set_colour(a,b,c,d,aes_global)
#define edit_resized(a,b,c,d)					mt_edit_resized(a,b,c,d,aes_global)
#define edit_get_dirty(a,b) 					mt_edit_get_dirty(a,b,aes_global)
#define edit_set_dirty(a,b,c)					mt_edit_set_dirty(a,b,c,aes_global)
#define edit_get_sel(a,b,c,d)					mt_edit_get_sel(a,b,c,d,aes_global)
#define edit_get_pos(a,b,c,d,e,f,g,h)			mt_edit_get_pos(a,b,c,d,e,f,g,h,aes_global)
#define edit_set_pos(a,b,c,d,e,f,g,h)			mt_edit_set_pos(a,b,c,d,e,f,g,h,aes_global)
#define edit_get_scrollinfo(a,b,c,d,e,f,g,h,i)	mt_edit_get_scrollinfo(a,b,c,d,e,f,g,h,i,aes_global)
#define edit_scroll(a,b,c,d,e)					mt_edit_scroll(a,b,c,d,e,aes_global)
/**@}*/

__END_DECLS

#endif /* _GEMLIB_X_H_ */

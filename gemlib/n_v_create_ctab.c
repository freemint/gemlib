/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** 
 *
 *  @param handle Device handle
 *  @param color_space 
 *  @param px_format 
 *
 *  @return 
 *
 *  @since NVDI 5 ?
 *
 *
 *
 */

COLOR_TAB *
v_create_ctab (short handle, long color_space, unsigned long px_format)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[4];   
	short vdi_intout[N_PTRINTS];

	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_intout, vdi_dummy);
	
	vdi_intin_long(0) = color_space;
	vdi_intin_long(2) = px_format;

	VDI_TRAP_ESC (vdi_params, handle, 206,8, 0,4);

	return vdi_intout_ptr(0, COLOR_TAB *);
}

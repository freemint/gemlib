/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"
#include <stddef.h>

/** 
 *
 *  @param handle Device handle
 *  @param src_bm 
 *  @param dst_bm 
 *  @param src_rect 
 *  @param dst_rect 
 *  @param mode 
 *
 *  @since NVDI 5 ?
 *
 *
 *
 */

void
vr_transfer_bits (short handle, GCBITMAP * src_bm, GCBITMAP * dst_bm,
                  short *src_rect, short *dst_rect, short mode)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[4];   
	short vdi_ptsin[8];   

	VDI_PARAMS(vdi_control, vdi_intin, vdi_ptsin, vdi_dummy, vdi_dummy);
	
	vdi_intin[0] = mode;
	vdi_intin[1] = 0;
	vdi_intin[2] = 0;
	vdi_intin[3] = 0;

	*(GRECT*)(vdi_ptsin +0) = *(GRECT*)src_rect;
	*(GRECT*)(vdi_ptsin +4) = *(GRECT*)dst_rect;

	vdi_control_ptr(7)  = src_bm;
	vdi_control_ptr(9)  = dst_bm;
	vdi_control_ptr(11) = NULL;

	VDI_TRAP (vdi_params, handle, 170, 4,4);
}

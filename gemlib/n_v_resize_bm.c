/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** 
 *
 *  @param handle Device handle
 *  @param width 
 *  @param height 
 *  @param byte_width 
 *  @param addr 
 *
 *  @return 
 *
 *  @since NVDI 5 ?
 *
 */

short
v_resize_bm (short handle, short width, short height, long byte_width,
             unsigned char *addr)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[6];   
	short vdi_intout[1]; 

	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_intout, vdi_dummy);
	
	vdi_intin         [0] = width;
	vdi_intin         [1] = height;
	*(long*)&vdi_intin[2] = byte_width;
	vdi_intin_ptr     (4) = addr;

	VDI_TRAP_ESC (vdi_params, handle, 100,2, 0,6);
	
	return vdi_intout[0];
}

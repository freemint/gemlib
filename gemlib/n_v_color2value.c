/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** 
 *
 *  @param handle Device handle
 *  @param color_space 
 *  @param color 
 *
 *  @return 
 *
 *  @since NVDI 5 ?
 *
 *
 *
 */

unsigned long
v_color2value (short handle, long color_space, COLOR_ENTRY * color)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[6];   
	short vdi_intout[2]; 

	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_intout, vdi_dummy);
	
	*(long*)       &vdi_intin[0] = color_space;
	*(COLOR_ENTRY*)&vdi_intin[2] = *color;

	VDI_TRAP (vdi_params, handle, 204, 0,6);

	return *(unsigned long *)&vdi_intout[0];
}

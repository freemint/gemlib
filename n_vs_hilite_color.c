#include "gem_vdiP.h"
#include "mt_gemx.h"

/** 
 *
 *  @param handle Device handle
 *  @param color_space color space
 *  @param hilite_color COLOR_ENTRY of the highlighting color
 *
 *  @return -1=wrong subfunction number, 0=function not present, 1=all ok
 *
 *  @since NVDI 5 ?
 *
 *
 *
 */

short
vs_hilite_color (short handle, long color_space, COLOR_ENTRY * hilite_color)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[6];   
	short vdi_intout[1]; 

	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_intout, vdi_dummy);
	
	vdi_intin_long(0) = color_space;
	*(COLOR_ENTRY*)&vdi_intin[2] = *hilite_color;

	VDI_TRAP (vdi_params, handle, 207, 0,6);

	return vdi_intout[0];
}

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
 *  @param nearest_color  \n
 *         [option CHECK_NULLPTR] nearest_color may be NULL
 *
 *  @return 
 *
 *  @since NVDI 5 ?
 *
 *
 *
 */

long
v_color2nearest (short handle, long color_space, COLOR_ENTRY * color,
                 COLOR_ENTRY * nearest_color)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[6];   
	short vdi_intout[6]; 

	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_intout, vdi_dummy);
	
	*(long*)       &vdi_intin[0] = color_space;
	*(COLOR_ENTRY*)&vdi_intin[2] = *color;

	VDI_TRAP_ESC (vdi_params, handle, 204,2, 0,6);

#if CHECK_NULLPTR
	if (nearest_color)
#endif
	*nearest_color = *(COLOR_ENTRY*)&vdi_intout[2];
	
	return vdi_intout_long(0);
}

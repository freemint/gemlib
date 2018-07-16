/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** 
 *
 *  @param handle Device handle
 *  @param value 
 *  @param color  \n
 *         [option CHECK_NULLPTR] color may be NULL
 *
 *  @return 
 *
 *  @since NVDI 5 ?
 *
 *
 *
 */

long
v_value2color (short handle, unsigned long value, COLOR_ENTRY * color)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[6]; 
	short vdi_intin[2];

	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_intout, vdi_dummy);
	vdi_intin_long(0) = value;
	
	VDI_TRAP_ESC (vdi_params, handle, 204,1, 0,2);

#if CHECK_NULLPTR
	if (color)
#endif
	*color = *(COLOR_ENTRY*)&vdi_intout[2];
	
	return vdi_intout_long(0);
}

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
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[6]; 
	VDI_PARAMS(vdi_control, (short*)&value, 0L, vdi_intout, 0L);
#else
	*(unsigned long *)&vdi_intin[0] = value;
#endif
	
	VDI_TRAP_ESC (vdi_params, handle, 204,1, 0,2);

#if CHECK_NULLPTR
	if (color)
#endif
	*color = *(COLOR_ENTRY*)&vdi_intout[2];
	
	return vdi_intout_long(0);
}

/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "gemx.h"

/** 
 *
 *  @param handle Device handle
 *  @param value 
 *  @param color 
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
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		&value,                      /* vdi_intin   */
		0L,                          /* vdi_ptsin   */
		&vdi_intout[0],              /* vdi_intout  */
		0L                           /* vdi_ptsout  */
	};
#else
	*(unsigned long *)&vdi_intin[0] = value;
#endif
	
	VDI_TRAP_ESC (vdi_params, handle, 204,1, 0,2);

	*color = *(COLOR_ENTRY*)&vdi_intout[2];
	
	return vdi_intout_long(0);
}

/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** 
 *
 *  @param handle Device handle
 *  @param index 
 *
 *  @return 
 *
 *  @since NVDI 5 ?
 *
 *
 *
 */

unsigned long
v_ctab_idx2value (short handle, short index)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[2]; 
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		&index,                      /* vdi_intin   */
		0L,                          /* vdi_ptsin   */
		&vdi_intout[0],              /* vdi_intout  */
		0L                           /* vdi_ptsout  */
	};
#else
	vdi_intin[0] = index;
#endif
	
	VDI_TRAP_ESC (vdi_params, handle, 206,5, 0,1);

	return *(unsigned long *)&vdi_intout[0];
}

/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "gemx.h"

/** 
 *
 *  @param handle Device handle
 *  @param vdi_index 
 *
 *  @return 
 *
 *  @since NVDI 5 ?
 *
 *
 *
 */

short
v_ctab_vdi2idx (short handle, short vdi_index)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[1]; 
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		&vdi_index,                  /* vdi_intin   */
		0L,                          /* vdi_ptsin   */
		&vdi_intout[0],              /* vdi_intout  */
		0L                           /* vdi_ptsout  */
	};
#else
	vdi_intin[0] = vdi_index;
#endif
	
	VDI_TRAP_ESC (vdi_params, handle, 206,4, 0,1);

	return vdi_intout[0];
}

/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "gemx.h"

/** 
 *
 *  @param handle Device handle
 *  @param px_format 
 *
 *  @return 
 *
 *  @since NVDI 5 ?
 *
 *
 *
 */

long
vq_px_format (short handle, unsigned long *px_format)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[4]; 
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		0L,                          /* vdi_intin   */
		0L,                          /* vdi_ptsin   */
		&vdi_intout[0],              /* vdi_intout  */
		0L                           /* vdi_ptsout  */
	};
#endif
	
	VDI_TRAP_ESC (vdi_params, handle, 204,3, 0,0);

	*px_format = *(unsigned long *)&vdi_intout[2];
	
	return vdi_intout_long(0);
}

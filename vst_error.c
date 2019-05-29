#include "gem_vdiP.h"

/** 
 *
 *  @param handle Device handle
 *  @param mode type of error handling
 *  @param errorvar address of the error variable
 *
 *  @since SpeedoGDOS 4.0
 *
 *
 *
 */

void
vst_error (short handle, short mode, short *errorvar)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[1 + N_PTRINTS];
	short vdi_intout[VDI_INTOUTMAX]; /* todo (doc wanted) */
	short vdi_ptsout[VDI_PTSOUTMAX]; /* todo (doc wanted) */
	
	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_intout, vdi_ptsout );
	
	vdi_intin    [0] = mode;
	vdi_intin_ptr(1, short *) = errorvar;
	
	VDI_TRAP (vdi_params, handle, 245, 0, 1 + N_PTRINTS);
}

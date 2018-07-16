/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** This function sets the skew of vector font characters in steps of 1/10 degrees. 
 *  The skewing angle is independent from vst_effects() and must be in a range 
 *  between -90 and +90 degrees. Positive angles will lean the characters to the 
 *  left whereas negative angles will lean them to the right.
 *
 *  @param handle Device handle
 *  @param skew angle in 1/10 degrees
 *
 *  @return selected angle in 1/10 degrees
 *
 *  @since NVDI 3.00
 *
 */

short
vst_skew (short handle, short skew)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[1]; 

	VDI_PARAMS(vdi_control, &skew, 0L, vdi_intout, vdi_dummy);
	
	VDI_TRAP (vdi_params, handle, 253, 0,1);
	
	return vdi_intout[0];
}

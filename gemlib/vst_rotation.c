/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** enables text rotation in 1/10 of degrees. If the selected font 
 *  is a bitmap font, rotation works only in steps of 90 degrees
 *
 *  @param handle Device handle
 *  @param ang requested angle
 *
 *  @return realized angle
 *
 *  @since all VDI versions\n
 *         This function is not required and may
 *         not be supported on all devices. The Extended
 *         Inquire function returns the availability of
 *         this function.
 *
 */

short
vst_rotation (short handle, short ang)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[1]; 
	VDI_PARAMS(vdi_control, &ang, 0L, vdi_intout, vdi_dummy );
#else
	vdi_intin[0] = ang;
#endif
	
	VDI_TRAP (vdi_params, handle, 13, 0,1);

	return vdi_intout[0];
}

/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** switcher color calibration on or off and can be used to set 
 *  a calibration table.
 *  Before you call this function you should check if it exists (call 
 *  vq_calibrate()).
 *
 *  @param handle Device handle
 *  @param flag requested calibration off (0) or on (1)
 *  @param rgb pointer to calibration table or 0L
 *
 *  @return selected calibration off (0) or on (1)
 *
 *  @since depends on the driver
 *
 *  @note
 *  The calibration table is used for each workstation of the device driver. 
 *  Therefore the calibration should only be changed by CPX modules or accessories.
 *  
 *
 */

short
vs_calibrate (short handle, short flag, short *rgb)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[3];   
	short vdi_intout[1]; 
	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_intout, 0L );
#endif
	
	vdi_intin_ptr(0) = rgb;
	vdi_intin    [2] = flag;
	
	VDI_TRAP_ESC (vdi_params, handle, 5,76, 0,3);
	
	return vdi_intout[0];
}

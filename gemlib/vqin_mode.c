/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** inquires the input mode of the specified device
 *
 *  @param handle Device handle
 *  @param dev input device (see vsin_mode())
 *  @param mode mode
 *
 *  @since all VDI versions
 *
 */

void
vqin_mode (short handle, short dev, short *mode)
{
	short vdi_control[VDI_CNTRLMAX]; 

	VDI_PARAMS(vdi_control, &dev, 0L, mode, vdi_dummy );
		
	VDI_TRAP (vdi_params, handle, 115, 0,1);
}

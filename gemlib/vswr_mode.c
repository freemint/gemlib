/*
 *   general attribute
 */

#include "gem_vdiP.h"


short
vswr_mode (short handle, short mode)
{
	vdi_intin[0] = mode;

	VDI_TRAP (vdi_params, handle, 32, 0,1);

	return vdi_intout[0];
}

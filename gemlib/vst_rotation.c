/*
 *  text attribute
 */

#include "gem_vdiP.h"


short
vst_rotation (short handle, short ang)
{
	vdi_intin[0] = ang;

	VDI_TRAP (vdi_params, handle, 13, 0,1);

	return vdi_intout[0];
}

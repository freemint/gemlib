/*
 *  text attribute
 */

#include "gem_vdiP.h"


void
vst_scratch (short handle, short mode)
{
	vdi_intin[0] = mode;

	VDI_TRAP (vdi_params, handle, 244, 0,1);
}

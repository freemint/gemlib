/*
 *  text attribute
 */

#include "gem_vdiP.h"


void
vst_error (short handle, short mode, short *errorvar)
{
	vdi_intin[0]            = mode;
	*(short**)&vdi_intin[1] = errorvar;
	
	VDI_TRAP (vdi_params, handle, 245, 0,3);
}

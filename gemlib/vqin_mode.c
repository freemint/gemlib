#include "gem_vdiP.h"


void
vqin_mode (short handle, short dev, short *mode)
{
	vdi_intin[0] = dev;
	
	VDI_TRAP (vdi_params, handle, 115, 0,1);
	
	*mode = vdi_intout[0];
}

/*
 *   fill attribute
 */

#include "gem_vdiP.h"


void
vsf_udpat (short handle, short pat[], short planes)
{
	vdi_params.intin = pat;
	
	VDI_TRAP (vdi_params, handle, 112, planes *16,0);

	vdi_params.intin = vdi_intin;
}


#include "gem.h"


void
vsf_udpat (short handle, short pat[], short planes)
{
	vdi_control[0] = 112;
	vdi_control[1] = 0;
	vdi_control[3] = planes << 4;
	vdi_control[5] = 0;
	vdi_control[6] = handle;

	vdi_params.intin = pat;

	vdi (&vdi_params);

	vdi_params.intin = vdi_intin;
}

/*
 * * fill attribute
 */


#include "gem.h"


void
vr_trnfm (short handle, MFDB * src, MFDB * dst)
{
	*((MFDB **) (&vdi_control[7])) = src;
	*((MFDB **) (&vdi_control[9])) = dst;

	vdi_control[0] = 110;
	vdi_control[1] = 0;
	vdi_control[3] = 0;
	vdi_control[5] = 0;
	vdi_control[6] = handle;

	vdi (&vdi_params);
}

#include "gem_vdiP.h"


void
vr_trnfm (short handle, MFDB * src, MFDB * dst)
{
	*((MFDB **) (&vdi_control[7])) = src;
	*((MFDB **) (&vdi_control[9])) = dst;

	VDI_TRAP (vdi_params, handle, 110, 0,0);
}

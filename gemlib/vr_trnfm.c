#include "gem_vdiP.h"


void
vr_trnfm (short handle, MFDB * src, MFDB * dst)
{
	vdi_control_ptr(7) = src;
	vdi_control_ptr(9) = dst;

	VDI_TRAP_00 (vdi_params, handle, 110);
}

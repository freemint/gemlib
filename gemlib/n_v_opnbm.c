/*
 *   NOTE: requires EdDI version 1.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


void
v_opnbm (short *work_in, MFDB *bitmap, short *handle, short *work_out)
{
	vdi_params.intin  = &work_in[0];
	vdi_params.intout = &work_out[0];
	vdi_params.ptsout = &work_out[45];

	vdi_control_ptr(7) = bitmap;
	VDI_TRAP_ESC (vdi_params, *handle, 100,1, 0,20);

	vdi_params.intin  = vdi_intin;
	vdi_params.intout = vdi_intout;
	vdi_params.ptsout = vdi_ptsout;
	
	*handle = vdi_control[6];
}

/*
 *   special graphic funkcion
 */

#include "gem_vdiP.h"


void
v_output_window (short handle, short *pxy)
{
	vdi_params.ptsin = pxy;

	VDI_TRAP_ESC (vdi_params, handle, 5,21, 2,0);

	vdi_params.ptsin = vdi_ptsin;
}

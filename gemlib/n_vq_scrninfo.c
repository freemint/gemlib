/*
 *   NOTE: requires EdDI version 1.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


void
vq_scrninfo (short handle, short *work_out)
{
	vdi_params.intout = work_out;

	vdi_intin[0] = 2;
	
	VDI_TRAP_ESC (vdi_params, handle, 102,1, 0,1);

	vdi_params.intout = vdi_intout;
}

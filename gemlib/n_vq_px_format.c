/*
 *   NOTE: requires NVDI version 5.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


long
vq_px_format (short handle, unsigned long *px_format)
{
	VDI_TRAP_ESC (vdi_params, handle, 204,3, 0,0);

	*px_format = *(unsigned long *)&vdi_intout[2];
	
	return vdi_intout_long(0);
}

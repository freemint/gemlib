/*
 *   NOTE: requires NVDI version 3.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


void
vqt_fontheader (short handle, char *buffer, char *pathname)
{
	vdi_intin_ptr(0) = buffer;
	
	VDI_TRAP (vdi_params, handle, 232, 0,2);
	
	vdi_array2str (vdi_intout, pathname, vdi_control[4]);
}

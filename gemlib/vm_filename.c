/*
 *   metafile function
 */

#include "gem_vdiP.h"


void
vm_filename (short handle, const char *filename)
{
	register short n = vdi_str2array (filename, vdi_intin);
	
	VDI_TRAP_ESC (vdi_params, handle, 5,100, 0,n);
}

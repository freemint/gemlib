/*
 * * metafile function
 */

#include "gem_vdiP.h"


void
vm_pagesize (short handle, short pgwidth, short pgheight)
{
	vdi_intin[0] = 0;
	vdi_intin[1] = pgwidth;
	vdi_intin[2] = pgheight;
	
	VDI_TRAP_ESC (vdi_params, handle, 5,99, 0,3);
}

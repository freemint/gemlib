/*
 *   metafile function
 */

#include "gem_vdiP.h"


void
vm_coords (short handle, short llx, short lly, short urx, short ury)
{
	vdi_intin[0] = 1;
	vdi_intin[1] = llx;
	vdi_intin[2] = lly;
	vdi_intin[3] = urx;
	vdi_intin[4] = ury;
	
	VDI_TRAP_ESC (vdi_params, handle, 5,99, 0,5);
}

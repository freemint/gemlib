
#include "gem.h"


void
vm_coords (short handle, short llx, short lly, short urx, short ury)
{
	vdi_intin[0] = 1;
	vdi_intin[1] = llx;
	vdi_intin[2] = lly;
	vdi_intin[3] = urx;
	vdi_intin[4] = ury;
	vdi_control[0] = 5;
	vdi_control[1] = 0;
	vdi_control[3] = 5;
	vdi_control[5] = 99;
	vdi_control[6] = handle;
	vdi (&vdi_params);
}

/*
 * * metafile function
 */

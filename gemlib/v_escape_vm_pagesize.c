
#include "gem.h"


void
vm_pagesize (int handle, int pgwidth, int pgheight)
{
	vdi_intin[0] = 0;
	vdi_intin[1] = pgwidth;
	vdi_intin[2] = pgheight;
	vdi_control[0] = 5;
	vdi_control[1] = 0;
	vdi_control[3] = 3;
	vdi_control[5] = 99;
	vdi_control[6] = handle;
	vdi (&vdi_params);
}

/*
 * * metafile function
 */

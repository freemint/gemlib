
#include "gem.h"


void
vm_filename (short handle, const char *filename)
{
	short n;

	n = vdi_str2array (filename, vdi_intin);
	vdi_control[0] = 5;
	vdi_control[1] = 0;
	vdi_control[3] = n;
	vdi_control[5] = 100;
	vdi_control[6] = handle;
	vdi (&vdi_params);

}

/*
 * * metafile function
 */

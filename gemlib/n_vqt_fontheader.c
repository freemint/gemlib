#include "gemx.h"

/*
 * * NOTE: requires NVDI version 3.x or higher
 */

void
vqt_fontheader (short handle, char *buffer, char *pathname)
{
	*((char **) (&vdi_intin[0])) = buffer;
	vdi_control[0] = 232;
	vdi_control[1] = 0;
	vdi_control[3] = 2;
	vdi_control[5] = 0;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	vdi_array2str (vdi_intout, pathname, vdi_control[4]);
}

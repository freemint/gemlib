
#include "gem.h"


void
vs_curaddress (int handle, int row, int col)
{
	vdi_intin[0] = row;
	vdi_intin[1] = col;
	vdi_control[0] = 5;
	vdi_control[1] = 0;
	vdi_control[3] = 2;
	vdi_control[5] = 11;
	vdi_control[6] = handle;
	vdi (&vdi_params);
}

/*
 * * text function
 */

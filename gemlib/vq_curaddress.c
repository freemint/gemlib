
#include "gem.h"


void
vq_curaddress (int handle, int *cur_row, int *cur_col)
{
	vdi_control[0] = 5;
	vdi_control[1] = 0;
	vdi_control[3] = 0;
	vdi_control[5] = 15;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	*cur_row = vdi_intout[0];
	*cur_col = vdi_intout[1];
}

/*
 * * text function
 */

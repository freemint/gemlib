
#include "gem.h"


void
vq_chcells (short handle, short *n_rows, short *n_cols)
{
	vdi_control[0] = 5;
	vdi_control[1] = 0;
	vdi_control[3] = 0;
	vdi_control[5] = 1;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	*n_rows = vdi_intout[0];
	*n_cols = vdi_intout[1];
}

/*
 * * text function
 */

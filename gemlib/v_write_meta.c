
#include "gem.h"


void
v_write_meta (short handle, short numvdi_intin, short *avdi_intin, short num_ptsin,
	      short *a_ptsin)
{
	vdi_params.intin = &avdi_intin[0];
	vdi_params.ptsin = &a_ptsin[0];

	vdi_control[0] = 5;
	vdi_control[1] = num_ptsin;
	vdi_control[3] = numvdi_intin;
	vdi_control[5] = 99;
	vdi_control[6] = handle;

	vdi (&vdi_params);

	vdi_params.intin = &vdi_intin[0];
	vdi_params.ptsin = &vdi_ptsin[0];
}

/*
 * * metafile function
 */


#include "gem.h"


void
v_write_meta (int handle, int numvdi_intin, int *avdi_intin, int num_ptsin,
	      int *a_ptsin)
{
#ifdef __MSHORT__
	vdi_params.intin = (short *) &avdi_intin[0];
	vdi_params.ptsin = (short *) &a_ptsin[0];
#else
	register int i;

	for (i = 0; i < numvdi_intin; i++)
		vdi_intin[i] = avdi_intin[i];

	for (i = 0; i < num_ptsin; i++)
		vdi_ptsin[i] = a_ptsin[i];
#endif
	vdi_control[0] = 5;
	vdi_control[1] = num_ptsin;
	vdi_control[3] = numvdi_intin;
	vdi_control[5] = 99;
	vdi_control[6] = handle;
	vdi (&vdi_params);

#ifdef __MSHORT__
	vdi_params.intin = &vdi_intin[0];
	vdi_params.ptsin = &vdi_ptsin[0];
#endif
}

/*
 * * metafile function
 */

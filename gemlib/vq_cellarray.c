
#include "gem.h"


void
vq_cellarray (short handle, short pxyarray[], short row_len, short nrows,
	      short *el_used, short *rows_used, short *status, short color[])
{
	short i;

	vdi_ptsin[0] = pxyarray[0];
	vdi_ptsin[1] = pxyarray[1];
	vdi_ptsin[2] = pxyarray[2];
	vdi_ptsin[3] = pxyarray[3];
	vdi_control[7] = row_len;
	vdi_control[8] = nrows;
	vdi_control[0] = 27;
	vdi_control[1] = 2;
	vdi_control[3] = 0;
	vdi_control[5] = 0;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	for (i = 0; i < vdi_control[4]; i++)
		color[i] = vdi_intout[i];
	*el_used = vdi_control[9];
	*rows_used = vdi_control[10];
	*status = vdi_control[11];
}

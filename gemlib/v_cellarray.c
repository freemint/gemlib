
#include "gem.h"


void
v_cellarray (int handle, int pxyarray[], int row_length, int elements,
	     int nrows, int write_mode, int colarray[])
{
	short *wptr, *end;

	wptr = vdi_intin;
	end = wptr + (short) nrows *(short) elements;

	while (wptr < end)
		*wptr++ = *colarray++;

	vdi_ptsin[0] = pxyarray[0];
	vdi_ptsin[1] = pxyarray[1];
	vdi_ptsin[2] = pxyarray[2];
	vdi_ptsin[3] = pxyarray[3];

	vdi_control[0] = 10;
	vdi_control[1] = 2;
	vdi_control[3] = (int) (wptr - vdi_intin);
	vdi_control[6] = handle;
	vdi_control[7] = row_length;
	vdi_control[8] = elements;
	vdi_control[9] = nrows;
	vdi_control[10] = write_mode;
	vdi (&vdi_params);
}


#include "gem.h"


void
v_cellarray (short handle, short pxy[], short row_length, short elements,
	     short nrows, short write_mode, short colarray[])
{
	/* XXX optimize me */

	short *wptr, *end;

	wptr = vdi_intin;
	end = wptr + nrows * elements;

	while (wptr < end)
		*wptr++ = *colarray++;

	vdi_ptsin[0] = pxy[0];
	vdi_ptsin[1] = pxy[1];
	vdi_ptsin[2] = pxy[2];
	vdi_ptsin[3] = pxy[3];

	vdi_control[0] = 10;
	vdi_control[1] = 2;
	vdi_control[3] = (short) (wptr - vdi_intin);
	vdi_control[5] = 0;
	vdi_control[6] = handle;
	vdi_control[7] = row_length;
	vdi_control[8] = elements;
	vdi_control[9] = nrows;
	vdi_control[10] = write_mode;

	vdi (&vdi_params);
}

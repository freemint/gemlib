#include "gem_vdiP.h"


void
v_cellarray (short handle, short pxy[], short row_length, short elements,
             short nrows, short write_mode, short colarray[])
{
	register short n = row_length * nrows;
	
	vdi_params.intin = colarray;
	vdi_params.ptsin = pxy;
	
	vdi_control[7]  = row_length;
	vdi_control[8]  = elements;
	vdi_control[9]  = nrows;
	vdi_control[10] = write_mode;
	VDI_TRAP (vdi_params, handle, 10, 2,n);
	
	vdi_params.intin = vdi_intin;
	vdi_params.ptsin = vdi_ptsin;
}

#include "gem_vdiP.h"


void
vq_cellarray (short handle, short pxy[], short row_len, short nrows,
              short *el_used, short *rows_used, short *status, short color[])
{
	vdi_params.ptsin  = pxy;
	vdi_params.intout = color;
	
	vdi_control[7] = row_len;
	vdi_control[8] = nrows;
	VDI_TRAP (vdi_params, handle, 27, 2,0);

	vdi_params.ptsin  = vdi_ptsin;
	vdi_params.intout = vdi_intout;
	
	*el_used   = vdi_control[9];
	*rows_used = vdi_control[10];
	*status    = vdi_control[11];
}


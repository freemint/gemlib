/*
 *   text function
 */

#include "gem_vdiP.h"


void
vq_chcells (short handle, short *n_rows, short *n_cols)
{
	VDI_TRAP_ESC (vdi_params, handle, 5,1, 0,0);
	
	*n_rows = vdi_intout[0];
	*n_cols = vdi_intout[1];
}

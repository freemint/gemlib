/*
 *   text function
 */

#include "gem_vdiP.h"


void
vq_curaddress (short handle, short *cur_row, short *cur_col)
{
	VDI_TRAP_ESC (vdi_params, handle, 5,15, 0,0);
	
	*cur_row = vdi_intout[0];
	*cur_col = vdi_intout[1];
}

/*
 *   text function
 */

#include "gem_vdiP.h"


void
vs_curaddress (short handle, short row, short col)
{
	vdi_intin[0] = row;
	vdi_intin[1] = col;
	
	VDI_TRAP_ESC (vdi_params, handle, 5,11, 0,2);
}

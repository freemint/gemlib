/*
 *   special graphic funkcion
 */

#include "gem_vdiP.h"


void
v_trays (short handle, short input, short output,
         short *set_input, short *set_output)
{
	vdi_intin[0] = input;
	vdi_intin[1] = output;
	
	VDI_TRAP_ESC (vdi_params, handle, 5,29, 0,2);
	
	*set_input  = vdi_intout[0];
	*set_output = vdi_intout[1];
}

/*
 *   special graphic funkcion
 */

#include "gem_vdiP.h"


void
vq_tray_names (short handle, char *input_name, char *output_name,
               short *input, short *output)
{
	vdi_intin_ptr(0) = input_name;
	vdi_intin_ptr(2) = output_name;
	
	VDI_TRAP_ESC (vdi_params, handle, 5,36, 0,4);
	
	*input  = vdi_intout[0];
	*output = vdi_intout[1];
}

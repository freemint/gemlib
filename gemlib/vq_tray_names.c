/*
 *   special graphic funkcion
 */

#include "gem_vdiP.h"


void
vq_tray_names (short handle, const char *input_name, const char *output_name,
               short *input, short *output)
{
	*((const char **)(&vdi_intin[0])) = input_name;
	*((const char **)(&vdi_intin[2])) = output_name;
	
	VDI_TRAP_ESC (vdi_params, handle, 5,36, 0,4);
	
	*input  = vdi_intout[0];
	*output = vdi_intout[1];
}

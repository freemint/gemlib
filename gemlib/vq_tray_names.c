/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** returns the names of the current input and output tray
 *
 *  @param handle Device handle
 *  @param input_name pointer to the name of the input tray or NULL
 *  @param output_name pointer to the name of the output tray or NULL
 *  @param input number of the input tray
 *  @param output number of the output tray
 *  @return 0 if the driver doesn't supporte this function, any positive
 *          value (2) otherwise
 *
 *  @since depends on the driver. If the driver doesn't support this
 *         function, input and output are set to 0, and the tray name
 *         is set to '\\0' (if pointer isn't NULL).
 *
 */

short
vq_tray_names (short handle, char *input_name, char *output_name,
               short *input, short *output)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[4];   
	short vdi_intout[2]; 
	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_intout, 0L );
#endif
	
	vdi_intin_ptr(0) = input_name;
	vdi_intin_ptr(2) = output_name;
	
	VDI_TRAP_ESC (vdi_params, handle, 5,36, 0,4);
	
	if (vdi_control[4]) /* function supported by the driver */
	{
		*input  = vdi_intout[0];
		*output = vdi_intout[1];
	}
	else  /* function not supported by the driver */
	{
		*input = *output = 0;
		if (input_name) *input_name=0;
		if (output_name) *output_name=0;
	}
	
	return vdi_control[4];
}

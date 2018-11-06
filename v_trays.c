#include "gem_vdiP.h"

/** specify the paper trays. If the requested 
 *  tray does not exist, the standard tray will be selected (input 0 and 
 *  output 0).
 *
 *  @param handle Device handle
 *  @param input requested input tray
 *         - (-1) : manual input
 *         - 0 :  default input (tray 1)
 *         - 1 :  tray 2
 *         - etc...
 *  @param output requested output tray
 *         - 0: standard output (usually front)
 *         - 1: output 2
 *         - etc...
 *  @param set_input selected input tray \n
 *         [option CHECK_NULLPTR] set_input may be NULL
 *  @param set_output selected output tray \n
 *         [option CHECK_NULLPTR] set_output may be NULL
 *
 *  @return 0 if the driver doesn't supporte this function, any positive
 *          value (2) otherwise
 *
 *  @since depends on the driver. If the driver doesn't supporte this
 *         function, \p set_input and \p set_output will contain 0.
 *
 *  @sa vq_tray_names()
 *
 */

short
v_trays (short handle, short input, short output,
         short *set_input, short *set_output)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[2];   
	short vdi_intout[2]; 

	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_intout, vdi_dummy );
	
	vdi_intin[0] = input;
	vdi_intin[1] = output;
	
	VDI_TRAP_ESC (vdi_params, handle, 5,29, 0,2);
	
	if (vdi_control[4]) /* function supported by the driver */
	{
#if CHECK_NULLPTR
	if (set_input)
#endif
		*set_input  = vdi_intout[0];
#if CHECK_NULLPTR
	if (set_output)
#endif
		*set_output = vdi_intout[1];
	}
	else
	{
#if CHECK_NULLPTR
	if (set_input)
#endif
		*set_input  = 0;
#if CHECK_NULLPTR
	if (set_output)
#endif
		*set_output = 0;
	}
	
	return vdi_control[4];
}

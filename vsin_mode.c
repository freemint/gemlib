#include "gem_vdiP.h"

/** sets the input mode for the specified device
 *
 *  @param handle Device handle
 *  @param dev input device
 *         - 1: Mouse
 *         - 2: Cursor
 *         - 3: Function keys
 *         - 4: Keyboard
 *  @param mode requested input mode
 *         - REQUEST MODE (1): wait until input data is available
 *         - SAMPLE MODE  (2): return device status and input data (if available)
 *
 *  @return selected input mode
 *
 *  @since all VDI versions
 *
 */

short
vsin_mode (short handle, short dev, short mode)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[2];   
	short vdi_intout[1]; 
	
	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_intout, vdi_dummy );
	
	vdi_intin[0] = dev;
	vdi_intin[1] = mode;
	
	VDI_TRAP (vdi_params, handle, 33, 0,2);
	
	return vdi_intout[0];
}

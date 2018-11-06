#include "gem_vdiP.h"

/** You can limit the area for graphic operations by calling this function. If 
 *  you enable clipping graphic operations will only take place in the clipping 
 *  rectangle.
 *
 *  @param handle Device handle
 *  @param clip_flag turn on/off the clipping as follow:
 *         - 0 : turn clipping off.
 *           Warning: Do not switch off clipping because a graphic object
 *           which is drawn outside of the visible screen area will overwrite
 *           memory or cause a bus error.
 *         - 1 (or any nonzero value) : turn clipping on
 *  @param pxy clipping rectangle
 *
 *  @since all VDI versions
 *
 */

void
vs_clip (short handle, short clip_flag, short pxy[])
{
	short vdi_control[VDI_CNTRLMAX]; 
	
	VDI_PARAMS(vdi_control, &clip_flag, pxy, vdi_dummy, vdi_dummy );
	
	VDI_TRAP (vdi_params, handle, 129, 2,1);
}

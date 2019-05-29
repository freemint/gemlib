#include "gem_vdiP.h"

/** 
 *
 *  @param handle Device handle
 *  @param xdimension  \n
 *         [option CHECK_NULLPTR] xdimension may be NULL
 *  @param ydimension  \n
 *         [option CHECK_NULLPTR] ydimension may be NULL
 *
 *  @since supported by all table drivers
 *
 *
 *
 */

void
vq_tdimensions (short handle, short *xdimension, short *ydimension)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[2]; 

	VDI_PARAMS(vdi_control, 0L, 0L, vdi_intout, vdi_dummy );
	
	VDI_TRAP_ESC (vdi_params, handle, 5,84, 0,0);
	
#if CHECK_NULLPTR
	if (xdimension)
#endif
	*xdimension = vdi_intout[0];
#if CHECK_NULLPTR
	if (ydimension)
#endif
	*ydimension = vdi_intout[1];
}

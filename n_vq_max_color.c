#include "gem_vdiP.h"
#include "mt_gemx.h"

/** 
 *
 *  @param handle Device handle
 *  @param hilite_color \n
 *         [option CHECK_NULLPTR] hilite_color may be NULL
 *
 *  @return color space set 
 *
 *  @since NVDI 5 ?
 *
 *
 *
 */

long
vq_max_color (short handle, COLOR_ENTRY * hilite_color)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[6]; 

	VDI_PARAMS(vdi_control, 0L, 0L, vdi_intout, vdi_dummy);
	
	VDI_TRAP_ESC (vdi_params, handle, 209,2, 0,0);

#if CHECK_NULLPTR
	if (hilite_color)
#endif
	*hilite_color = *(COLOR_ENTRY *) & vdi_intout[2];
	
	return vdi_intout_long(0);
}

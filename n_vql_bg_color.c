#include "gem_vdiP.h"
#include "mt_gemx.h"

/** 
 *
 *  @param handle Device handle
 *  @param bg_color  \n
 *         [option CHECK_NULLPTR] bg_color may be NULL
 *
 *  @return color space
 *
 *  @since NVDI 5 ?
 *
 *
 *
 */

long
vql_bg_color (short handle, COLOR_ENTRY * bg_color)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[6]; 

	VDI_PARAMS(vdi_control, 0L, 0L, vdi_intout, vdi_dummy );
	
	VDI_TRAP_ESC (vdi_params, handle, 203,2, 0,0);

#if CHECK_NULLPTR
	if (bg_color)
#endif
	*bg_color = *(COLOR_ENTRY*)&vdi_intout[2];
	
	return vdi_intout_long(0);
}

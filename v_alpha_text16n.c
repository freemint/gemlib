#include "gem_vdiP.h"

/** 
 *
 *  @param handle Device handle
 *  @param wstr
 *  @param num string len  
 *
 *  @since 
 *
 *  @sa
 *
 *
 *
 */

void
v_alpha_text16n (short handle, const short * wstr, short num)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[5]; /* from TOS.HYP */

	VDI_PARAMS(vdi_control, wstr, 0L, vdi_intout, vdi_dummy);
	
	VDI_TRAP_ESC (vdi_params, handle, 5,25, 0,num);
}

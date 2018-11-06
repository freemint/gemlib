#include "gem_vdiP.h"

/** This function displays a string. The string starts at the current cursor 
 *  position.
 *
 *  @param handle Device handle
 *  @param str 
 *
 *  @since all VDI versions
 *
 */

void
v_curtext (short handle, const char *str)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[VDI_INTINMAX];   
	short n = vdi_str2array_n (str, vdi_intin, VDI_INTINMAX);

	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_dummy, vdi_dummy );
	
	VDI_TRAP_ESC (vdi_params, handle, 5,12, 0,n);
}

#include "gem_vdiP.h"

/** This function displays a string. The string starts at the current cursor 
 *  position.
 *
 *  @param handle Device handle
 *  @param wstr string (16 bits per character)
 *  @param num string len 
 *
 *  @since all VDI versions
 *
 */

void
v_curtext16n (short handle, const short * wstr, short num)
{
	short vdi_control[VDI_CNTRLMAX];   

	VDI_PARAMS(vdi_control, wstr, 0L, vdi_dummy, vdi_dummy );
	
	VDI_TRAP_ESC (vdi_params, handle, 5,12, 0,num);
}

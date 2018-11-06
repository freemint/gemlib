#include "gem_vdiP.h"

/** 'neutralizes' a preceding call of "HIDE CURSOR". If you want to 
 *  display the mouse cursor immediately without regard to the hide counter, the 
 *  paramter \p reset has to be zero.
 *
 *  @param handle Device handle
 *  @param reset 
 *         - 0 :    display cursor immediately
 *         - any nonzero value: decrement hide counter and display cursor if necessary
 *
 *  @since all VDI versions
 *
 *  @note Use mt_graf_mouse() to switch the cursor on or off.
 *
 */

void
v_show_c (short handle, short reset)
{
	short vdi_control[VDI_CNTRLMAX]; 

	VDI_PARAMS(vdi_control, &reset, 0L, vdi_dummy, vdi_dummy );
		
	VDI_TRAP (vdi_params, handle, 122, 0,1);
}

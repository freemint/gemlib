/*
 *  $Id$
 */

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
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		&reset,                      /* vdi_intin   */
		0L,                          /* vdi_ptsin   */
		0L,                          /* vdi_intout  */
		0L                           /* vdi_ptsout  */
	};
#else
	vdi_intin[0] = reset;
#endif
		
	VDI_TRAP (vdi_params, handle, 122, 0,1);
}

#include "gem_vdiP.h"

/** places a graphic cursor at the specified location
 *
 *  @param handle Device handle
 *  @param x x-coordinate of location to
 *		   place cursor in current
 *		   coordinate system
 *  @param y y-coordinate of location to
 *		   place cursor in current
 *		   coordinate system.
 *
 *  @since all VDI versions
 *
 *  The cursor is usually a
 *	cross hair cursor and is of the same type as
 *	that used for Input Locator, Request Mode. If
 *	sample mode input is supported, the application
 *	can use this call to generate the cursor for
 *	Input Locator, Sample Mode. In memory-mapped
 *	devices, the cursor is drawn in XOR mode so GEM
 *	VDI can remove it.
 *
 */

void
v_dspcur (short handle, short x, short y)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_ptsin[2];   

	VDI_PARAMS(vdi_control, 0L, vdi_ptsin, vdi_dummy, vdi_dummy );
	
	vdi_ptsin[0] = x;
	vdi_ptsin[1] = y;
	
	VDI_TRAP_ESC (vdi_params, handle, 5,18, 1,0);
}

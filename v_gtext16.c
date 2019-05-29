#include "gem_vdiP.h"

/** same as v_gtext()
 *
 *  @param handle Device handle
 *  @param x x-coordinate
 *  @param y y-coordinate
 *  @param wstr string, with 16 bits per character.
 *
 *  @since all VDI versions
 *
 */

void
v_gtext16 (short handle, short x, short y, const short *wstr)
{
	short n = vdi_wstrlen (wstr);
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_ptsin[2];   

	VDI_PARAMS(vdi_control, wstr, vdi_ptsin, vdi_dummy, vdi_dummy );
	
	vdi_ptsin[0] = x;
	vdi_ptsin[1] = y;

	VDI_TRAP (vdi_params, handle, 8, 1,n);
}


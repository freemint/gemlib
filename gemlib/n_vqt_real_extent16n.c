#include "gem_vdiP.h"
#include "mt_gemx.h"

/** see vqt_real_extent
 *
 *  @param handle Device handle
 *  @param x x-coordinate
 *  @param y y-coordinate
 *  @param wstring string in 16 bits format
 *  @param num string len
 *  @param extent coordinates of the bounding box
 *
 *  @since NVDI 3.00
 *
 *
 *
 */

void
vqt_real_extent16n (short handle, short x, short y, const WCHAR *wstring, short num, short extent[])
{
	short vdi_control[VDI_CNTRLMAX];  
	short vdi_ptsin[2];   

	VDI_PARAMS(vdi_control, (short *)NO_CONST(wstring), vdi_ptsin, vdi_dummy, extent);

	vdi_ptsin[0] = x;
	vdi_ptsin[1] = y;
	
	VDI_TRAP_ESC (vdi_params, handle, 240,4200, 1,num);
}

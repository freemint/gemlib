#include "gem_vdiP.h"
#include "mt_gemx.h"

/** see vqt_f_extent()
 *
 *  @param handle Device handle
 *  @param wstr string (16 bits per character)
 *  @param num string len 
 *  @param extent extent[0..7] : coordinates of the rectangle
 *
 *  @since NVDI 3.00
 *
 *
 *
 */

void
vqt_f_extent16n (short handle, const WCHAR * wstr, short num, short extent[])
{
	short vdi_control[VDI_CNTRLMAX]; 

	VDI_PARAMS(vdi_control, (short *)NO_CONST(wstr), 0L, vdi_dummy, extent );
	
	VDI_TRAP (vdi_params, handle, 240, 0,num);
}

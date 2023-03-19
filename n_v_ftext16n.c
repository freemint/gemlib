#include "gem_vdiP.h"
#include "mt_gemx.h"

/** see v_ftext()
 *
 *  @param handle Device handle
 *  @param pos point for coordinates
 *  @param wstr string (16 bits per character)
 *  @param num string len
 *
 *
 *
 */

void
v_ftext16n (short handle, PXY pos, const WCHAR * wstr, short num)
{
	short vdi_control[VDI_CNTRLMAX]; 

	VDI_PARAMS(vdi_control, (const short *)wstr, (short*)&pos, vdi_dummy, vdi_dummy);
	
	VDI_TRAP (vdi_params, handle, 241, 1,num);
}

/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** see vqt_f_extent()
 *
 *  @param handle Device handle
 *  @param wstr 
 *  @param num string len 
 *  @param extent 
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

	VDI_PARAMS(vdi_control, wstr, 0L, vdi_dummy, extent );
	
	VDI_TRAP (vdi_params, handle, 240, 0,num);
}

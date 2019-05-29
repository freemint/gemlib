#include "gem_vdiP.h"
#include "mt_gemx.h"

/** 
 *
 *  @param handle Device handle
 *  @param ctab reference to color table
 *
 *  @return 0=error, 1=all ok
 *
 *  @since NVDI 5 ?
 *
 *
 *
 */

short
v_delete_ctab (short handle, COLOR_TAB * ctab)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[1]; 

	VDI_PARAMS(vdi_control, (short*)&ctab, 0L, vdi_intout, vdi_dummy);
	
	VDI_TRAP_ESC (vdi_params, handle, 206,9, 0,2);

	return vdi_intout[0];
}

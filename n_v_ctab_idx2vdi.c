#include "gem_vdiP.h"
#include "mt_gemx.h"

/** 
 *
 *  @param handle Device handle
 *  @param index Index of colortab entry
 *
 *  @return Index of VDI color
 *
 *  @since NVDI 5 ?
 *
 *
 *
 */

short
v_ctab_idx2vdi (short handle, short index)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[1]; 

	VDI_PARAMS(vdi_control, &index, 0L, vdi_intout, vdi_dummy);
		
	VDI_TRAP_ESC (vdi_params, handle, 206,3, 0,1);

	return vdi_intout[0];
}

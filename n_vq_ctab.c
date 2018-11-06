#include "gem_vdiP.h"
#include "mt_gemx.h"

/** 
 *
 *  @param handle Device handle
 *  @param ctab_length 
 *  @param ctab 
 *
 *  @return 
 *
 *  @since NVDI 5 ?
 *
 *
 *
 */

short
vq_ctab (short handle, long ctab_length, COLOR_TAB * ctab)
{
	short vdi_control[VDI_CNTRLMAX]; 

	VDI_PARAMS(vdi_control, (short*)&ctab_length, 0L, (short*)ctab, vdi_dummy);
	
	VDI_TRAP (vdi_params, handle, 206, 0,2);

	return (vdi_control[4] ? 1 : 0);
}

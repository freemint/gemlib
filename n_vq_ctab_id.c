#include "gem_vdiP.h"
#include "mt_gemx.h"

/** 
 *
 *  @param handle Device handle
 *
 *  @return id of the current color table 
 *
 *  @since NVDI 5 ?
 *
 *
 *
 */

long
vq_ctab_id (short handle)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[2]; 

	VDI_PARAMS(vdi_control, 0L, 0L, vdi_intout, vdi_dummy);
	
	VDI_TRAP_ESC (vdi_params, handle, 206,2, 0,0);

	return vdi_intout_long(0);
}

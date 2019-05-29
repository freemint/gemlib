#include "gem_vdiP.h"
#include "mt_gemx.h"

/** 
 *
 *  @param handle Device handle
 *
 *  @return number of entries set 
 *
 *  @since NVDI 5 ?
 *
 *
 *
 */

short
vs_dflt_ctab (short handle)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[1]; 

	VDI_PARAMS(vdi_control, 0L, 0L, vdi_intout, vdi_dummy);
	
	VDI_TRAP_ESC (vdi_params, handle, 205,2, 0,0);

	return vdi_intout[0];
}

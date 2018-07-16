/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** After calling v_bez_on(), you can call v_bez()/v_bez_fill() without a 
 *  sub-opcode in contrl[5]. This function exists only for compatibility reasons 
 *  and usually it is only used in old GEM/3 metafiles.
 *
 *  @param handle Device handle
 *
 *  @return bezier depth, is a value between 0 (no beziers) and 7 (maximum quality) and 
 *          represents the bezier depth. You should only use this value to determine if 
 *          the driver is able to draw bezier curves.
 *
 *  @since NVDI 2.10
 *
 *  Applications should only use this call to determine, if the driver is able
 *  to draw bezier curves (check 
 *  if the return value indicates bezier support).
 *  
 *
 */

short
v_bez_on (short handle)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[1]; 

	VDI_PARAMS(vdi_control, 0L, 0L, vdi_intout, vdi_dummy);
	
	vdi_intout[0] = 0;
	
	/* nota: ctrl1=1 means v_bez "ON", it's not the nb of entries in ptsin[] */
	VDI_TRAP_ESC (vdi_params, handle, 11,13, 1,0);

	return vdi_intout[0];
}

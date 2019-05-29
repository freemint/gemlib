#include "gem_vdiP.h"
#include "mt_gemx.h"

/** 
 *
 *  @param handle Device handle
 *  @param type 0=text color, 1=fill color, 2=line color, 3=marker color
 *  @param r red portion in tenth of a precent
 *  @param g green portion in tenth of a precent
 *  @param b blue portion in tenth of a precent
 *
 *  @since NVDI 5 ?
 *
 *
 *
 */

void
v_setrgb (short handle, short type, short r, short g, short b)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[3];   

	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_dummy, vdi_dummy);
	
	vdi_intin[0] = r;
	vdi_intin[1] = g;
	vdi_intin[2] = b;

	VDI_TRAP_ESC (vdi_params, handle, 138,type, 0,3);
}

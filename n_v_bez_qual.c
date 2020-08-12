#include "gem_vdiP.h"
#include "mt_gemx.h"

/** specifies the  quality and accuracy of the bezier curves. You can 
 *  select the quality in a range between 0 and 100 per cent. 
 *
 *  @param handle Device handle
 *  @param percent requested bezier quality
 *  @param actual realized bezier quality
 *
 *  @since since NVDI 2.10
 *
 *
 *
 */

short
v_bez_qual (short handle, short percent, short *actual)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[3];   

	VDI_PARAMS(vdi_control, vdi_intin, 0L, actual, vdi_dummy);
	
	vdi_intin[0] = 32;
	vdi_intin[1] = 1;
	vdi_intin[2] = percent;
	
	VDI_TRAP_ESC (vdi_params, handle, 5,99, 0,3);
	return *actual;
}

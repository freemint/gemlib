#include "gem_vdiP.h"
#include "mt_gemx.h"

/** This function is not documented. Dont use it!
 *
 *  @param handle Device handle
 *  @param name name
 *
 *  @return unknow
 * 
 *  @since depend of the driver
 *
 */


short vs_save_disp_list(short handle, const char *name)
{
	short vdi_control[VDI_CNTRLMAX];
	short vdi_intout[2];
	short vdi_intin[N_PTRINTS];

	VDI_PARAMS (vdi_control, vdi_intin, vdi_dummy, vdi_intout, vdi_dummy);
	
	vdi_intin_ptr(0, const char *) = name;
	vdi_intout[0] = 0;
	VDI_TRAP_ESC (vdi_params, handle, 5,2106, 0, 2);
	
	return vdi_intout[0];
}

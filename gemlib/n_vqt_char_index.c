/*
 *   NOTE: requires NVDI version 4.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


short
vqt_char_index (short handle, short scr_index, short scr_mode, short dst_mode)
{
	vdi_intin[0] = scr_index;
	vdi_intin[1] = scr_mode;
	vdi_intin[2] = dst_mode;
	
	VDI_TRAP (vdi_params, handle, 190, 0,3);
	
	return vdi_intout[0];
}

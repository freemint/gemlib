/*
 *   NOTE: requires NVDI version 3.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


short
vqt_name_and_id (short handle, short font_format, char *font_name, char *ret_name)
{
	register short n = vdi_str2array (font_name, vdi_intin);
	vdi_intin[0]     = font_format;
	
	VDI_TRAP_ESC (vdi_params, handle, 230,100, 0,n);
	
	vdi_array2str (vdi_intin, ret_name, vdi_control[4]);
	
	return vdi_intout[0];
}

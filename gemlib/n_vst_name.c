/*
 *   NOTE: requires NVDI version 3.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


short
vst_name (short handle, short font_format, char *font_name, char *ret_name)
{
	register short n = 1 + vdi_str2array (font_name, vdi_intin + 1);

	vdi_intin[0] = font_format;
	
	VDI_TRAP (vdi_params, handle, 230, 0,n);
	
	vdi_array2str (vdi_intout, ret_name, vdi_control[4]);
	
	return vdi_intout[0];
}

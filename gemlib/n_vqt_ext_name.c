/*
 *   NOTE: requires NVDI version 3.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


short
vqt_ext_name (short handle, short index,
              char *name, short *font_format, short *flags)
{
	vdi_intin[0] = index;
	vdi_intin[1] = 0;

	VDI_TRAP_ESC (vdi_params, handle, 130,1, 0,2);

	vdi_array2str (vdi_intout + 1, name, 32);
	name[32]     = vdi_intout[33];
	*flags       = (vdi_intout[34] >> 8) & 0xff;
	*font_format = vdi_intout[34] & 0xff;
	
	return vdi_intout[0];
}

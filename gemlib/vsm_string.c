#include "gem_vdiP.h"


short
vsm_string (short handle, short len, short echo, short echoxy[], char *str)
{
	vdi_intin[0]      = len;
	vdi_intin[1]      = echo;
	*(long*)vdi_ptsin = *(long*)echoxy;
	
	VDI_TRAP (vdi_params, handle, 31, 1,2);
	
	vdi_array2str (vdi_intout, str, vdi_control[4]);
	
	return vdi_control[4];
}

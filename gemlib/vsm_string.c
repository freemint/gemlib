
#include "gem.h"


short
vsm_string (short handle, short len, short echo, short echoxy[], char *str)
{
	vdi_intin[0] = len;
	vdi_intin[1] = echo;
	vdi_ptsin[0] = echoxy[0];
	vdi_ptsin[1] = echoxy[1];
	vdi_control[0] = 31;
	vdi_control[1] = 1;
	vdi_control[3] = 2;
	vdi_control[5] = 0;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	vdi_array2str (vdi_intout, str, vdi_control[4]);
	return vdi_control[4];
}

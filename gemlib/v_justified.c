
#include "gem.h"


void
v_justified (short handle, short x, short y, const char *str, short len,
	     short word_space, short char_space)
{
	short i;

	vdi_intin[0] = word_space;
	vdi_intin[1] = char_space;
	i = vdi_str2array (str, vdi_intin + 2);

	vdi_ptsin[0] = x;
	vdi_ptsin[1] = y;
	vdi_ptsin[2] = len;
	vdi_ptsin[3] = 0;

	vdi_control[0] = 11;
	vdi_control[1] = 2;
	vdi_control[3] = i + 2;
	vdi_control[5] = 10;
	vdi_control[6] = handle;

	vdi (&vdi_params);
}


#include "gem.h"


void
v_curtext (short handle, const char *str)
{
	short i;

	i = vdi_str2array (str, vdi_intin);
	vdi_control[0] = 5;
	vdi_control[1] = 0;
	vdi_control[3] = i;
	vdi_control[5] = 12;
	vdi_control[6] = handle;
	vdi (&vdi_params);
}

/*
 * * text function
 */

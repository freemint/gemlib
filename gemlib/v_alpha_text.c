
#include "gem.h"


void
v_alpha_text (short handle, const char *str)
{
	short n;

	n = vdi_str2array (str, vdi_intin);
	vdi_control[0] = 5;
	vdi_control[1] = 0;
	vdi_control[3] = n;
	vdi_control[5] = 25;
	vdi_control[6] = handle;
	vdi (&vdi_params);
}

/*
 * * text function
 */

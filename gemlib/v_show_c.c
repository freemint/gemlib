
#include "gem.h"


void
v_show_c (short handle, short reset)
{
	vdi_intin[0] = reset;
	vdi_control[0] = 122;
	vdi_control[1] = 0;
	vdi_control[3] = 1;
	vdi_control[5] = 0;
	vdi_control[6] = handle;
	vdi (&vdi_params);
}

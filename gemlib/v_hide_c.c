
#include "gem.h"


void
v_hide_c (short handle)
{
	vdi_control[0] = 123;
	vdi_control[1] = 0;
	vdi_control[3] = 0;
	vdi_control[5] = 0;
	vdi_control[6] = handle;
	vdi (&vdi_params);
}

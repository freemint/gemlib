
#include "gem.h"


void
v_set_app_buff (int handle, void *buf_p, int size)
{
	*((void **) (&vdi_intin[0])) = buf_p;
	vdi_intin[3] = size;
	vdi_control[0] = -1;
	vdi_control[1] = 0;
	vdi_control[3] = 3;
	vdi_control[5] = 6;
	vdi_control[6] = handle;
	vdi (&vdi_params);
}

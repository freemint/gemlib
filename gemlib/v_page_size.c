
#include "gem.h"


int
v_page_size (int handle, int page_id)
{
	vdi_intin[0] = page_id;
	vdi_control[0] = 5;
	vdi_control[1] = 0;
	vdi_control[3] = 1;
	vdi_control[5] = 37;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	return vdi_intout[0];
}

/*
 * * special graphic funkcion
 */


#include "gem.h"


void
v_contourfill (short handle, short x, short y, short index)
{
	vdi_intin[0] = index;
	vdi_ptsin[0] = x;
	vdi_ptsin[1] = y;
	vdi_control[0] = 103;
	vdi_control[1] = 1;
	vdi_control[3] = 1;
	vdi_control[6] = handle;
	vdi (&vdi_params);
}

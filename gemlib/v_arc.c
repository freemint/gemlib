
#include "gem.h"


void
v_arc (short handle, short x, short y, short radius, short begang, short endang)
{
	vdi_intin[0] = begang;
	vdi_intin[1] = endang;
	vdi_ptsin[0] = x;
	vdi_ptsin[1] = y;
	vdi_ptsin[2] = 0;
	vdi_ptsin[3] = 0;
	vdi_ptsin[4] = 0;
	vdi_ptsin[5] = 0;
	vdi_ptsin[6] = radius;
	vdi_ptsin[7] = 0;

	vdi_control[0] = 11;
	vdi_control[1] = 4;
	vdi_control[3] = 2;
	vdi_control[5] = 2;
	vdi_control[6] = handle;
	vdi (&vdi_params);
}


#include "gem.h"


void
v_ellarc (short handle, short x, short y, short xrad, short yrad, short begang,
	  short endang)
{
	vdi_intin[0] = begang;
	vdi_intin[1] = endang;
	vdi_ptsin[0] = x;
	vdi_ptsin[1] = y;
	vdi_ptsin[2] = xrad;
	vdi_ptsin[3] = yrad;

	vdi_control[0] = 11;
	vdi_control[1] = 2;
	vdi_control[3] = 2;
	vdi_control[5] = 6;
	vdi_control[6] = handle;
	vdi (&vdi_params);
}

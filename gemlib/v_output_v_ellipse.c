
#include "gem.h"


void
v_ellipse (int handle, int x, int y, int xrad, int yrad)
{
	vdi_ptsin[0] = x;
	vdi_ptsin[1] = y;
	vdi_ptsin[2] = xrad;
	vdi_ptsin[3] = yrad;
	vdi_control[0] = 11;
	vdi_control[1] = 2;
	vdi_control[3] = 0;
	vdi_control[5] = 5;
	vdi_control[6] = handle;
	vdi (&vdi_params);
}


#include "gem.h"


void
vqt_get_table (int handle, short **map)
{
	vdi_control[0] = 254;
	vdi_control[1] = 0;
	vdi_control[3] = 0;
	vdi_control[5] = 0;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	*map = *((short **) (&vdi_intout[0]));
}

#include "gem_vdiP.h"


void
vqt_get_table (short handle, short **map)
{
	VDI_TRAP (vdi_params, handle, 254, 0,0);
	
	*map = *((short **)(&vdi_intout[0]));
}

#include "gem_vdiP.h"


void
vqt_get_table (short handle, short **map)
{
	VDI_TRAP_00 (vdi_params, handle, 254);
	
	*map = vdi_intout_ptr(0);
}

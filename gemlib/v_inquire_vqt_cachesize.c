
#include "gem.h"


void
vqt_cachesize (int handle, int which_cache, long *size)
{
	vdi_intin[0] = which_cache;
	vdi_control[0] = 255;
	vdi_control[1] = 0;
	vdi_control[3] = 1;
	vdi_control[5] = 0;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	*size = *((long *) (&vdi_intout[0]));
}

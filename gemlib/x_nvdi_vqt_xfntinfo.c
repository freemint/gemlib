
#include "gemx.h"


int
vqt_xfntinfo (int handle, int flags, int id, int index, XFNT_INFO * info)
{
	info->size = (long) sizeof (XFNT_INFO);
	vdi_intin[0] = flags;
	vdi_intin[1] = id;
	vdi_intin[2] = index;
	*((XFNT_INFO **) (&vdi_intin[3])) = info;
	vdi_control[0] = 229;
	vdi_control[1] = 0;
	vdi_control[3] = 5;
	vdi_control[5] = 0;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	return vdi_intout[1];
}

/*
 * * NOTE: requires NVDI version 3.x or higher
 */

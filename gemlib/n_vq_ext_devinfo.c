
#include "gemx.h"


short
vq_ext_devinfo (short handle, short device, short *dev_exists,
		char *file_path, char *file_name, char *name)
{
	vdi_intin[0] = device;
	*((char **) (&vdi_intin[1])) = file_path;
	*((char **) (&vdi_intin[3])) = file_name;
	*((char **) (&vdi_intin[5])) = name;

	vdi_control[0] = 248;
	vdi_control[1] = 0;
	vdi_control[3] = 7;
	vdi_control[5] = 4242;
	vdi_control[6] = handle;

	vdi (&vdi_params);

	*dev_exists = vdi_intout[0];
	return vdi_intout[1];
}

/*
 * * NOTE: requires NVDI version 3.x or higher
 */

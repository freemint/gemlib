
#include "gemx.h"


void
vq_devinfo (short handle, short device, short *dev_open, char *file_name,
	    char *device_name)
{
	short len, i;

	vdi_intin[0] = device;
	vdi_control[0] = 248;
	vdi_control[1] = 0;
	vdi_control[3] = 1;
	vdi_control[5] = 0;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	vdi_array2str (vdi_intout, file_name, vdi_control[4]);
	*dev_open = vdi_ptsout[0];

	/* Name in ptsout als C-String, d.h. pro ptsout[] 2 Buchstaben!! */
	if ((vdi_control[2] == 1) && (vdi_control[1] > 0))	/* steht so in NVDI4-Doku */
		len = vdi_control[1];
	else
		len = vdi_control[2] - 1;
	for (i = 1; i <= len; i++)
		*((short *) device_name)++ = vdi_ptsout[i];
	*device_name++ = 0;
}

/*
 * * NOTE: requires NVDI version 3.x or higher
 */

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

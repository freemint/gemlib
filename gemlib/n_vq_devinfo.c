/*
 *   NOTE: requires NVDI version 3.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"
#include <string.h>


void
vq_devinfo (short handle, short device,
            short *dev_open, char *file_name, char *device_name)
{
	register short len;

	vdi_intin[0] = device;

	VDI_TRAP (vdi_params, handle, 248, 0,1);

	vdi_array2str (vdi_intout, file_name, vdi_control[4]);
	*dev_open = vdi_ptsout[0];

	/* Name in ptsout als C-String, d.h. pro ptsout[] 2 Buchstaben!!
	 * steht so in NVDI4-Doku
	 * */
	if ((vdi_control[2] == 1) && (vdi_control[1] > 0)) {
		len = vdi_control[1];
	} else {
		len = (vdi_control[2] - 1) *2;
	}
	memcpy (device_name, vdi_ptsout +1, len);
	device_name[len] = '\0';
}

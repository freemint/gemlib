/*
 *   NOTE: requires NVDI version 3.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


short
vq_ext_devinfo (short handle, short device,
                short *dev_exists, char *file_path, char *file_name, char *name)
{
	vdi_intin    [0] = device;
	vdi_intin_ptr(1) = file_path;
	vdi_intin_ptr(3) = file_name;
	vdi_intin_ptr(5) = name;

	VDI_TRAP_ESC (vdi_params, handle, 248,4242, 0,7);

	*dev_exists = vdi_intout[0];
	
	return vdi_intout[1];
}

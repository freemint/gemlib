/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** Similar to vq_devinfo() the function vq_ext_devinfo() returns information 
 *  about the driver.
 *
 *  @param handle Device handle
 *  @param device device id (0-99)
 *  @param dev_exists: \n
 *         - 0: no driver
 *         - != 0: driver exists 
 *  @param file_path pointer to the file path
 *  @param file_name pointer to the file name
 *  @param name pointer to the device name
 *
 *  @return device opened:
 *          - 0: driver is closed
 *          - != 0: driver is already open
 *
 *  @since NVDI 3.00
 *
 *
 *
 */

short
vq_ext_devinfo (short handle, short device,
                short *dev_exists, char *file_path, char *file_name, char *name)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[7];   
	short vdi_intout[2]; 
	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_intout, vdi_dummy);
#endif
	
	vdi_intin    [0] = device;
	vdi_intin_ptr(1) = file_path;
	vdi_intin_ptr(3) = file_name;
	vdi_intin_ptr(5) = name;

	VDI_TRAP_ESC (vdi_params, handle, 248,4242, 0,7);

	*dev_exists = vdi_intout[0];
	
	return vdi_intout[1];
}

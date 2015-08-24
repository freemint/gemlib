/*
 *  $Id$
 */

#include "mt_gem.h"
#include "mt_gemx.h"

/** reports back, if a driver exists and if he has been opened.
 *  Besides the name of the driver (e.g. "XVGA256.SYS") and the 'readable' name 
 *  ("VGA 256 colors") are returned.
 *
 *  @param handle any Device handle. handle must be a valid VDI handle.
 *         The workstation opened by the AES (see mt_graf_handle() ) seems 
 *         to be a good choice. Some VDI layer crashes is you set handle a nul value.
 *  @param device device id (0-99)
 *  @param dev_busy  
 *         - 0: driver is closed or can be opened once more
 *         - 1: driver is already open and cannot be opened once more ATM.
 *  @param file_name file name
 *  @param device_name readable device name
 *
 *  @since NVDI 3.00, SpeedoGDOS 4
 *
 *  @sa vq_devinfo()
 *
 *  @note FontGDOS 2 may crash this binding (vdi_control values returned are
 *        doesn't deals with the data returned in vdi_intout/ptsout).
 *
 *  @note If the file name is empty, there is no driver with the given id \p device.
 *
 */

void
vqt_devinfo (short handle, short device,
            short *dev_busy, char *file_name, char *device_name)
{
	short dummy;
	
	*dev_busy = vq_devinfo(handle, device, &dummy, file_name, device_name);
}

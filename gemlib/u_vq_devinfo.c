

#include "gem_vdiP.h"
#include "mt_gemx.h"
#include <string.h>

/** reports back, if a driver exists and if he has been opened.
 *  Besides the name of the driver (e.g. "XVGA256.SYS") and the 'readable' name 
 *  ("VGA 256 colors") are returned.
 *
 *  @param handle any Device handle. handle must be a valid VDI handle.
 *         The workstation opened by the AES (see mt_graf_handle() ) seems 
 *         to be a good choice. Some VDI layer crashes is you set handle a nul value.
 *  @param device device id (0-99)
 *  @param dev_exists  
 *         - 0: driver doesn't exist for this device.
 *         - 1: driver exists for this device
 *  @param file_name file name
 *  @param device_name readable device name
 *
 *  @return 0 if the driver is not opened, or can be opened once more.
 *          It's similar to the dev_busy parameter of vqt_devinfo().
 *
 *  @since NVDI 3.00, SpeedoGDOS 4
 *
 *  @sa vqt_devinfo()
 *
 *  @note FontGDOS 2 may crash this binding (vdi_control values returned are
 *        doesn't deals with the data returned in vdi_intout/ptsout).
 *
 *  @note If the file name is empty, there is no driver with the given id \p device.
 *
 */

short
udef_vq_devinfo (short handle, short device,
            short *dev_exists, char *file_name, char *device_name)
{
	short len;

	VDI_PARAMS(_VDIParBlk.vdi_control, &device, 0L, _VDIParBlk.vdi_intout, _VDIParBlk.vdi_ptsout);

	VDI_TRAP (vdi_params, handle, 248, 0,1);

	/* does the driver exist ? */
	if (_VDIParBlk.vdi_control[4]==0 || _VDIParBlk.vdi_intout[0]==0)
	{
		*dev_exists = 0;
		*file_name = 0;
		*device_name = 0;
		return 0;
	}
	
	/* here, the driver exists */
	*dev_exists = 1;
	
	/* set the filename. The value in vdi_intout may be "DRIVER.SYS"
	 * or "DRIVER   SYS". vdi_intout is not a nul-terminated string.
	 * In both cases, this binding returns a valid filename: "DRIVER.SYS"
	 * with a null-character to ended the string. 
	 */
	for (len=0; len<_VDIParBlk.vdi_control[4]; len++) 
	{
		*file_name = _VDIParBlk.vdi_intout[len];
		if (*file_name==' ')
		{
			if (_VDIParBlk.vdi_intout[len+1]!=' ')
			{
		 		*file_name='.';
				file_name++;
			}
		}
		else
			file_name++;
	}
	*file_name=0;
	
	/* device name in ptsout is a C-String, (a nul-terminated string with 8bits per characters)
	 * each short value (vdi_ptsout[x]) contains 2 characters.
	 * When ptsout contains a device name, NVDI/SpeedoGDOS seems to always write the value "13"
	 * in vdi_control[1] (hey! this should be a read only value from the VDI point of view!!!),
	 * and SpeedoGDOS 5 may set vdi_control[2] == 1 (intead of the size of vdi_ptsout, including
	 * the device_name). It's seems that this value "13" (written in vdi_control[1]) has missed
	 * its target (vdi_control[2]). So, here is a workaround:
	 */
	if ((_VDIParBlk.vdi_control[2] == 1) && (_VDIParBlk.vdi_control[1] > 0)) {
		len = _VDIParBlk.vdi_control[1] *2;
	} else {
		len = (_VDIParBlk.vdi_control[2] - 1) *2;
	}
	memcpy (device_name, _VDIParBlk.vdi_ptsout +1, len);
	device_name[len] = '\0';

	return _VDIParBlk.vdi_ptsout[0];
}

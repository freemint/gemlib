/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"
#include <string.h>

/** reports back, if a driver exists and if he has been opened.
 *  Besides the name of the driver (e.g. "XVGA256.SYS") and the 'readable' name 
 *  ("VGA 256 colors") are returned.
 *
 *  @param handle Device handle
 *  @param device device id (0-99)
 *  @param dev_open  
 *         - 0: driver is closed
 *         - 1: driver is already open
 *  @param file_name file name
 *  @param device_name readable device name
 *
 *  @since NVDI 3.00
 *
 *  @note If the file name is empty, there is no driver with the given id \p device.
 *
 */

void
vq_devinfo (short handle, short device,
            short *dev_open, char *file_name, char *device_name)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[VDI_INTOUTMAX]; 
	short vdi_ptsout[VDI_PTSOUTMAX]; 
#endif
	register short len;
#if USE_LOCAL_VDIPB
	VDI_PARAMS(vdi_control, &device, 0L, vdi_intout, vdi_ptsout);
#endif
	
#if !(USE_LOCAL_VDIPB)
	vdi_intin[0] = device;
#endif

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

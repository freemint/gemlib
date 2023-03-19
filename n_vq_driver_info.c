#include "gem_vdiP.h"
#include "mt_gemx.h"

/** This function returns information about version number of the library and 
 *  driver.
 *
 *  @param handle Device handle
 *  @param lib library version number ($0102 = 1.02)
 *  @param drv driver version number
 *  @param plane number of planes
 *         - 1:  mono
 *         - 3:  CMY
 *         - 4:  CMYK
 *  @param attr unknown
 *  @param name full name of the printer (26 characters + null byte)
 * 
 * 
 *  @return 0 if this function is not supported by the driver, any other value if
 *          the driver support this function. 
 * 
 *          intout[1] returns the file format (based on the file extension):
 *         - 0:  unknown file format
 *         - 1:  IMG
 *         - 2:  TGA
 * 
 * 
 *  @since depend of the driver
 *
 *  
 *
 *
 */


short vq_driver_info(short handle, short *lib, short *drv, short *plane, short *attr, char name[27])
{
	short vdi_control[VDI_CNTRLMAX];
	short vdi_intout[31];

	VDI_PARAMS (vdi_control, vdi_dummy, vdi_dummy, vdi_intout, vdi_dummy);
	
	vdi_intout[0] = 0;
	VDI_TRAP_ESC (vdi_params, handle, 5,2101, 0, 0);
	
	*lib = vdi_intout[1];
	*drv = vdi_intout[2];
	*plane = vdi_intout[3];
	*attr = vdi_intout[4];	
	vdi_array2str(&vdi_intout[5], name, 26);
	return vdi_intout[0];
}

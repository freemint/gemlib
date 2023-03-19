#include "gem_vdiP.h"
#include "mt_gemx.h"

/** This function returns information about file formats supported by v_bit_image().  
 *
 *  @param handle Device handle
 *  @param ver v_bit_image() version number
 *  @param maximg maximum image number per page
 *  @param form available image format
 *         - bit 0 & 1:  IMG
 *           - 00: IMG mono
 *           - 01: reserved
 *           - 10: reserved 
 *           - 11: reserved 
 *         - bit 2 & 3:  TGA
 *           - 00: TGA unknown 
 *           - 01: TGA type 2 unpacked
 *           - 10: reserved 
 *           - 11: reserved 
 *         - bit 4 to 15:  reserved
 * 
 * 
 *  @return 0 if this function is not supported by the driver, any other value if
 *          the driver support this function. 
 * 
 * 
 * 
 *  @since depend of the driver
 *
 *  
 *
 *
 */

short vq_bit_image(short handle, short *ver, short *maximg, short *form)
{
	short vdi_control[VDI_CNTRLMAX];
	short vdi_intout[4];

	VDI_PARAMS (vdi_control, vdi_dummy, vdi_dummy, vdi_intout, vdi_dummy);
	
	vdi_intout[0] = 0;
	VDI_TRAP_ESC (vdi_params, handle, 5,2102, 0, 0);
	
	*ver = vdi_intout[1];
	*maximg = vdi_intout[2];
	*form = vdi_intout[3];
	return vdi_intout[0];
}

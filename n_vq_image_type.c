#include "gem_vdiP.h"
#include "mt_gemx.h"

/** This function returns information about the specified bitmap file.
 *
 *  @param handle Device handle
 *  @param file pointer to file name
 *  @param image pointer to a BIT_IMAGE structure
 * 
 * 
 *  @return 0 if this function is not supported by the driver, any other value if
 *          the driver support this function.
 * 
 *  @since depend of the driver
 *
 *  
 *
 *
 */

short vq_image_type(short handle, const char *file, BIT_IMAGE *image)
{
	short vdi_control[VDI_CNTRLMAX];
	short vdi_intout[2];
	short vdi_intin[VDI_INTINMAX];
	short vdi_ptsin[N_PTRINTS];
	short i;

	VDI_PARAMS (vdi_control, vdi_intin, vdi_ptsin, vdi_intout, vdi_dummy);
	
	i = vdi_str2array(file, vdi_intin);
	vdi_intin[i++] = 0;
	vdi_ptsin_ptr(0, BIT_IMAGE *) = image;
	vdi_intout[0] = 0;
	VDI_TRAP_ESC (vdi_params, handle, 5,2105, 1, i);
	
	return vdi_intout[0];
}

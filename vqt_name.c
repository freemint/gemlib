#include "gem_vdiP.h"

/** This function returns a 32-character string that describes the face.
 *
 *  @param handle Device handle
 *  @param element number of the font
 *  @param name name of the font
 *
 *  @return ID number
 *
 *  @since all VDI versions; extended since NVDI 3.00 (add 33th byte to
 *  name for "bitmap/vector font" flag)
 *
 *  @note if the name is 32 characters long, \p name is not 0 terminated !
 *  @note some device driver returns -1 for their not available system font
 */

short
vqt_name (short handle, short element, char *name)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[128];
	short len=33;
	short *src;
	char  *des;
	
	VDI_PARAMS(vdi_control, &element, 0L, vdi_intout, vdi_dummy );
	
	vdi_intout[33] = 0;

	VDI_TRAP (vdi_params, handle, 130, 0,1);

	/* vdi_array2str-like but without adding a NULL byte at the end */
	src = vdi_intout + 1;
	des = name;
	while (len > 0) {
		*(des++) = (char) *(src++);
		len--;
	}
	
	return vdi_intout[0];
}

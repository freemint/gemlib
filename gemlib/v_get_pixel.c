/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** On a device with up to 8 planes (256 simultaneously displayable colors) this 
 *  function returns the value and the color index of a pixel.
 *
 *  @param handle Device handle
 *  @param x 
 *  @param y 
 *  @param pel pixel value \n
 *         [option CHECK_NULLPTR] pel may be NULL
 *  @param index color index \n
 *         [option CHECK_NULLPTR] index may be NULL
 *
 *  @since all VDI versions (screen drivers only)
 *
 *
 *  In HiColor (15 or 16 bits) \p pel contains the pixel value and \p index is 
 *  usually -1.
 *  
 *  In TrueColor \p pel ist the low word and \p index the high word of the pixel value.
 *  
 */

void
v_get_pixel (short handle, short x, short y, short *pel, short *index)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_ptsin[2];   
	short vdi_intout[2]; 

	VDI_PARAMS(vdi_control, 0L, vdi_ptsin, vdi_intout, vdi_dummy );
	
	vdi_ptsin[0] = x;
	vdi_ptsin[1] = y;

	VDI_TRAP (vdi_params, handle, 105, 1,0);

#if CHECK_NULLPTR
	if (pel)
#endif
	*pel   = vdi_intout[0];
#if CHECK_NULLPTR
	if (index)
#endif
	*index = vdi_intout[1];
}

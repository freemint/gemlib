/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** sets the width of lines for polyline operations
 *
 *  @param handle Device handle
 *  @param width requested line width
 *
 *  @return selected line width, which is always an odd value (1, 3, 5 or ...),
 *          which means that even values are rounded down.
 *
 *  @since all VDI versions
 *
 *  @note 
 *  The line width is always in relation to the horizontal pixel size
 *  (if the aspect ratio is not 1:1, the height is corrected so that a
 *  horizontal and a vertical line seem to have the same width, though 
 *  horizontal and vertical pixel size are different - e.g. in ST mid ). 
 *  
 *  Most device drivers ignore the line type and draw solid lines 
 *  if the line is more than one pixel wide.
 *
 */

/* binding note: width (requested and selected) are in ptsin and ptsout arrays.
   This is not an error !
   BTW, intin and intout arrays would have been a better choice */

short
vsl_width (short handle, short width)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_ptsin[2];   
	short vdi_ptsout[2]; 
	VDI_PARAMS(vdi_control, 0L, vdi_ptsin, vdi_dummy, vdi_ptsout );
#endif
	
	vdi_ptsin[0] = width;
	vdi_ptsin[1] = 0;

	VDI_TRAP (vdi_params, handle, 16, 1,0);

	return vdi_ptsout[0];
}

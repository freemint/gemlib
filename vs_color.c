/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** Set Color Representation
 *
 *  @param handle Device handle
 *  @param index color index (pen)
 *  @param rgb contain the intensity of red, green, blue as following:
 *         - rgb[0] : Red color intensity (in tenths percent, 0-1000).
 *         - rgb[1] : Green color intensity.
 *         - rgb[2] : Blue color intensity
 *
 *  @since all VDI versions
 *
 *  This function sets the RGB color associated with a color index. The intensity 
 *  of red, green and blue is set in per mille (0-1000). If the device driver has 
 *  a CLUT, the new setting will immediately change the color of all pixels with 
 *  color index \p index.
 *
 *  If a device has more than 256 simultaneously displayable colors, it usually 
 *  does not have a CLUT. In this case the pixels do not contain a color value or 
 *  index but a direct color value in RGB (e.g. a pixel with 32 bits has 8 unused 
 *  bits, 8 bits for red, 8 bits for green and 8 bits for blue). This means that
 *  the VDI creates a pseudo CLUT with 256 pens and calling vs_color() for one of 
 *  these pens will not change the color of the pixels which have been drawn with 
 *  this pen, but it will change the color of new pixels drawn with this pen. 
 *  Note that the palettes are handled per workstation which means, that each 
 *  workstation has its own palette (pseudo CLUT) and changing the RGB value for 
 *  a color index on one workstation will not change the value of the same pen 
 *  in another workstation. 
 *
 *
 */

void
vs_color (short handle, short index, const short rgb[])
{
	short *ptr;
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[4];   
	
	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_dummy, vdi_dummy );
	
	ptr = vdi_intin;
	*(ptr ++) = index;		       /* vdi_intin[0] = index */
	*(ptr ++) = *(rgb ++);	       /* vdi_intin[1] = rgb[0] */
	*(ptr ++) = *(rgb ++);	       /* vdi_intin[2] = rgb[1] */
	*(ptr   ) = *(rgb   );	       /* vdi_intin[3] = rgb[2] */

	VDI_TRAP (vdi_params, handle, 14, 0,4);
}

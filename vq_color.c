/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** returns the RGB color intensity for a color
 *  index. You can either request the realized intensities or you can get the 
 *  intensities you tried to set with vs_color().
 *
 *  @param handle Device handle
 *  @param index color index (pen)
 *  @param flag defined as follow:
 *         - 0: return color values requested at vs_color()
 *         - 1: return realized color values
 *  @param rgb intensity of red, green, blue
 *
 *  @return color index
 *
 *  @since all VDI versions
 *
 *  @ note
 *  The color value you try to set via vs_color() can differ form the realized 
 *  color value because a CLUT usually has less than 1000 levels per color 
 *  component (e.g. 8 bit - 256 levels - per component).
 *  Most drivers for direct color devices return only the realized RGB value 
 *  because the number of levels is sufficient.
 *
 */

short
vq_color (short handle, short index, short flag, short rgb[])
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[2];   
	short vdi_intout[4]; 

	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_intout, vdi_dummy );
	
	vdi_intin[0] = index;
	vdi_intin[1] = flag;
	
	VDI_TRAP (vdi_params, handle, 26, 0,2);
	
	rgb[0] = vdi_intout[1];
	rgb[1] = vdi_intout[2];
	rgb[2] = vdi_intout[3];
	
	return vdi_intout[0];
}

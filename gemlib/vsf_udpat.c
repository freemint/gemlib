/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** is the function which allows you to set a 
 *  user-defined 16*16 pixel pattern.
 *
 *  @param handle Device handle
 *  @param pat For the pattern data, bit 15 of word 1 is the
 *	       upper left bit of the pattern. Bit 0 of word
 *	       16 is the lower right bit of the pattern. Bit
 *	       zero is the Least Significant Bit of the word.
 *	       Words are stored in the same format as 16-bit
 *	       integers (ie pat[0] correspond to the top line of the pattern, and
 *         pat[15] correspond to the bottom line of the pattern). \n
 *	       For a single plane pattern, a bit value of 1
 *	       indicates foreground color. A bit value of 0
 *	       indicates the background color. The color used
 *	       for the foreground is determined by the current
 *	       fill area color index.\n
 *	       Patterns with multiple colors have to be
 *	       stored in standard format and must have the same number of planes as the
 *	       device. Exception: If the device is a Hicolor or Truecolor device (direct
 *	       color mapping) you always pass a pattern width 32-bit pixels (xrgb).\n
 *	       Note that the
 *	       writing mode must be set to replace (mode MR_REPLACE = 1),
 *	       when using a multiplane fill pattern.
 *  @param planes 
 *
 *  @since all VDI versions
 *
 *  @note If you use a pattern with multiple colors you should select color index 1 and 
 *        writing mode 1.
 *
 */

void
vsf_udpat (short handle, short pat[], short planes)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	VDI_PARAMS(vdi_control, pat, 0L, 0L, 0L );
#else
	vdi_params.intin = pat;
#endif
		
	VDI_TRAP (vdi_params, handle, 112, planes *16,0);

#if !(USE_LOCAL_VDIPB)
	vdi_params.intin = vdi_intin;
#endif
}

#include "gem_vdiP.h"

/** sets the style index based on the fill interior style. This index has no
 *	effect if the interior style is hollow, solid, or user-defined.
 *
 *  @param handle Device handle
 *  @param style requested style index, range from 1 to a
 * 	       device-dependent maximum. If the requested
 *		   index is not available, GEM VDI uses index
 *		   style 1.The index references a hatch style if
 *		   the selected fill interior style is hatch, or a
 *		   pattern if the selected interior fill style is
 *		   pattern.
 *
 *  @return selected style index
 *
 *  @since all VDI versions
 *
 *
 */

short
vsf_style (short handle, short style)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[1]; 
	
	VDI_PARAMS(vdi_control, &style, 0L, vdi_intout, vdi_dummy );
	
	VDI_TRAP (vdi_params, handle, 24, 0,1);

	return vdi_intout[0];
}

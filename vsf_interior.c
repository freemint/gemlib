#include "gem_vdiP.h"

/** selects the fill type for filled graphic objects
 *
 *  @param handle Device handle
 *  @param style requested fill type :
 *         - FIS_HOLLOW (0) : fills the interior with the current
 *           background color (index 0).
 *         - FIS_SOLID (1) : fills
 *			 the area with the currently selected fill color.
 *         - FIS_PATTERN (2)
 *         - FIS_HATCH (3)
 *         - FIS_USER (4)
 *         .
 *         If the 
 *         requested type is invalid, type 0 (hollow) will be selected.
 *
 *  @return selected fill type
 *
 *  @since all VDI versions
 *
 */

short
vsf_interior (short handle, short style)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[1]; 
	
	VDI_PARAMS(vdi_control, &style, 0L, vdi_intout, vdi_dummy );
	
	VDI_TRAP (vdi_params, handle, 23, 0,1);

	return vdi_intout[0];
}

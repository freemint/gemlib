/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** sets the line type for polyline operations
 *
 *  @param handle Device handle
 *  @param style requested line type :
 *         - SOLID (1) : \p %1111111111111111 (solid line)
 *         - LDASHED (2) : \p %1111111111110000  (long dash)
 *         - DOTTED (3) : \p %1110000011100000  (dots)
 *         - DASHDOT (4) : \p %1111111100011000  (dash, dot)
 *         - DASH (5) : \p %1111111100000000  (dash)
 *         - DASHDOTDOT (6) : \p %1111000110011000  (dash, dot, dot)
 *         - USERLINE (7) : user-defined, via vsl_udsty()
 *         .
 *         If the 
 *         requested line type is not available, line type 1 will be selected (solid).
 *
 *  @return realized line type
 *
 *  @since all VDI versions
 *
 */

short
vsl_type (short handle, short style)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[1]; 
	VDI_PARAMS(vdi_control, &style, 0L, vdi_intout, vdi_dummy );
#else
	vdi_intin[0] = style;
#endif
	
	VDI_TRAP (vdi_params, handle, 15, 0,1);

	return vdi_intout[0];
}

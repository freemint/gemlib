/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** turns the outline of a filled area (rectangle, polygone, ellipse, ...)
 *  on or off, and set the line type for this outline.
 *
 *  @param handle Device handle
 *  @param vis perimeter flag
 *         - PERIMETER_OFF (0) : invisible
 *         - PERIMETER_ON (1) : visible
 *         .
 *         Any nonzero value of
 *	       the visibility flag causes the perimeter to be visible.
 *  @param style same as vsl_type().
 *
 *  @return perimeter flag
 *
 *  @since PC/GEM3
 *
 *  This call is similar to vsf_perimeter(), but one can choose the line type used
 *  to draw the perimeter. vsf_perimeter() only allow to draw solid lines.
 *
 */

short
vsf_perimeter3 (short handle, short vis, short style)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[1]; 
	short vdi_intin[2]; 
	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_intout, 0L );
#endif

	vdi_intin[0] = vis;
	vdi_intin[1] = style;

	VDI_TRAP (vdi_params, handle, 104, 0,2);

	return vdi_intout[0];
}

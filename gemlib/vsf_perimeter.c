/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** turns the outline of a filled area (rectangle, polygone, ellipse, ...)
 *  on or off.
 *
 *  @param handle Device handle
 *  @param vis perimeter flag
 *         - PERIMETER_OFF (0) : invisible
 *         - PERIMETER_ON (1) : visible
 *         .
 *         Any nonzero value of
 *	       the visibility flag causes the perimeter to be visible.
 *
 *  @return perimeter flag
 *
 *  @since all VDI versions
 *
 *  When visibility is on (the
 *	default at Open Workstation) the border of a
 *	fill area is drawn in the current fill area
 *	color with a solid line. When visibility is
 *	off, no outline is drawn.
 *
 */

short
vsf_perimeter (short handle, short vis)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[1]; 
	VDI_PARAMS(vdi_control, &vis, 0L, vdi_intout, vdi_dummy );
#else
	vdi_intin[0] = vis;
#endif

	VDI_TRAP (vdi_params, handle, 104, 0,1);

	return vdi_intout[0];
}

/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** draws a filled area, for example a complex polygon.
 *
 *  @param handle Device handle
 *  @param count 
 *  @param pxy coordinates
 *
 *  @since all VDI versions
 *
 *  The area is filled using the
 *	following current attributes:
 *	 - fill area color
 *	 - interior style (hollow, solid, pattern, hatch
 *	   or user-defined)
 *	 - writing mode
 *	 - style index
 *
 *	The area is outlined with a solid line of the
 *	current fill area color if the fill area
 *	perimeter visibility is on, which is the
 *	default at Open Workstation. *
 *
 */

void
v_fillarea (short handle, short count, short pxy[])
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	VDI_PARAMS(vdi_control, 0L, pxy, 0L, 0L );
#else
	vdi_params.ptsin = pxy;
#endif
	
	VDI_TRAP (vdi_params, handle, 9, count,0);

#if !(USE_LOCAL_VDIPB)
	vdi_params.ptsin = vdi_ptsin;
#endif
}

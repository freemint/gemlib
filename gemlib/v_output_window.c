/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** This escape is required only for printers.
 *  It allows the application to request that a
 *  particular rectangular window of the picture be
 *  output to the printer. This escape is similar
 *  to the Update Workstation function, except that
 *  the rectangular area must be specified.
 *
 *  @param handle Device handle
 *  @param pxy window to be output
 *
 *  @since all VDI versions
 *
 *  Note that use of this function does not always
 *  guarantee that adjacent pictures will abut.
 *  Pictures will abut with a resolution of one
 *  printer head height.
 *
 *
 */

void
v_output_window (short handle, short *pxy)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		0L,                          /* vdi_intin   */
		pxy,                         /* vdi_ptsin   */
		0L,                          /* vdi_intout  */
		0L                           /* vdi_ptsout  */
	};
#else
	vdi_params.ptsin = pxy;
#endif
	
	VDI_TRAP_ESC (vdi_params, handle, 5,21, 2,0);

#if !(USE_LOCAL_VDIPB)
	vdi_params.ptsin = vdi_ptsin;
#endif
}

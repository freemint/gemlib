/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** returns the number of the function key pressed
 *
 *  @param handle Device handle
 *  @param cin initialisierende Taste (0)
 *  @param cout ausgew„hlte Funktionstaste
 *
 *  @since all VDI versions
 */


void
vrq_choice (short handle, short cin, short *cout)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		&cin,                        /* vdi_intin   */
		0L,                          /* vdi_ptsin   */
		cout,                        /* vdi_intout  */
		0L                           /* vdi_ptsout  */
	};
#else
	vdi_intin[0] = cin;
#endif
	
	VDI_TRAP (vdi_params, handle, 30, 0,1);
	
#if !(USE_LOCAL_VDIPB)
	*cout = vdi_intout[0];
#endif
}

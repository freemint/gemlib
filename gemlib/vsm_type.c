/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** selects the kind of marker for v_pmarker().
 *
 *  @param handle Device handle
 *  @param symbol requested marker type. If the 
 *         requested marker kind is not available, type 3 is used.
 *         The total number of markers available is device
 *		   dependent, but GEM VDI always defines at least
 *		   six marker types:
 *	       - MRKR_DOT (1) : dot
 *	       - MRKR_PLUS (2) : plus
 *	       - MRKR_ASTERISK (3) : asterisk
 *	       - MRKR_BOX (4) : square
 *	       - MRKR_CROSS (5) : diagonal cross
 *	       - MRKR_DIAMOND (6) : diamond
 *	       - (7..n) : device-dependent
 *
 *  @return selected marker type
 *
 *  @since all VDI versions
 *
 */

short
vsm_type (short handle, short symbol)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[1]; 
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		&symbol,                     /* vdi_intin   */
		0L,                          /* vdi_ptsin   */
		&vdi_intout[0],              /* vdi_intout  */
		0L                           /* vdi_ptsout  */
	};
#else
	vdi_intin[0] = symbol;
#endif
	
	VDI_TRAP (vdi_params, handle, 18, 0,1);

	return vdi_intout[0];
}

/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "gemx.h"

/** allows the caller to set a user-defined track kerning
 *
 *  @param handle Device handle
 *  @param offset offset in 1/65536 pixels.
 *  @param pairmode pair kerning on (1) or off (0)
 *  @param tracks track kerning mode
 *  @param pairs number of kerning pairs
 *
 *  @since NVDI 3.00
 *
 */

void
vst_track_offset (short handle, long offset, short pairmode,
                  short *tracks, short *pairs)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[4];   
	short vdi_intout[2]; 
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		&vdi_intin[0],               /* vdi_intin   */
		0L,                          /* vdi_ptsin   */
		&vdi_intout[0],              /* vdi_intout  */
		0L                           /* vdi_ptsout  */
	};
#endif
	
	vdi_intin[0]          = 255;
	vdi_intin[1]          = pairmode;
	*(long*)&vdi_intin[2] = offset;
	
	VDI_TRAP (vdi_params, handle, 237, 0,4);
	
	*tracks = vdi_intout[0];
	*pairs  = vdi_intout[1];
}

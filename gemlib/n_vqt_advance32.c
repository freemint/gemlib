/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** This call returns the advance vector of a character which can be used to place 
 *  the next one (the advance width is not the width of the character bitmap!).
 *
 *  @param handle Device handle
 *  @param ch character index
 *  @param advx x advance in 1/65536 pixels
 *  @param advy y advance in 1/65536 Pixels
 *
 *  @since NVDI 3.00
 *
 *  @note
 *  Remember that \p advx and \p advy are only offsets used to place 
 *  the next character - they do not include parts of the character which extend 
 *  beyond the em square.
 *  
 *
 */

void
vqt_advance32 (short handle, short ch, long *advx, long *advy)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_ptsout[8]; 
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		&ch,                         /* vdi_intin   */
		0L,                          /* vdi_ptsin   */
		0L,                          /* vdi_intout  */
		&vdi_ptsout[0]               /* vdi_ptsout  */
	};
#else
	vdi_intin[0] = ch;
#endif
	
	VDI_TRAP (vdi_params, handle, 247, 0,2);

	*advx = *(long*)&vdi_ptsout[4];
	*advy = *(long*)&vdi_ptsout[6];
}

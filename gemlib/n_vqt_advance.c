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
 *  @param advx x advance in pixels
 *  @param advy y advance in pixels
 *  @param xrem x remainder (mod 16384)
 *  @param yrem y remainder (mod 16384)
 *
 *  @since NVDI 3.00
 *
 *  @note
 *  The values \p advx .. \p yrem are returned for compatibility's sake only. Do 
 *  not use them! You should use \p x_advance and \p y_advance from vqt_advance32().
 *  
 *
 */

void
vqt_advance (short handle, short ch,
             short *advx, short *advy, short *xrem, short *yrem)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_ptsout[8]; 
	VDI_PARAMS(vdi_control, &ch, 0L, 0L, vdi_ptsout);
#else
	vdi_intin[0] = ch;
#endif
	
	VDI_TRAP (vdi_params, handle, 247, 0,1);

	*advx = vdi_ptsout[0];
	*advy = vdi_ptsout[1];
	*xrem = vdi_ptsout[2];
	*yrem = vdi_ptsout[3];
}

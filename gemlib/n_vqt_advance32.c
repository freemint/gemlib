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
 *  @param advx x advance in 1/65536 pixels \n
 *         [option CHECK_NULLPTR] advx may be NULL
 *  @param advy y advance in 1/65536 Pixels \n
 *         [option CHECK_NULLPTR] advy may be NULL
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
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_ptsout[8]; 

	VDI_PARAMS(vdi_control, &ch, 0L, vdi_dummy, vdi_ptsout);
	
	VDI_TRAP (vdi_params, handle, 247, 0,1);

#if CHECK_NULLPTR
	if (advx)
#endif
	*advx = *(long*)&vdi_ptsout[4];
#if CHECK_NULLPTR
	if (advy)
#endif
	*advy = *(long*)&vdi_ptsout[6];
}

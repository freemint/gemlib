/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** This function sets the character width in pixels. The next call of vst_height(), 
 *  vst_point() or vst_arbpt32() resets the width.
 *
 *  @param handle Device handle
 *  @param width requested width
 *  @param char_width selected character width
 *  @param char_height selected character height
 *  @param cell_width selected character cell width
 *  @param cell_height selected character cell height
 *
 *  @since NVDI 3.00
 *
 *  @note
 *  You should use vst_setsize32() instead of vst_width() because vst_width() uses 
 *  only an integer value as relative width and it therefore does not offer the 
 *  necessary accuracy.
 *  
 *
 */

void
vst_width (short handle, short width, short *char_width, short *char_height,
           short *cell_width, short *cell_height)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_ptsin[2];   
	short vdi_ptsout[4]; 
	VDI_PARAMS(vdi_control, 0L, vdi_ptsin, 0L, vdi_ptsout);
#endif
	
	vdi_ptsin[0] = width;
	
	VDI_TRAP (vdi_params, handle, 231, 1,0);
	
	*char_width  = vdi_ptsout[0];
	*char_height = vdi_ptsout[1];
	*cell_width  = vdi_ptsout[2];
	*cell_height = vdi_ptsout[3];
}

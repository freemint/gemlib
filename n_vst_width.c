#include "gem_vdiP.h"
#include "mt_gemx.h"

/** This function sets the character width in pixels. The next call of vst_height(), 
 *  vst_point() or vst_arbpt32() resets the width.
 *
 *  @param handle Device handle
 *  @param width requested width
 *  @param char_width selected character width \n
 *         [option CHECK_NULLPTR] char_width may be NULL
 *  @param char_height selected character height \n
 *         [option CHECK_NULLPTR] char_height may be NULL
 *  @param cell_width selected character cell width \n
 *         [option CHECK_NULLPTR] cell_width may be NULL
 *  @param cell_height selected character cell height \n
 *         [option CHECK_NULLPTR] cell_height may be NULL
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
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_ptsin[2];   
	short vdi_ptsout[4]; 

	VDI_PARAMS(vdi_control, 0L, vdi_ptsin, vdi_dummy, vdi_ptsout);
	
	vdi_ptsin[0] = width;
	
	VDI_TRAP (vdi_params, handle, 231, 1,0);
	
#if CHECK_NULLPTR
	if (char_width)
#endif
	*char_width  = vdi_ptsout[0];
#if CHECK_NULLPTR
	if (char_height)
#endif
	*char_height = vdi_ptsout[1];
#if CHECK_NULLPTR
	if (cell_width)
#endif
	*cell_width  = vdi_ptsout[2];
#if CHECK_NULLPTR
	if (cell_height)
#endif
	*cell_height = vdi_ptsout[3];
}

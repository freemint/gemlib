/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** sets the character height in pixels
 *
 *  @param handle Device handle
 *  @param height requested character height. The height is specified as the 
 *         distance between baseline and the top of the character cell.
 *  @param charw selected character width
 *  @param charh selected character height
 *  @param cellw selected character cell width
 *  @param cellh selected character cell height
 *
 *  @return AFAIK, nothing... who know what VDI puts in vdi_intout[0] ?
 *
 *  @since all VDI versions
 *
 *  @note NVDI doc says that if the font is a bitmap and the requested height does
 *        not exist, the VDI scales the bitmap.\n
 *        original VDI doc says that if the desired character height does not map
 *        exactly to a device size, GEM VDI selects the
 *        closest character size that does not exceed the
 *        requested size.
 *
 *  @note NVDI doc says that if the font is a vector font, \p char_width and \p cell_width
 *        are not the exact 
 *        character widths but only rounded values.\n
 *        original VDI doc says that For
 *        proportional faces, GEM VDI returns the width
 *        of the widest character and the width of the
 *        widest character cell in the face.
 *
 */

void
vst_height (short handle, short height,
            short *charw, short *charh, short *cellw, short *cellh)
{
	short *ptr;
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_ptsin[2];   
	short vdi_ptsout[4]; 
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		0L,                          /* vdi_intin   */
		&vdi_ptsin[0],               /* vdi_ptsin   */
		0L,                          /* vdi_intout  */
		&vdi_ptsout[0]               /* vdi_ptsout  */
	};
#endif
	
	vdi_ptsin[0] = 0;
	vdi_ptsin[1] = height;

	VDI_TRAP (vdi_params, handle, 12, 1,0);

	ptr = vdi_ptsout;
	*charw = *(ptr ++);			 				 /* *charw = vdi_ptsout[0] */
	*charh = *(ptr ++);			 				 /* *charh = vdi_ptsout[1] */
	*cellw = *(ptr ++);			 				 /* *cellw = vdi_ptsout[2] */
	*cellh = *(ptr);			 				 /* *cellh = vdi_ptsout[3] */
}

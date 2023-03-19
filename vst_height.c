#include "gem_vdiP.h"

/** sets the character height in pixels
 *
 *  @param handle Device handle
 *  @param height requested character height. The height is specified as the 
 *         distance between baseline and the top of the character cell.
 *  @param charw selected character width \n
 *         [option CHECK_NULLPTR] charw may be NULL
 *  @param charh selected character height \n
 *         [option CHECK_NULLPTR] charh may be NULL
 *  @param cellw selected character cell width \n
 *         [option CHECK_NULLPTR] cellw may be NULL
 *  @param cellh selected character cell height \n
 *         [option CHECK_NULLPTR] cellh may be NULL
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
#if !(CHECK_NULLPTR)
	short *ptr;
#endif
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_ptsin[2];   
	short vdi_ptsout[4]; 
	
	VDI_PARAMS(vdi_control, 0L, vdi_ptsin, vdi_dummy, vdi_ptsout );
	
	vdi_ptsin[0] = 0;
	vdi_ptsin[1] = height;

	VDI_TRAP (vdi_params, handle, 12, 1,0);

#if CHECK_NULLPTR
	if (charw) *charw = vdi_ptsout[0];
	if (charh) *charh = vdi_ptsout[1];
	if (cellw) *cellw = vdi_ptsout[2];
	if (cellh) *cellh = vdi_ptsout[3];
#else
	ptr = vdi_ptsout;
	*charw = *(ptr ++);			 				 /* *charw = vdi_ptsout[0] */
	*charh = *(ptr ++);			 				 /* *charh = vdi_ptsout[1] */
	*cellw = *(ptr ++);			 				 /* *cellw = vdi_ptsout[2] */
	*cellh = *(ptr);			 				 /* *cellh = vdi_ptsout[3] */
#endif
}

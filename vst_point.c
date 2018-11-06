#include "gem_vdiP.h"

/** sets the character cell height in points (1 pt  = 1/72").
 *  For bitmap font this function selects the closest height which is smaller or 
 *  equal to the requested size. If the font is a vector font, only predefined 
 *  heights can be selected (usually 8, 9, 10, 11, 12, 14, 18, 24, 36, and 48 pt).
 *
 *  @param handle Device handle
 *  @param point requested character cell height (1/72").
 *         The specified height is the
 *         distance between the baseline of one line of
 *         text and the baseline of the next line of text,
 *         which is the character cell height.
 *  @param charw selected character width
 *  @param charh selected character height
 *  @param cellw selected character cell width
 *  @param cellh selected character cell height
 *
 *  @return selected character cell height (1/72")
 *
 *  @since all VDI versions
 *
 */

short
vst_point (short handle, short point,
           short *charw, short *charh, short *cellw, short *cellh)
{
#if !(CHECK_NULLPTR)
	short *ptr;
#endif
	short vdi_control[VDI_CNTRLMAX];
	short vdi_intout[1];
	short vdi_ptsout[4];
	
	VDI_PARAMS(vdi_control, &point, 0L, vdi_intout, vdi_ptsout );
	
	VDI_TRAP (vdi_params, handle, 107, 0,1);

#if CHECK_NULLPTR
	if (charw) *charw = vdi_ptsout[0];
	if (charh) *charh = vdi_ptsout[1];
	if (cellw) *cellw = vdi_ptsout[2];
	if (cellh) *cellh = vdi_ptsout[3];
#else
	ptr = vdi_ptsout;
	*charw = *(ptr ++);				    	/* *charw = vdi_ptsout[0] */
	*charh = *(ptr ++);				    	/* *charh = vdi_ptsout[1] */
	*cellw = *(ptr ++);				    	/* *cellw = vdi_ptsout[2] */
	*cellh = *(ptr);				    	/* *cellh = vdi_ptsout[3] */
#endif

	return vdi_intout[0];
}

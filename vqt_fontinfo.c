/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** returns size information for the current font. Special effects and 
 *  enlargment are taken into account.
 *
 *  @param handle Device handle
 *  @param minade minimum character index \n
 *         [option CHECK_NULLPTR] minade may be NULL
 *  @param maxade maximum character index \n
 *         [option CHECK_NULLPTR] maxade may be NULL
 *  @param distances 
 *         - distances[0]: distance of bottom line and baseline
 *         - distances[1]: distance of descent line and baseline
 *         - distances[2]: distance of half line and baseline
 *         - distances[3]: distance of ascent line and basline
 *         - distances[4]: distance of top line and baseline
 *         .
 *         [option CHECK_NULLPTR] distances may be NULL
 *  @param maxwidth maximum character cell width \n
 *         [option CHECK_NULLPTR] maxwidth may be NULL
 *  @param effects 
 *         - effects[0]: additional character width due to text effects
 *         - effects[1]: left offset of skewed text
 *         - effects[2]: right offset of skewed text
 *         .
 *         [option CHECK_NULLPTR] effects may be NULL
 *
 *  @since all VDI versions
 *
 */

void
vqt_fontinfo (short handle, short *minade, short *maxade, short distances[],
              short *maxwidth, short effects[])
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[2]; 
	short vdi_ptsout[10]; 
	
	VDI_PARAMS(vdi_control, 0L, 0L, vdi_intout, vdi_ptsout );
	
	VDI_TRAP_00 (vdi_params, handle, 131);

#if CHECK_NULLPTR
	if (minade)
#endif
	*minade   = vdi_intout[0];
#if CHECK_NULLPTR
	if (maxade)
#endif
	*maxade   = vdi_intout[1];
#if CHECK_NULLPTR
	if (maxwidth)
#endif
	*maxwidth = vdi_ptsout[0];

#if CHECK_NULLPTR
	if (distances) {
#endif
	distances[0] = vdi_ptsout[1];
	distances[1] = vdi_ptsout[3];
	distances[2] = vdi_ptsout[5];
	distances[3] = vdi_ptsout[7];
	distances[4] = vdi_ptsout[9];
#if CHECK_NULLPTR
	}
#endif

#if CHECK_NULLPTR
	if (effects) {
#endif
	effects[0] = vdi_ptsout[2];
	effects[1] = vdi_ptsout[4];
	effects[2] = vdi_ptsout[6];
#if CHECK_NULLPTR
	}
#endif
}

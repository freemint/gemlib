/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** sets the horizontal and vertical alignment for graphic text
 *
 *  @param handle Device handle
 *  @param hin requested horizontal alignment. If an 
 *         invalid horizontal alignment is requested, the text will be left justified.
 *         - TA_LEFT (0) : left justified
 *         - TA_CENTER (1) : centered
 *         - TA_RIGHT (2) : right justified
 *  @param vin requested vertical alignment. If an invalid vertical alignment is
 *         requested, the text will be aligned to the baseline.
 *         - TA_BASE (0) : baseline
 *         - TA_HALF (1) : half line
 *         - TA_ASCENT (2) : ascent line
 *         - TA_BOTTOM (3) : bottom
 *         - TA_DESCENT (4) : descent
 *         - TA_TOP (5) : top
 *  @param hout selected horizontal alignment
 *  @param vout selected vertical alignment
 *
 *  @since all VDI versions
 *
 */

void
vst_alignment (short handle, short hin, short vin, short *hout, short *vout)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[2];   
	short vdi_intout[2]; 
	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_intout, 0L  );
#endif
	
	vdi_intin[0] = hin;
	vdi_intin[1] = vin;

	VDI_TRAP (vdi_params, handle, 39, 0,2);

	*hout = vdi_intout[0];
	*vout = vdi_intout[1];
}

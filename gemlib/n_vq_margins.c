/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** 
 *
 *  @param handle Device handle
 *  @param top_margin 
 *  @param bottom_margin 
 *  @param left_margin 
 *  @param right_margin 
 *  @param hdpi 
 *  @param vdpi 
 *
 *  @return 
 *
 *  @since NVDI 5 ?
 *
 *
 *
 */

short
vq_margins (short handle, short *top_margin, short *bottom_margin,
            short *left_margin, short *right_margin, short *hdpi, short *vdpi)
{
#if USE_LOCAL_VDIPB
	/* todo (doc wanted) */
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[VDI_INTOUTMAX]; 
	short vdi_ptsout[VDI_PTSOUTMAX]; 
	VDI_PARAMS(vdi_control, 0L, 0L, vdi_intout, vdi_ptsout);
#endif
	
	vdi_intout[0] = 0;

	VDI_TRAP_ESC (vdi_params, handle, 5,2100, 0,0);

	*top_margin    = vdi_intout[1];
	*bottom_margin = vdi_intout[2];
	*left_margin   = vdi_intout[3];
	*right_margin  = vdi_intout[4];
	*hdpi          = vdi_intout[5];
	*vdpi          = vdi_intout[6];

	return vdi_intout[0];
}

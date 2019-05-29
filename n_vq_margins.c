#include "gem_vdiP.h"
#include "mt_gemx.h"

/** 
 *
 *  @param handle Device handle
 *  @param top_margin top margin in pixels
 *  @param bottom_margin bottom margin in pixels
 *  @param left_margin left margin in pixels
 *  @param right_margin right margin in pixels
 *  @param hdpi horizontal dpi resolution
 *  @param vdpi vertical dpi resolution
 *
 *  @return 0 if this function is not supported by the driver, any other value if
 *          the driver support this function.
 *
 *  @since depend of the driver
 *
 *
 *
 */

short
vq_margins (short handle, short *top_margin, short *bottom_margin,
            short *left_margin, short *right_margin, short *hdpi, short *vdpi)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[7]; 

	VDI_PARAMS(vdi_control, 0L, 0L, vdi_intout, vdi_dummy);
	
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

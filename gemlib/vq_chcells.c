/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** This call returns the number of columns and rows/lines of the text screen
 *
 *  @param handle Device handle
 *  @param n_rows number of lines
 *  @param n_cols number of columns \n
 *         If \p n_rows and \p n_cols are 0, the device does not support
 *         text mode.
 *
 *  @since all VDI versions
 *
 */

void
vq_chcells (short handle, short *n_rows, short *n_cols)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[2]; 
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		0L,                          /* vdi_intin   */
		0L,                          /* vdi_ptsin   */
		&vdi_intout[0],              /* vdi_intout  */
		0L                           /* vdi_ptsout  */
	};
#endif
	
	VDI_TRAP_ESC (vdi_params, handle, 5,1, 0,0);
	
	*n_rows = vdi_intout[0];
	*n_cols = vdi_intout[1];
}

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
	VDI_PARAMS(vdi_control, 0L, 0L, vdi_intout, 0L );
#endif
	
	VDI_TRAP_ESC (vdi_params, handle, 5,1, 0,0);
	
	*n_rows = vdi_intout[0];
	*n_cols = vdi_intout[1];
}

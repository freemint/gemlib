/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** This call returns the number of columns and rows/lines of the text screen
 *
 *  @param handle Device handle
 *  @param n_rows number of lines \n
 *         [option CHECK_NULLPTR] n_rows may be NULL
 *  @param n_cols number of columns  \n
 *         [option CHECK_NULLPTR] n_cols may be NULL\n
 *  
 *  @note  If \p n_rows and \p n_cols are 0, the device does not support
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
	VDI_PARAMS(vdi_control, 0L, 0L, vdi_intout, vdi_dummy );
#endif
	
	VDI_TRAP_ESC (vdi_params, handle, 5,1, 0,0);
	
#if CHECK_NULLPTR
	if (n_rows)
#endif
	*n_rows = vdi_intout[0];
#if CHECK_NULLPTR
	if (n_cols)
#endif
	*n_cols = vdi_intout[1];
}

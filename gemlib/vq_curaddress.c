/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** This call returns the current cursor position
 *
 *  @param handle Device handle
 *  @param cur_row (1 to the maximum number of rows) \n
 *         [option CHECK_NULLPTR] cur_row may be NULL
 *  @param cur_col (1 to the maximum number of columns) \n
 *         [option CHECK_NULLPTR] cur_col may be NULL
 *
 *  @since all VDI versions
 *
 */

void
vq_curaddress (short handle, short *cur_row, short *cur_col)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[2]; 

	VDI_PARAMS(vdi_control, 0L, 0L, vdi_intout, vdi_dummy );
	
	VDI_TRAP_ESC (vdi_params, handle, 5,15, 0,0);
	
#if CHECK_NULLPTR
	if (cur_row)
#endif
	*cur_row = vdi_intout[0];
#if CHECK_NULLPTR
	if (cur_col)
#endif
	*cur_col = vdi_intout[1];
}

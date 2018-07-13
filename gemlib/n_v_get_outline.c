/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** 
 *
 *  @param handle Device handle
 *  @param index 
 *  @param x_offset 
 *  @param y_offset 
 *  @param pts 
 *  @param flags 
 *  @param max_pts 
 *
 *  @return 
 *
 *  @since NVDI 5 ?
 *
 *
 *
 */

short
v_get_outline (short handle, short index, short x_offset, short y_offset,
               short *pts, char *flags, short max_pts)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[4 + 2 * N_PTRINTS];
	short vdi_intout[1]; 

	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_intout, vdi_dummy);
	
	vdi_intin    [0] = index;
	vdi_intin    [1] = max_pts;
	vdi_intin_ptr(2, short *) = pts;
	vdi_intin_ptr(2 + N_PTRINTS, char *) = flags;
	vdi_intin    [2 + 2 * N_PTRINTS] = x_offset;
	vdi_intin    [3 + 2 * N_PTRINTS] = y_offset;

	VDI_TRAP_ESC (vdi_params, handle, 243,1, 0, 4 + 2 * N_PTRINTS);

	return vdi_intout[0];
}

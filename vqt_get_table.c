#include "gem_vdiP.h"

/** 
 *
 *  @param handle Device handle
 *  @param map address of character allocation table
 *
 *  @since SpeedoGDOS 4.0
 *
 *
 *
 *
 */

void
vqt_get_table (short handle, short **map)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[VDI_INTOUTMAX]; /* todo (doc wanted) */
	short vdi_ptsout[VDI_PTSOUTMAX]; /* todo (doc wanted) */

	VDI_PARAMS(vdi_control, 0L, 0L, vdi_intout, vdi_ptsout);
	
	VDI_TRAP_00 (vdi_params, handle, 254);
	
	*map = vdi_intout_ptr(0, short *);
}

/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** 
 *
 *  @param handle Device handle
 *  @param index 
 *  @param color_space 
 *  @param color 
 *
 *  @return 
 *
 *  @since NVDI 5 ?
 *
 *
 *
 */

short
vs_ctab_entry (short handle, short index, long color_space, COLOR_ENTRY * color)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[7];   
	short vdi_intout[1]; 
	COLOR_ENTRY *ent;

	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_intout, vdi_dummy);
	
	vdi_intin                [0] = index;
	vdi_intin_long(1) = color_space;
	ent = (COLOR_ENTRY*)&vdi_intin[3];
	*ent = *color;

	VDI_TRAP_ESC (vdi_params, handle, 205,1, 0,7);

	return vdi_intout[0];
}

/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** draws a string with the selected text attributes.
 *
 *  @param handle Device handle
 *  @param x 
 *  @param y 
 *  @param str string
 *
 *  @since all VDI versions
 *
 *  If you have 
 *  selected a vector font, neither pair nor track kerning are used and the 
 *  character widths are non-fractional (that means the widths returned by 
 *  vqt_width()).
 *
 */

void
v_gtext (short handle, short x, short y, const char *str)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[VDI_INTINMAX];   
	short vdi_ptsin[2];   
	register short n = vdi_str2array (str, vdi_intin);

	VDI_PARAMS(vdi_control, vdi_intin, vdi_ptsin, vdi_dummy, vdi_dummy );

	vdi_ptsin[0]     = x;
	vdi_ptsin[1]     = y;
	
	VDI_TRAP (vdi_params, handle, 8, 1,n);
}

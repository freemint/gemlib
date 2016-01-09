/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "vdi_userdef.h"


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
 *  @note Use it for work with userdef, not reentrant function!
 */

void
udef_v_gtext (short handle, short x, short y, const char *str)
{
	short n = vdi_str2array_n (str, _VDIParBlk.vdi_intin, VDI_INTINMAX);

	VDI_PARAMS(_VDIParBlk.vdi_control, _VDIParBlk.vdi_intin, _VDIParBlk.vdi_ptsin, vdi_dummy, vdi_dummy );

	_VDIParBlk.vdi_ptsin[0]     = x;
	_VDIParBlk.vdi_ptsin[1]     = y;
	
	VDI_TRAP (vdi_params, handle, 8, 1,n);
}

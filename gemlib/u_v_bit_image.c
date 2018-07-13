/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "vdi_userdef.h"


/** UDEF version of v_bit_image(). See \ref overviewUDEF for details about UDEF feature
 */

void
udef_v_bit_image (short handle, const char *filename, short aspect, short x_scale,
             short y_scale, short h_align, short v_align, short *pxy)
{

	short n = 5 + vdi_str2array_n (filename, _VDIParBlk.vdi_intin + 5, VDI_INTINMAX-5);

	VDI_PARAMS(_VDIParBlk.vdi_control, _VDIParBlk.vdi_intin, pxy, vdi_dummy, vdi_dummy);

	_VDIParBlk.vdi_intin[0] = aspect;
	_VDIParBlk.vdi_intin[1] = x_scale;
	_VDIParBlk.vdi_intin[2] = y_scale;
	_VDIParBlk.vdi_intin[3] = h_align;
	_VDIParBlk.vdi_intin[4] = v_align;
	
	VDI_TRAP_ESC (vdi_params, handle, 5,23, 2,n);
}

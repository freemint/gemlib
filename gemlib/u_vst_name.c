/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"
#include "vdi_userdef.h"


/** UDEF version of vst_name(). See \ref overviewUDEF for details about UDEF feature
 */

short
udef_vst_name (short handle, short font_format, char *font_name, char *ret_name)
{
	short n = 1 + vdi_str2array_n (font_name, _VDIParBlk.vdi_intin + 1, VDI_INTINMAX-1);

	VDI_PARAMS(_VDIParBlk.vdi_control, _VDIParBlk.vdi_intin, 0L, _VDIParBlk.vdi_intout, vdi_dummy);

	_VDIParBlk.vdi_intin[0] = font_format;

	/* set the 0 as return value in case NVDI is not present */
	_VDIParBlk.vdi_intout[0] = 0;
	/* set the length to 0 for the same case */
	_VDIParBlk.vdi_control[4] = 0;

 	VDI_TRAP (vdi_params, handle, 230, 0,n);
	
#if CHECK_NULLPTR
	if (ret_name)
#endif
	vdi_array2str (_VDIParBlk.vdi_intout+1, ret_name, _VDIParBlk.vdi_control[4]-1);
	
	return _VDIParBlk.vdi_intout[0];
}

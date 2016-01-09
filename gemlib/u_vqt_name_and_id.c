/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"
#include "vdi_userdef.h"


/** This function searches the font specified by \p font_name and \p font_format. 
 *  Missing or extra spaces in the font name are ignored. If the font cannot be 
 *  found, return value is zero.
 *
 *  @param handle Device handle
 *  @param font_format possible font formats
 *         - 1: bitmap font
 *         - 2: Speedo font
 *         - 4: TrueType font
 *         - 8: Type 1 font
 *  @param font_name font name
 *  @param ret_name font name
 *
 *  @return font id or 0 on failure
 *
 *  @since NVDI 3.02
 *
 *  @note Use it for work with userdef, not reentrant function!
 *
 */


short
udef_vqt_name_and_id (short handle, short font_format, char *font_name, char *ret_name)
{
	short n = 1 + vdi_str2array_n (font_name, _VDIParBlk.vdi_intin+1, VDI_INTINMAX-1);

	VDI_PARAMS(_VDIParBlk.vdi_control, _VDIParBlk.vdi_intin, 0L, _VDIParBlk.vdi_intout, vdi_dummy);
	
	_VDIParBlk.vdi_intin[0]     = font_format;

	/* set the 0 as return value in case NVDI is not present */
	_VDIParBlk.vdi_intout[0] = 0;
	/* set the length to 0 for the same case */
	_VDIParBlk.vdi_control[4] = 0;
	
	VDI_TRAP_ESC (vdi_params, handle, 230,100, 0,n);
	
	vdi_array2str (_VDIParBlk.vdi_intout+1, ret_name, _VDIParBlk.vdi_control[4]-1);
	
	return _VDIParBlk.vdi_intout[0];
}

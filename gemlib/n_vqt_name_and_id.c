/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

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
 *  @return font id or 0
 *
 *  @since NVDI 3.02
 *
 *
 *
 */

short
vqt_name_and_id (short handle, short font_format, char *font_name, char *ret_name)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[VDI_INTINMAX];   
	short vdi_intout[VDI_INTOUTMAX]; 
	register short n = 1 + vdi_str2array (font_name, vdi_intin+1);

	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_intout, vdi_dummy);
	
	vdi_intin[0]     = font_format;
	
	VDI_TRAP_ESC (vdi_params, handle, 230,100, 0,n);
	
	vdi_array2str (vdi_intout+1, ret_name, vdi_control[4]-1);
	
	return vdi_intout[0];
}

/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** This function selects the font specified by \p font_name and \p font_format. 
 *  Missing or extra spaces in the font name are ignored. If the requested font 
 *  is not available, the system font is selected.
 *
 *  @param handle Device handle
 *  @param font_format possible font formats
 *         - 1: bitmap font
 *         - 2: Speedo font
 *         - 4: TrueType font
 *         - 8: Type 1 font
 *  @param font_name font name
 *  @param ret_name name of the selected font
 *
 *  @return selected font id
 *
 *  @since NVDI 3.02
 *
 */

short
vst_name (short handle, short font_format, char *font_name, char *ret_name)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[VDI_INTINMAX];   
	short vdi_intout[VDI_INTOUTMAX]; 
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		&vdi_intin[0],               /* vdi_intin   */
		0L,                          /* vdi_ptsin   */
		&vdi_intout[0],              /* vdi_intout  */
		0L                           /* vdi_ptsout  */
	};
#endif
	register short n = 1 + vdi_str2array (font_name, vdi_intin + 1);

	vdi_intin[0] = font_format;
	
	VDI_TRAP (vdi_params, handle, 230, 0,n);
	
	vdi_array2str (vdi_intout+1, ret_name, vdi_control[4]-1);
	
	return vdi_intout[0];
}

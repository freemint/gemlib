/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** is an extended version of vqt_name()
 *
 *  @param handle Device handle
 *  @param index index (1 - number of fonts)
 *  @param name 
 *         - name[0..31] : font name
 *         - name[32] :  0: bitmap font, 1: vector font
 *  @param font_format 
 *         - 1: bitmap font
 *         - 2: Speedo font
 *         - 4: TrueType font
 *         - 8: Type 1 font
 *  @param flags 
 *         - 0: proportional font
 *         - 1: monospaced font
 *
 *  @return font id
 *
 *  @since NVDI 3.00
 *
 *
 *
 */

short
vqt_ext_name (short handle, short index,
              char *name, short *font_format, short *flags)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[2];   
	short vdi_intout[35]; 
	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_intout, vdi_dummy);
#endif
	
	vdi_intin[0] = index;
	vdi_intin[1] = 0;

	VDI_TRAP_ESC (vdi_params, handle, 130,1, 0,2);

	vdi_array2str (vdi_intout + 1, name, 32);
	if (vdi_control[4] > 34)
	{
		name[32]     = vdi_intout[33];
		*flags       = (vdi_intout[34] >> 8) & 0xff;
		*font_format = vdi_intout[34] & 0xff;
	}
	else if (vdi_control[4] > 33 )
	{
		name[32]	 = vdi_intout[33];
		*flags		 = 0;
		*font_format = vdi_intout[33] ? 0 : 1;
	}
	else
	{
		name[32] 	 = 0;
		*flags		 = 0;
		*font_format = 0;
	}
	
	return vdi_intout[0];
}

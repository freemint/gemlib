/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** vst_charmap()-like function which is able to use Unicode for mapping
 *  characters.
 *
 *  @param handle Device handle
 *  @param mode mapping mode
 *         - 0: direct mapping
 *         - 1: ASCII mapping
 *         - 2: Unicode mapping
 *
 *  @return set mapping mode
 *
 *  @since NVDI 4
 *
 *  If you select Unicode and if you want to determine whether a certain character
 *  exists, you should call vqt_width(). If the index returned by vqt_width() is -1, 
 *  the character does not exist. Instead of vqt_width() you can also call 
 *  vqt_char_index() and map the Unicode index into a direct index.
 *
 *
 */

short
vst_map_mode (short handle, short mode)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[2];   
	short vdi_intout[1]; 
	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_intout, 0L);
#endif
	
	vdi_intin[0] = mode;
	vdi_intin[1] = 1;

	VDI_TRAP (vdi_params, handle, 236, 0,2);

	return vdi_intout[0];
}

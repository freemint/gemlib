/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** This function returns extended font information specified by \p flags in a
 *  XFNT_INFO structure. If the index is a nonzero value vqt_xfntinfo() searches 
 *  the correspoding font and returns the requested information. If \p index is zero, 
 *  vqt_xfntinfo() searches the font specified by \p id. If \p index and \p id are 
 *  zero, this function returns information about the current font.
 *
 *  @param handle Device handle
 *  @param flags kind of requested information (bit number):
 *         - 0:    return the full font name (font_name)
 *         - 1:    return the name of the family (family_name)
 *         - 2:    return the style name (style_name)
 *         - 3:    return the file name (file_name1)
 *         - 4:    return the 2. optional file name (file_name2)
 *         - 5:    return the 3. optional file name (file_name3)
 *         - 8:    return the available pt sizes (without enlargment) (pt_cnt, pt_sizes)
 *         - 9:    return the available pt sizes (with enlargment) (pt_cnt, pt_sizes)
 *  @param id font id or 0 (current font)
 *  @param index font index or 0 (use id)
 *  @param info pointer to the XFNT_INFO structure
 *
 *  @return font id
 *
 *  @since NVDI 3.02
 *
 */

short
vqt_xfntinfo (short handle, short flags, short id, short index, XFNT_INFO *info)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[5];   
	short vdi_intout[3]; /* vdi_intout[0..2] will be filled */
	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_intout, 0L);
#endif
	
	info->size = sizeof (XFNT_INFO);
	vdi_intin    [0] = flags;
	vdi_intin    [1] = id;
	vdi_intin    [2] = index;
	vdi_intin_ptr(3) = info;
	
	VDI_TRAP (vdi_params, handle, 229, 0,5);
	
	return vdi_intout[1];
}

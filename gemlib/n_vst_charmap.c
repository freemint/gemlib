/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** switches from ASCII-mapping to direct mapping, which means that you 
 *  can access all characters of a font (e.g. if the user wants to select a special 
 *  non-ASCII character), but an index like 65 does not stand for 'A' anymore but 
 *  for another character. If you switch to direct mapping, the number of characters 
 *  per font (minADE and maxADE/vqt_fontinfo()) is changed to the number of really 
 *  existing characters.  
 *
 *  @param handle Device handle
 *  @param mode mapping mode
 *         - 0: direct mapping
 *         - 1: ASCII mapping
 *
 *  @since NVDI 3.00
 *
 *  @note
 *  If you want to switch on ASCII-mapping, you should use 1 as <mode> and not 
 *  any other nonzero value, because other mapping might exist in future 
 *  (e.g. Unicode).
 *  
 *  @note
 *  Since NVDI 4 is able to use Unicode for mapping characters, there is an extended 
 *  Binding to select Unicode (see vst_map_mode()).
 *  
 *
 */

void
vst_charmap (short handle, short mode)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		&mode,                       /* vdi_intin   */
		0L,                          /* vdi_ptsin   */
		0L,                          /* vdi_intout  */
		0L                           /* vdi_ptsout  */
	};
#else
	vdi_intin[0] = mode;
#endif

	VDI_TRAP (vdi_params, handle, 236, 0,1);
}

/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** This function can be used to set the track and pair kerning mode. Most Speedo 
 *  fonts have 3 kerning tracks. Ordinary TrueType fonts do not have any kerning 
 *  tracks, but some GX TrueTypes do.
 *
 *  @param handle Device handle
 *  @param tmode requested track kerning mode
 *         - 0: no track kerning
 *         - 1: normal
 *         - 2: tight
 *         - 3: very tight
 *  @param pmode pair kerning on (1) or off (0)
 *         - 0: no pair kerning
 *         - 1: do pair kerning
 *  @param tracks track kerning mode \n
 *         [option CHECK_NULLPTR] tracks may be NULL
 *  @param pairs number of kerning pairs \n
 *         [option CHECK_NULLPTR] pairs may be NULL
 *
 *  @since NVDI 3.00
 *
 *  @note
 *  NVDI allows the caller to set a user-defined track kerning.
 *  see vst_track_offset()
 *
 */

void
vst_kern (short handle, short tmode, short pmode, short *tracks, short *pairs)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[2];   
	short vdi_intout[2]; 
	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_intout, 0L);
#endif
	
	vdi_intin[0] = tmode;
	vdi_intin[1] = pmode;
	
	VDI_TRAP (vdi_params, handle, 237, 0,2);
	
#if CHECK_NULLPTR
	if (tracks)
#endif
	*tracks = vdi_intout[0];
#if CHECK_NULLPTR
	if (pairs)
#endif
	*pairs  = vdi_intout[1];
}

/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** allows the caller to set a user-defined track kerning
 *
 *  @param handle Device handle
 *  @param offset offset in 1/65536 pixels.
 *  @param pairmode pair kerning on (1) or off (0)
 *  @param tracks track kerning mode \n
 *         [option CHECK_NULLPTR] tracks may be NULL
 *  @param pairs number of kerning pairs \n
 *         [option CHECK_NULLPTR] pairs may be NULL
 *
 *  @since NVDI 3.00
 *
 */

void
vst_track_offset (short handle, long offset, short pairmode,
                  short *tracks, short *pairs)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[4];   
	short vdi_intout[2]; 

	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_intout, vdi_dummy);
	
	vdi_intin[0]          = 255;
	vdi_intin[1]          = pairmode;
	vdi_intin_long(2) = offset;
	
	VDI_TRAP (vdi_params, handle, 237, 0,4);
	
#if CHECK_NULLPTR
	if (tracks)
#endif
	*tracks = vdi_intout[0];
#if CHECK_NULLPTR
	if (pairs)
#endif
	*pairs  = vdi_intout[1];
}

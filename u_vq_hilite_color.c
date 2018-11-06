#include "gem_vdiP.h"
#include "mt_gemx.h"
#include "vdi_userdef.h"


/** UDEF version of vq_hilite_color(). See \ref overviewUDEF for details about UDEF feature
 */

long
udef_vq_hilite_color (short handle, COLOR_ENTRY * hilite_color)
{
	VDI_PARAMS(_VDIParBlk.vdi_control, 0L, 0L, _VDIParBlk.vdi_intout, vdi_dummy);
	
	VDI_TRAP_00 (vdi_params, handle, 209);

#if CHECK_NULLPTR
	if (hilite_color)
#endif
	*hilite_color = *(COLOR_ENTRY*)&_VDIParBlk.vdi_intout[2];
	
	return vdi_intout_long(0);
}

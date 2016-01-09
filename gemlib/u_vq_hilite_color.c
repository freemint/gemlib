/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"
#include "vdi_userdef.h"


/** 
 *
 *  @param handle Device handle
 *  @param hilite_color  \n
 *         [option CHECK_NULLPTR] hilite_color may be NULL
 *
 *  @return 
 *
 *  @since NVDI 5 ?
 *
 *  @note Use it for work with userdef, not reentrant function!
 *
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
	
	return *(long*)_VDIParBlk.vdi_intout;
}

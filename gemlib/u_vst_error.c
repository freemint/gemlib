/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "vdi_userdef.h"


/** UDEF version of vst_error(). See \ref overviewUDEF for details about UDEF feature
 */

void
udef_vst_error (short handle, short mode, short *errorvar)
{

	VDI_PARAMS(_VDIParBlk.vdi_control, _VDIParBlk.vdi_intin, 0L, _VDIParBlk.vdi_intout, _VDIParBlk.vdi_ptsout );
	
	_VDIParBlk.vdi_intin[0] = mode;
	*(short **)_VDIParBlk.vdi_intin[1] = errorvar;
	
	VDI_TRAP (vdi_params, handle, 245, 0,3);
}

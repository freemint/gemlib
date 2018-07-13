/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "vdi_userdef.h"


/** UDEF version of v_loadcache(). See \ref overviewUDEF for details about UDEF feature
 */

short
udef_v_loadcache (short handle, const char *filename, short mode)
{
	short n = 1 + vdi_str2array_n (filename, _VDIParBlk.vdi_intin + 1, VDI_INTINMAX-1);

	VDI_PARAMS(_VDIParBlk.vdi_control, _VDIParBlk.vdi_intin, 0L, _VDIParBlk.vdi_intout, _VDIParBlk.vdi_ptsout );

	_VDIParBlk.vdi_intin[0] = mode;

	VDI_TRAP (vdi_params, handle, 250, 0, n);
	
	return _VDIParBlk.vdi_intout[0];
}

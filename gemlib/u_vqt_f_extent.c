/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"
#include "vdi_userdef.h"


/** UDEF version of vqt_f_extent(). See \ref overviewUDEF for details about UDEF feature
 */

void
udef_vqt_f_extent (short handle, const char *str, short extent[])
{
	short n = vdi_str2array_n (str, _VDIParBlk.vdi_intin, VDI_INTINMAX);

	VDI_PARAMS(_VDIParBlk.vdi_control, _VDIParBlk.vdi_intin, 0L, vdi_dummy, extent);

	VDI_TRAP (vdi_params, handle, 240, 0,n);
}

#include "gem_vdiP.h"
#include "mt_gemx.h"
#include "vdi_userdef.h"


/** UDEF version of vqt_real_extent(). See \ref overviewUDEF for details about UDEF feature
 */

void
udef_vqt_real_extent (short handle, short x, short y, const char *string, short extent[])
{
	short n = vdi_str2array_n (string, _VDIParBlk.vdi_intin, VDI_INTINMAX);

	VDI_PARAMS(_VDIParBlk.vdi_control, _VDIParBlk.vdi_intin, _VDIParBlk.vdi_ptsin, vdi_dummy, extent);

	_VDIParBlk.vdi_ptsin[0] = x;
	_VDIParBlk.vdi_ptsin[1] = y;
	
	VDI_TRAP_ESC (vdi_params, handle, 240,4200, 1,n);
}

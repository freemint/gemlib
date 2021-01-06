#include "gem_vdiP.h"
#include "mt_gemx.h"
#include "vdi_userdef.h"


/** UDEF version of vqt_real_extentn(). See \ref overviewUDEF for details about UDEF feature
 */

void
udef_vqt_real_extentn (short handle, short x, short y, const char *string, short num, short extent[])
{
	VDI_PARAMS(_VDIParBlk.vdi_control, _VDIParBlk.vdi_intin, _VDIParBlk.vdi_ptsin, vdi_dummy, extent);

	num = vdi_str2array_n (string, _VDIParBlk.vdi_intin, num);

	_VDIParBlk.vdi_ptsin[0] = x;
	_VDIParBlk.vdi_ptsin[1] = y;
	
	VDI_TRAP_ESC (vdi_params, handle, 240,4200, 1,num);
}

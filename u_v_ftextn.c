#include "gem_vdiP.h"
#include "mt_gemx.h"
#include "vdi_userdef.h"


/** UDEF version of v_ftext(). See \ref overviewUDEF for details about UDEF feature
 */

void
udef_v_ftextn (short handle, short x, short y, const char *str, short num)
{
	VDI_PARAMS(_VDIParBlk.vdi_control, _VDIParBlk.vdi_intin, _VDIParBlk.vdi_ptsin, vdi_dummy, vdi_dummy);
	
	num = vdi_str2array_n (str, _VDIParBlk.vdi_intin, num);

	_VDIParBlk.vdi_ptsin[0] = x;
	_VDIParBlk.vdi_ptsin[1] = y;

	VDI_TRAP (vdi_params, handle, 241, 1,num);
}

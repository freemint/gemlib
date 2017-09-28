/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "vdi_userdef.h"


/** UDEF version of vsm_string(). See \ref overviewUDEF for details about UDEF feature
 */


short
udef_vsm_string (short handle, short len, short echo, short echoxy[], char *str)
{

	VDI_PARAMS(_VDIParBlk.vdi_control, _VDIParBlk.vdi_intin, _VDIParBlk.vdi_ptsin, _VDIParBlk.vdi_intout, vdi_dummy );
	
	_VDIParBlk.vdi_intin[0]      = len;
	_VDIParBlk.vdi_intin[1]      = echo;
	_VDIParBlk.vdi_ptsin[0]      = echoxy[0];
	_VDIParBlk.vdi_ptsin[1]      = echoxy[1];
	
	VDI_TRAP (vdi_params, handle, 31, 1,2);
	
	vdi_array2str (_VDIParBlk.vdi_intout, str, _VDIParBlk.vdi_control[4]);
	
	return _VDIParBlk.vdi_control[4];
}

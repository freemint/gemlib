/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"
#include "vdi_userdef.h"


/** UDEF version of vs_document_info(). See \ref overviewUDEF for details about UDEF feature
 */

short
udef_vs_document_info (short handle, short type, char *s, short wchar)
{
	short n = 1;

	VDI_PARAMS(_VDIParBlk.vdi_control, _VDIParBlk.vdi_intin, 0L, _VDIParBlk.vdi_intout, vdi_dummy);

	_VDIParBlk.vdi_intout[0] = 0;
	_VDIParBlk.vdi_intin[0]  = type;
	if (wchar) {
		/* 16bit strings not yet supported! */
		return 0;
	
	} else {
		n += vdi_str2array_n (s, _VDIParBlk.vdi_intin + 1, VDI_INTINMAX-1);
	}
	VDI_TRAP_ESC (vdi_params, handle, 5,2103, 0,n);
	
	return _VDIParBlk.vdi_intout[0];
}

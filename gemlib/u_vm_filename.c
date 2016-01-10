/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "vdi_userdef.h"


/** UDEF version of vm_filename(). See \ref overviewUDEF for details about UDEF feature
 */

void
udef_vm_filename (short handle, const char *filename)
{
	short n = vdi_str2array_n (filename, _VDIParBlk.vdi_intin, VDI_INTINMAX);

	VDI_PARAMS(_VDIParBlk.vdi_control, _VDIParBlk.vdi_intin, 0L, vdi_dummy, vdi_dummy);
	
	VDI_TRAP_ESC (vdi_params, handle, 5,100, 0,n);
}

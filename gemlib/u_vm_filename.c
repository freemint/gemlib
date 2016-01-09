/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "vdi_userdef.h"


/** This function should be used to change the name of the metafile. The 
 *  name \p filename must be an absolute path like "E:\\PICS\\FLIWATT.GEM".
 *
 *  @param handle Device handle
 *  @param filename 
 *
 *  @since all VDI versions
 *
 *  The metafile in the current directory created by v_opnwk() ("GEMFILE.GEM")
 *  will be closed (and deleted by NVDI). Therefore vm_filename() should be 
 *  called after v_opnwk().
 *
 *  Note:
 *  Old metafile driver may not delete the default file "GEMFILE.GEM" when 
 *  you call vm_filename(). That means that you are on the safe side if you 
 *  call Fdelete() after vm_filename() and try to delete GEMFILE.GEM.
 *Use it for work with userdef, not reentrant function!
 *  @note Use it for work with userdef, not reentrant function!
 */

void
udef_vm_filename (short handle, const char *filename)
{
	short n = vdi_str2array_n (filename, _VDIParBlk.vdi_intin, VDI_INTINMAX);

	VDI_PARAMS(_VDIParBlk.vdi_control, _VDIParBlk.vdi_intin, 0L, vdi_dummy, vdi_dummy);
	
	VDI_TRAP_ESC (vdi_params, handle, 5,100, 0,n);
}

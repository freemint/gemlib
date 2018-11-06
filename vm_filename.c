#include "gem_vdiP.h"

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
 *
 */

void
vm_filename (short handle, const char *filename)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[VDI_INTINMAX];   
	short n = vdi_str2array_n (filename, vdi_intin, VDI_INTINMAX);

	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_dummy, vdi_dummy);
	
	VDI_TRAP_ESC (vdi_params, handle, 5,100, 0,n);
}

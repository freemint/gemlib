#include "gem_vdiP.h"

/** The memory for the additional fonts is freed.
 *
 *  @param handle Device handle
 *  @param select 0 (reserved)
 *
 *  @since all VDI versions
 *
 *	If the fonts are being shared by other virtual
 *	workstations with the same root device handle,
 *	the fonts are not unloaded from memory until
 *	one of the following conditions is met:
 *	- all workstations that share the fonts are
 *	  closed
 *	- all workstations that share the external
 *	  fonts request that the external fonts be
 *	  unloaded
 *  
 *	The default system fonts for the workstation
 *	remain loaded and available.
 *
 */

void
vst_unload_fonts (short handle, short select)
{
	short vdi_control[VDI_CNTRLMAX]; 
	
	VDI_PARAMS(vdi_control, &select, 0L, vdi_dummy, vdi_dummy );
		
	VDI_TRAP (vdi_params, handle, 120, 0,1);
}

/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** starts output on devices like printers or plotters, which 
 *  buffer VDI commands in a display list and do not execute them immediately
 *
 *  @param handle Device handle
 *
 *  @since all VDI versions
 *
 *  The screen driver executes VDI commands immediately and therefore you do not 
 *  have to call "UPDATE WORKSTATION".
 *  
 *  Note: The picture is drawn to the printer but
 *  no new page occurs. A Clear Workstation causes
 *  a new page.
 *
 */

void
v_updwk (short handle)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	VDI_PARAMS(vdi_control, 0L, 0L, vdi_dummy, vdi_dummy );
#endif
	
	VDI_TRAP_00 (vdi_params, handle, 4);
}

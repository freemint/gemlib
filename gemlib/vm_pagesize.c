/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** is a sub-opcode of WRITE METAFILE ITEM and sets the page size in 1/10 mm.
 *
 *  @param handle Device handle
 *  @param pgwidth width in 1/10 mm
 *  @param pgheight height in 1/10 mm
 *
 *  @since 
 *
 *
 */

void
vm_pagesize (short handle, short pgwidth, short pgheight)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[3];   
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		&vdi_intin[0],               /* vdi_intin   */
		0L,                          /* vdi_ptsin   */
		0L,                          /* vdi_intout  */
		0L                           /* vdi_ptsout  */
	};
#endif
	
	vdi_intin[0] = 0;
	vdi_intin[1] = pgwidth;
	vdi_intin[2] = pgheight;
	
	VDI_TRAP_ESC (vdi_params, handle, 5,99, 0,3);
}

/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** is a sub-opcode of WRITE METAFILE ITEM and sets the used coordinate system.
 *
 *  @param handle Device handle
 *  @param llx x-Koordinate links unten
 *  @param lly y-Koordinate links unten
 *  @param urx x-Koordinate rechts oben
 *  @param ury y-Koordinate rechts oben
 *
 *  @since 
 *
 */

void
vm_coords (short handle, short llx, short lly, short urx, short ury)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[5];   
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		&vdi_intin[0],               /* vdi_intin   */
		0L,                          /* vdi_ptsin   */
		0L,                          /* vdi_intout  */
		0L                           /* vdi_ptsout  */
	};
#endif
	
	vdi_intin[0] = 1;
	vdi_intin[1] = llx;
	vdi_intin[2] = lly;
	vdi_intin[3] = urx;
	vdi_intin[4] = ury;
	
	VDI_TRAP_ESC (vdi_params, handle, 5,99, 0,5);
}

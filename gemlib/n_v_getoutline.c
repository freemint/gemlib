/*
 *   NOTE: requires NVDI version 3.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


void
v_getoutline (short handle, short ch, short *xyarray, char *bezarray,
              short maxverts, short *numverts)
{
	vdi_intin    [0] = ch;
	vdi_intin    [1] = maxverts;
	vdi_intin_ptr(2) = xyarray;
	vdi_intin_ptr(4) = bezarray;
	
	VDI_TRAP (vdi_params, handle, 243, 0,6);
	
	*numverts = vdi_intout[0];
}

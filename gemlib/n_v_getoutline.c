
#include "gemx.h"


void
v_getoutline (short handle, short ch, short *xyarray, char *bezarray, short maxverts,
	      short *numverts)
{
	vdi_intin[0] = ch;
	vdi_intin[1] = maxverts;
	*((short **) (&vdi_intin[2])) = xyarray;
	*((char **) (&vdi_intin[4])) = bezarray;
	vdi_control[0] = 243;
	vdi_control[1] = 0;
	vdi_control[3] = 6;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	*numverts = vdi_intout[0];
}

/*
 * * NOTE: requires NVDI version 3.x or higher
 */

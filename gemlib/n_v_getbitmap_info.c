
#include "gemx.h"


void
v_getbitmap_info (short handle, short ch, long *advancex, long *advancey,
		  long *xoffset, long *yoffset, short *width, short *height,
		  short **bitmap)
{
	vdi_intin[0] = ch;
	vdi_control[0] = 239;
	vdi_control[1] = 0;
	vdi_control[3] = 1;
	vdi_control[5] = 0;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	*width = vdi_intout[0];
	*height = vdi_intout[1];
	*advancex = *((long *) (&vdi_intout[2]));
	*advancey = *((long *) (&vdi_intout[4]));
	*xoffset = *((long *) (&vdi_intout[6]));
	*yoffset = *((long *) (&vdi_intout[8]));
	*bitmap = *((short **) (&vdi_intout[10]));
}

/*
 * * NOTE: requires NVDI version 3.x or higher
 */

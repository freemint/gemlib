/*
 *   NOTE: requires NVDI version 3.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


void
v_getbitmap_info (short handle, short ch, long *advancex, long *advancey,
                  long *xoffset, long *yoffset, short *width, short *height,
                  short **bitmap)
{
	vdi_intin[0] = ch;
	
	VDI_TRAP (vdi_params, handle, 239, 0,1);
	
	*width    = vdi_intout     [0];
	*height   = vdi_intout     [1];
	*advancex = vdi_intout_long(2);
	*advancey = vdi_intout_long(4);
	*xoffset  = vdi_intout_long(6);
	*yoffset  = vdi_intout_long(8);
	*bitmap   = (short*)vdi_intout_long(10);
}

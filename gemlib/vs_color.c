/*
 *   general attribute
 */

#include "gem_vdiP.h"


void
vs_color (short handle, short index, short rgb[])
{
	vdi_intin[0] = index;
	vdi_intin[1] = rgb[0];
	vdi_intin[2] = rgb[1];
	vdi_intin[3] = rgb[2];

	VDI_TRAP (vdi_params, handle, 14, 0,4);
}

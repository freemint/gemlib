#include "gem_vdiP.h"


short
vq_color (short handle, short index, short flag, short rgb[])
{
	vdi_intin[0] = index;
	vdi_intin[1] = flag;
	
	VDI_TRAP (vdi_params, handle, 26, 0,2);
	
	rgb[0] = vdi_intout[1];
	rgb[1] = vdi_intout[2];
	rgb[2] = vdi_intout[3];
	
	return vdi_intout[0];
}

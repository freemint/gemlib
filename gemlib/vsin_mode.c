#include "gem_vdiP.h"


short
vsin_mode (short handle, short dev, short mode)
{
	vdi_intin[0] = dev;
	vdi_intin[1] = mode;
	
	VDI_TRAP (vdi_params, handle, 33, 0,2);
	
	return vdi_intout[0];
}

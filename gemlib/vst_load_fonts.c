
#include "gem.h"


short
vst_load_fonts (short handle, short select)
{
	vdi_intin[0] = select;
	vdi_control[0] = 119;
	vdi_control[1] = 0;
	vdi_control[3] = 1;
	vdi_control[5] = 0;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	return vdi_intout[0];
}

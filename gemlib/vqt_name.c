#include "gem_vdiP.h"


short
vqt_name (short handle, short element, char *name)
{
	vdi_intin[0] = element;

	VDI_TRAP (vdi_params, handle, 130, 0,1);

	vdi_array2str (vdi_intout + 1, name, 33);
	
	return vdi_intout[0];
}

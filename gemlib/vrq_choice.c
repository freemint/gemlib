#include "gem_vdiP.h"


void
vrq_choice (short handle, short cin, short *cout)
{
	vdi_intin[0] = cin;
	
	VDI_TRAP (vdi_params, handle, 30, 0,1);
	
	*cout = vdi_intout[0];
}

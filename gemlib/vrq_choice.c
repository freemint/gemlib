
#include "gem.h"


void
vrq_choice (short handle, short cin, short *cout)
{
	vdi_intin[0] = cin;
	vdi_control[0] = 30;
	vdi_control[1] = 0;
	vdi_control[3] = 1;
	vdi_control[5] = 0;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	*cout = vdi_intout[0];
}

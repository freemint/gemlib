
#include "gem.h"


void
vqt_fontinfo (short handle, short *minade, short *maxade, short distances[],
	      short *maxwidth, short effects[])
{
	vdi_control[0] = 131;
	vdi_control[1] = 0;
	vdi_control[3] = 0;
	vdi_control[5] = 0;
	vdi_control[6] = handle;

	vdi (&vdi_params);

	*minade = vdi_intout[0];
	*maxade = vdi_intout[1];
	*maxwidth = vdi_ptsout[0];

	distances[0] = vdi_ptsout[1];
	distances[1] = vdi_ptsout[3];
	distances[2] = vdi_ptsout[5];
	distances[3] = vdi_ptsout[7];
	distances[4] = vdi_ptsout[9];

	effects[0] = vdi_ptsout[2];
	effects[1] = vdi_ptsout[4];
	effects[2] = vdi_ptsout[6];
}

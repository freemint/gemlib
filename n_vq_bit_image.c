#include "gem_vdiP.h"
#include "mt_gemx.h"

short vq_bit_image(short handle, short *ver, short *maximg, short *form)
{
	short vdi_control[VDI_CNTRLMAX];
	short vdi_intout[4];

	VDI_PARAMS (vdi_control, vdi_dummy, vdi_dummy, vdi_intout, vdi_dummy);
	
	vdi_intout[0] = 0;
	VDI_TRAP_ESC (vdi_params, handle, 5,2102, 0, 0);
	
	*ver = vdi_intout[1];
	*maximg = vdi_intout[2];
	*form = vdi_intout[3];
	return vdi_intout[0];
}

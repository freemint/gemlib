#include "gem_vdiP.h"
#include "mt_gemx.h"

short vq_driver_info(short handle, short *lib, short *drv, short *plane, short *attr, char name[27])
{
	short vdi_control[VDI_CNTRLMAX];
	short vdi_intout[31];

	VDI_PARAMS (vdi_control, vdi_dummy, vdi_dummy, vdi_intout, vdi_dummy);
	
	vdi_intout[0] = 0;
	VDI_TRAP_ESC (vdi_params, handle, 5,2101, 0, 0);
	
	*lib = vdi_intout[1];
	*drv = vdi_intout[2];
	*plane = vdi_intout[3];
	*attr = vdi_intout[4];	
	vdi_array2str(&vdi_intout[5], name, 26);
	return vdi_intout[0];
}

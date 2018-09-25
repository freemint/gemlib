#include "gem_vdiP.h"
#include "mt_gemx.h"

short vs_crop(short handle, short ltx1, short lty1, short ltx2, short lty2, short ltlen, short ltoffset)
{
	short vdi_control[VDI_CNTRLMAX];
	short vdi_intout[2];
	short vdi_intin[6];

	VDI_PARAMS (vdi_control, vdi_intin, vdi_dummy, vdi_intout, vdi_dummy);
	
	vdi_intin[0] = ltx1;
	vdi_intin[1] = lty1;
	vdi_intin[2] = ltx2;
	vdi_intin[3] = lty2;
	vdi_intin[4] = ltlen;
	vdi_intin[5] = ltoffset;	
	vdi_intout[0] = 0;
	VDI_TRAP_ESC (vdi_params, handle, 5,2104, 0, 6);
	
	return vdi_intout[0];
}

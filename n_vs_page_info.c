#include "gem_vdiP.h"
#include "mt_gemx.h"

short vs_page_info(short handle, short type, const char txt[60])
{
	short vdi_control[VDI_CNTRLMAX];
	short vdi_intout[1];
	short vdi_intin[62];
	short i;

	VDI_PARAMS (vdi_control, vdi_intin, vdi_dummy, vdi_intout, vdi_dummy);
	
	vdi_intin[0] = type;
	i = vdi_str2array_n(txt, &vdi_intin[1], 60) + 1;
	vdi_intin[i++] = '\0';
	vdi_intout[0] = 0;
	VDI_TRAP_ESC (vdi_params, handle, 5,2103, 0, i);
	
	return vdi_intout[0];
}

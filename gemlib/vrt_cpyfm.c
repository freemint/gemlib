#include "gem_vdiP.h"


void
vrt_cpyfm (short handle, short mode, short pxy[], MFDB *src, MFDB *dst,
           short color[])
{
	vdi_params.ptsin = pxy;
	
	vdi_intin[0]            = mode;
	*((long*)&vdi_intin[1]) = *(long*)color;
	vdi_control_ptr(7)      = src;
	vdi_control_ptr(9)      = dst;

	VDI_TRAP (vdi_params, handle, 121, 4,3);

	vdi_params.ptsin = vdi_ptsin;
}

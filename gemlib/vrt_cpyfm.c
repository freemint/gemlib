#include "gem_vdiP.h"


void
vrt_cpyfm (short handle, short mode, short pxy[], MFDB *src, MFDB *dst,
           short color[])
{
	vdi_params.ptsin = pxy;
	
	vdi_intin[0]                 = mode;
	*((long*)(&vdi_intin[1]))    = *(long*)color;
	*((MFDB**)(&vdi_control[7])) = src;
	*((MFDB**)(&vdi_control[9])) = dst;

	VDI_TRAP (vdi_params, handle, 121, 4,3);

	vdi_params.ptsin = vdi_ptsin;
}

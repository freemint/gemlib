#include "gem_vdiP.h"


void
vro_cpyfm (short handle, short mode, short pxy[], MFDB *src, MFDB *dst)
{
	vdi_params.ptsin = pxy;
	
	vdi_intin[0]                 = mode;
	*((MFDB**)(&vdi_control[7])) = src;
	*((MFDB**)(&vdi_control[9])) = dst;
	
	VDI_TRAP (vdi_params, handle, 109, 4,1);

	vdi_params.ptsin = vdi_ptsin;
}

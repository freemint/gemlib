/*
 *   metafile function
 */

#include "gem_vdiP.h"


void
v_write_meta (short handle, short numvdi_intin, short *avdi_intin,
              short num_ptsin, short *a_ptsin)
{
	vdi_params.intin = avdi_intin;
	vdi_params.ptsin = a_ptsin;

	VDI_TRAP_ESC (vdi_params, handle, 5,99, num_ptsin,numvdi_intin);

	vdi_params.intin = vdi_intin;
	vdi_params.ptsin = vdi_ptsin;
}

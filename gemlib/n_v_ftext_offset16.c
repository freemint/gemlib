/*
 *   NOTE: requires NVDI version 3.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


void
v_ftext_offset16 (short handle, short x, short y,
                  const short *wstr, const short *offset)
{
	const long * src = (const long*)offset;
	long       * dst =       (long*)vdi_ptsin;
	short     i, len = vdi_wstrlen (wstr);

	vdi_params.intin = wstr;

	vdi_ptsin[0] = x;
	vdi_ptsin[1] = y;
	for (i = 0; i < len; i++) {
		*(++dst) = *(src++);
	}
	VDI_TRAP (vdi_params, handle, 241, (len +1),len);

	vdi_params.intin = vdi_intin;
}

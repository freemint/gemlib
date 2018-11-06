#include "gem_vdiP.h"
#include "mt_gemx.h"
#include "vdi_userdef.h"


/** UDEF version of v_ftext_offset(). See \ref overviewUDEF for details about UDEF feature
 */

void
udef_v_ftext_offset (short handle, short x, short y,
                const char *str, const short *offset)
{	const long * src = (const long*)offset;
	long       * dst =       (long*)_VDIParBlk.vdi_ptsin;
	short     i, len = vdi_str2array_n (str, _VDIParBlk.vdi_intin, VDI_PTSINMAX);

	VDI_PARAMS(_VDIParBlk.vdi_control, _VDIParBlk.vdi_intin, _VDIParBlk.vdi_ptsin, vdi_dummy, vdi_dummy);
	
	_VDIParBlk.vdi_ptsin[0] = x;
	_VDIParBlk.vdi_ptsin[1] = y;
	for (i = 0; i < len; i++) {
		*(++dst) = *(src++);
	}

	VDI_TRAP (vdi_params, handle, 241, (len +1),len);
}

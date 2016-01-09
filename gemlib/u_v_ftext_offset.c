/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"
#include "vdi_userdef.h"


/** This text function uses track and pair kerning and works with an internal 
 *  resolution of 1/65536 pixels to maintain accurate character placement.
 *  This variant of v_ftext() which allows your application to specifiy 
 *  the offset of each character relative to the previous one
 *
 *  @param handle Device handle
 *  @param x 
 *  @param y 
 *  @param str 
 *  @param offset 
 *         - offset[0] : x-offset of the first character
 *         - offset[1] : y-offset of the first character
 *         - offset[2..(2*n)-1] : x-offset, y-offset of the next characters
 *
 *  @since NVDI 3.00
 *
 *  @note Use it for work with userdef, not reentrant function!
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

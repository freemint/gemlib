/*
 *   NOTE: requires NVDI version 5.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


short
v_resize_bm (short handle, short width, short height, long byte_width,
             unsigned char *addr)
{
	vdi_intin         [0] = width;
	vdi_intin         [1] = height;
	*(long*)&vdi_intin[2] = byte_width;
	vdi_intin_ptr     (4) = addr;

	VDI_TRAP_ESC (vdi_params, handle, 100,2, 0,6);
	
	return vdi_intout[0];
}

#include "gem_vdiP.h"

/** 
 *
 *  @param handle Device handle
 *  @param filename name of the file
 *
 *  @return -1 in case of error, else 0
 *
 *  @since SpeedoGDOS 5.1
 *
 *
 *
 */

short
v_savecache (short handle, const char *filename)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[VDI_INTINMAX];
	short vdi_intout[2]; /* todo (doc wanted) */
	short n = vdi_str2array_n (filename, vdi_intin, VDI_INTINMAX);

	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_intout, vdi_dummy );
	
	VDI_TRAP (vdi_params, handle, 249, 0,n);
	
	return vdi_intout[0];
}

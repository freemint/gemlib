/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** 
 *
 *  @param handle Device handle
 *  @param filename 
 *  @param mode 
 *
 *  @return 
 *
 *  @since all VDI versions
 *
 *  @sa
 *
 *
 *
 */

short
v_loadcache (short handle, const char *filename, short mode)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[VDI_INTINMAX];   
	short vdi_intout[VDI_INTOUTMAX]; /* todo (doc wanted) */
	short vdi_ptsout[VDI_PTSOUTMAX]; /* todo (doc wanted) */
	register short n = 1 + vdi_str2array (filename, vdi_intin + 1);

	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_intout, vdi_ptsout );
	
	vdi_intin[0] = mode;

	VDI_TRAP (vdi_params, handle, 250, 0, n);
	
	return vdi_intout[0];
}


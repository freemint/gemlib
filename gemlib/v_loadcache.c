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
#if USE_LOCAL_VDIPB
	/* todo (doc wanted) */
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[VDI_INTINMAX];   
	short vdi_intout[VDI_INTOUTMAX]; 
	short vdi_ptsout[VDI_PTSOUTMAX]; 
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		&vdi_intin[0],               /* vdi_intin   */
		0L,                          /* vdi_ptsin   */
		&vdi_intout[0],              /* vdi_intout  */
		&vdi_ptsout[0]               /* vdi_ptsout  */
	};
#endif
	register short n = 1 + vdi_str2array (filename, vdi_intin + 1);
	
	vdi_intin[0] = mode;

	VDI_TRAP (vdi_params, handle, 250, n,0);
	
	return vdi_intout[0];
}


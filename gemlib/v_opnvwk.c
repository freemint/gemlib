/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** opens a virtual workstation on an already 
 *  opened physical device (the screen). The attributes for each (virtual) 
 *  workstation are maintained separately.
 *
 *  @param work_in same as v_opnwk()
 *  @param handle before the call, \p handle specifies the handle of the
 *         physical workstation (returned by graf_handle). \n
 *         After the call, \p handle will contain the handle of the virtual
 *         workstation
 *  @param work_out same as v_opnwk()
 *
 *  @since all VDI versions
 *
 */


void
v_opnvwk (short work_in[], short *handle, short work_out[])
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		&work_in[0],                 /* vdi_intin   */
		0L,                          /* vdi_ptsin   */
		&work_out[0],                /* vdi_intout  */
		&work_out[45]                /* vdi_ptsout  */
	};
#else
	vdi_params.intin  = &work_in[0];
	vdi_params.intout = &work_out[0];
	vdi_params.ptsout = &work_out[45];
#endif
	
	VDI_TRAP (vdi_params, *handle, 100, 0,11);

#if !(USE_LOCAL_VDIPB)
	vdi_params.intin  = vdi_intin;
	vdi_params.intout = vdi_intout;
	vdi_params.ptsout = vdi_ptsout;
#endif

	*handle = vdi_control[6];
	
	/* some VDI doesn't have the same default parameters.
	   Here is a fix */	
	
	if (vdi_control[6]!=0)
	{ 
		short dummy;
		
		vsf_perimeter(vdi_control[6],PERIMETER_ON);
		vsl_ends(vdi_control[6],0,0);
		vsl_width(vdi_control[6],1);
		vst_effects(vdi_control[6],0);
		vsm_height(vdi_control[6],9);
		vst_height(vdi_control[6],13,&dummy,&dummy,&dummy,&dummy);
	}
}


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
	short vdi_control[VDI_CNTRLMAX]; 

	VDI_PARAMS(vdi_control, work_in, 0L, &work_out[0], &work_out[45] );
	
	VDI_TRAP (vdi_params, *handle, 100, 0,11);

	*handle = vdi_control[6];
	
	/* some VDI doesn't have the same default parameters.
	   Here is a fix */	
	
	if (vdi_control[6]!=0)
	{ 
		vsf_perimeter(vdi_control[6],PERIMETER_ON);
		vsl_ends(vdi_control[6],0,0);
		vsl_width(vdi_control[6],1);
		vst_effects(vdi_control[6],0);
		vsm_height(vdi_control[6],9);
	}
}


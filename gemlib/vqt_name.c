/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** This function returns a 32-character string that describes the face.
 *
 *  @param handle Device handle
 *  @param element 
 *  @param name 
 *
 *  @return ID number
 *
 *  @since all VDI versions; extended since NVDI 3.00 (add 33th byte to
 *  name for "bitmap/vector font" flag)
 *
 */

short
vqt_name (short handle, short element, char *name)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[VDI_INTOUTMAX]; 
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		&element,                    /* vdi_intin   */
		0L,                          /* vdi_ptsin   */
		&vdi_intout[0],              /* vdi_intout  */
		0L                           /* vdi_ptsout  */
	};
#else
	vdi_intin[0] = element;
#endif
	
	VDI_TRAP (vdi_params, handle, 130, 0,1);

	vdi_array2str (vdi_intout + 1, name, 33);
	
	return vdi_intout[0];
}

/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** this escape returns the name of a film.
 *
 *  @param handle Device handle
 *  @param index
 *  @param name
 *
 *  @return 0 (function not supported or wrong film index), or any positive
 *   value otherwise.
 *
 *  @since PC-GEM >= 2.0
 *
 *  @note a wrong film index returns an empty filmname.
 *
 */

short
vqp_filmname (short handle, short index, char * name)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[VDI_INTOUTMAX]; 
	VDI_PARAMS(vdi_control, &index, 0L, vdi_intout, 0L );
#else
	vdi_intin[0] = index;
#endif
		
	VDI_TRAP_ESC (vdi_params, handle, 5,92, 0,1);
	
	vdi_array2str( vdi_intout, name, vdi_control[4]);
	
	return vdi_control[4];
}

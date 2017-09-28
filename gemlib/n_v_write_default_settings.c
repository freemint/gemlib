/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** 
 *
 *  @param handle Device handle
 *  @param settings Pointer to a structur of the Typ PRN_SETTINGS
 *
 *  @return 0 for an error
 *
 *  @since NVDI 5.00
 *
 *
 *
 */

short v_write_default_settings( short handle, PRN_SETTINGS *settings )
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[N_PTRINTS];
	short vdi_intout[1]; 

	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_intout, 0L);

	vdi_intin_ptr(0, PRN_SETTINGS *) = settings;
	
	VDI_TRAP_ESC (vdi_params, handle, 182, 1, 0, N_PTRINTS);

	if ( vdi_control[4] >= 1 )
		return vdi_intout[0];

	return 0;
}

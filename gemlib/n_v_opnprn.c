/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** 
 *
 *  @param aes_handle Device handle
 *  @param settings 
 *  @param work_out 
 *
 *  @return 
 *
 *  @since NVDI 5 ?
 *
 *
 *
 */

short
v_opnprn (short aes_handle, PRN_SETTINGS *settings, short work_out[])
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[16];   
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		&vdi_intin[0],               /* vdi_intin   */
		0L,                          /* vdi_ptsin   */
		&work_out[0],                /* vdi_intout  */
		&work_out[45]                /* vdi_ptsout  */
	};
#endif
	
	register short i;

	vdi_intin[0] = settings->driver_id;
	for (i = 1; i < 10; vdi_intin[i++] = 1);
	vdi_intin    [10] = 2;
	vdi_intin    [11] = settings->size_id;
	vdi_intin_ptr(12) = settings->device;
	vdi_intin_ptr(14) = settings;

#if !(USE_LOCAL_VDIPB)
	vdi_params.intout = &work_out[0];
	vdi_params.ptsout = &work_out[45];
#endif

	VDI_TRAP (vdi_params, aes_handle, 1, 0,16);

#if !(USE_LOCAL_VDIPB)
	vdi_params.intout = &vdi_intout[0];
	vdi_params.ptsout = &vdi_ptsout[0];
#endif
	
	return vdi_control[6];
}

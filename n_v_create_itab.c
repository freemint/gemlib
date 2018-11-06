#include "gem_vdiP.h"
#include "mt_gemx.h"

/** 
 *
 *  @param handle Device handle
 *  @param ctab 
 *  @param bits 
 *
 *  @return 
 *
 *  @since NVDI 5 ?
 *
 *
 *
 */

ITAB_REF
v_create_itab (short handle, COLOR_TAB * ctab, short bits)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[3 + N_PTRINTS];
	short vdi_intout[N_PTRINTS];

	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_intout, vdi_dummy);
	
	vdi_intin_ptr(0, COLOR_TAB *) = ctab;
	vdi_intin    [N_PTRINTS] = bits;
	vdi_intin    [N_PTRINTS + 1] = 0;
	vdi_intin    [N_PTRINTS + 2] = 0;

	VDI_TRAP (vdi_params, handle, 208, 0, 3 + N_PTRINTS);

	return vdi_intout_ptr(0, ITAB_REF);
}

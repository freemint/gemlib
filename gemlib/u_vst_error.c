

#include "gem_vdiP.h"

/** 
 *
 *  @param handle Device handle
 *  @param mode 
 *  @param errorvar 
 *
 *  @since 
 *
 *  @sa
 *
 *
 *
 */

typedef struct
{
    short    vdi_control[VDI_CNTRLMAX];
    short    vdi_intin[VDI_INTINMAX];
    short    vdi_intout[VDI_INTOUTMAX];
    short    vdi_ptsin[VDI_PTSINMAX];
    short    vdi_ptsout[VDI_PTSOUTMAX];
} VDIPARBLK;

extern VDIPARBLK _VDIParBlk;

void
udef_vst_error (short handle, short mode, short *errorvar)
{

	VDI_PARAMS(_VDIParBlk.vdi_control, _VDIParBlk.vdi_intin, 0L, _VDIParBlk.vdi_intout, _VDIParBlk.vdi_ptsout );
	
	_VDIParBlk.vdi_intin[0] = mode;
	*(short **)_VDIParBlk.vdi_intin[1] = errorvar;
	
	VDI_TRAP (vdi_params, handle, 245, 0,3);
}

/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "gemx.h"

/** 
 *
 *  @param handle Device handle
 *  @param type 
 *  @param s 
 *  @param wchar 
 *
 *  @return 
 *
 *  @since NVDI 5 ?
 *
 *
 *
 */

short
vs_document_info (short handle, short type, char *s, short wchar)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[VDI_INTINMAX];   
	short vdi_intout[1]; 
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		&vdi_intin[0],               /* vdi_intin   */
		0L,                          /* vdi_ptsin   */
		&vdi_intout[0],              /* vdi_intout  */
		0L                           /* vdi_ptsout  */
	};
#endif
	
	register short n = 1;

	vdi_intout[0] = 0;
	vdi_intin[0]  = type;
	if (wchar) {
		/* 16bit strings not yet supported! */
		return 0;
	
	} else {
		n += vdi_str2array (s, vdi_intin + 1);
	}
	VDI_TRAP_ESC (vdi_params, handle, 5,2103, 0,n);
	
	return vdi_intout[0];
}

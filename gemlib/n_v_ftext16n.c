/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "gemx.h"

/** see v_ftext()
 *
 *  @param handle Device handle
 *  @param pos 
 *  @param wstr string (16 bits per character)
 *  @param num string len
 *
 *
 *
 */

void
v_ftext16n (short handle, PXY pos, const WCHAR * wstr, short num)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		(const short *)wstr,         /* vdi_intin   */
		&pos,                        /* vdi_ptsin   */
		0L,                          /* vdi_intout  */
		0L                           /* vdi_ptsout  */
	};
#else
	vdi_params.intin = (const short *)wstr;
	*(PXY*)vdi_ptsin = pos;
#endif
	
	VDI_TRAP (vdi_params, handle, 241, 1,num);

#if !(USE_LOCAL_VDIPB)
	vdi_params.intin = vdi_intin;
#endif
}

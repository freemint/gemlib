/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "gemx.h"

/** see v_ftext_offset()
 *
 *  @param handle Device handle
 *  @param x 
 *  @param y 
 *  @param wstr 
 *  @param offset 
 *
 *
 */

void
v_ftext_offset16 (short handle, short x, short y,
                  const WCHAR * wstr, const short * offset)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_ptsin[VDI_PTSINMAX];   
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		(const short *)wstr,         /* vdi_intin   */
		&vdi_ptsin[0],               /* vdi_ptsin   */
		0L,                          /* vdi_intout  */
		0L                           /* vdi_ptsout  */
	};
#endif
	
	const long * src = (const long*)offset;
	long       * dst =       (long*)vdi_ptsin;
	short     i, len = vdi_wstrlen ((const short *)wstr);

#if !(USE_LOCAL_VDIPB)
	vdi_params.intin = (const short *)wstr;
#endif

	vdi_ptsin[0] = x;
	vdi_ptsin[1] = y;
	for (i = 0; i < len; i++) {
		*(++dst) = *(src++);
	}
	VDI_TRAP (vdi_params, handle, 241, (len +1),len);

#if !(USE_LOCAL_VDIPB)
	vdi_params.intin = vdi_intin;
#endif
}

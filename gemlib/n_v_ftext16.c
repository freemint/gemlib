/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** see v_ftext()
 *
 *  @param handle Device handle
 *  @param x 
 *  @param y 
 *  @param wstr string (16 bits per character)
 *
 *
 *
 */

void
v_ftext16 (short handle, short x, short y, const WCHAR * wstr)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_ptsin[2];   
	register short n = vdi_wstrlen ((const short *)wstr);

	VDI_PARAMS(vdi_control, (const short *)wstr, vdi_ptsin, vdi_dummy, vdi_dummy);
	
	vdi_ptsin[0] = x;
	vdi_ptsin[1] = y;

	VDI_TRAP (vdi_params, handle, 241, 1,n);
}

/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** draws a filled arc, whose start and end angle can be set in
 *  tenths of degrees from 0 to 3600.
 *
 *  @param handle Device handle
 *  @param x 
 *  @param y 
 *  @param radius radius
 *  @param begang start angle
 *  @param endang end angle
 *
 *  @since all VDI versions
 *
 */

void
v_pieslice (short handle,
            short x, short y, short radius, short begang, short endang)
{
	short *ptr;
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[2];   
	short vdi_ptsin[8];   

	VDI_PARAMS(vdi_control, vdi_intin, vdi_ptsin, vdi_dummy, vdi_dummy );
		
	vdi_intin[0] = begang;
	vdi_intin[1] = endang;

	ptr = vdi_ptsin;
	*(ptr ++) = x;		    /* vdi_ptsin[0] = x; */
	*(ptr ++) = y;		    /* vdi_ptsin[1] = y; */
	*(ptr ++) = 0;		    /* vdi_ptsin[2] = 0; */
	*(ptr ++) = 0;		    /* vdi_ptsin[3] = 0; */
	*(ptr ++) = 0;		    /* vdi_ptsin[4] = 0; */
	*(ptr ++) = 0;		    /* vdi_ptsin[5] = 0; */
	*(ptr ++) = radius;	    /* vdi_ptsin[6] = radius; */
	*(ptr   ) = 0;			/* vdi_ptsin[7] = 0; */

	VDI_TRAP_ESC (vdi_params, handle, 11,3, 4,2);
}

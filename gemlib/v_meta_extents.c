/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** updates the extent of the metafile graphic and saves it in the 
 *  metafile header.
 *
 *  @param handle Device handle
 *  @param min_x 
 *  @param min_y 
 *  @param max_x 
 *  @param max_y 
 *
 *  @since all VDI versions
 *
 *  The extents information may
 *	be used by some applications to provide a quick
 *	indication of the minimum rectangle which will
 *	bound all primitives output to the metafile.
 *
 *	If the Update Metafile Extents escape is not
 *	used when outputting to the metafile, zeroes
 *	will be written in the extents information
 *	portion of the metafile header.
 */

void
v_meta_extents (short handle,
                short min_x, short min_y, short max_x, short max_y)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_ptsin[4];   

	VDI_PARAMS(vdi_control, 0L, vdi_ptsin, vdi_dummy, vdi_dummy );
	
	vdi_ptsin[0] = min_x;
	vdi_ptsin[1] = min_y;
	vdi_ptsin[2] = max_x;
	vdi_ptsin[3] = max_y;
	
	VDI_TRAP_ESC (vdi_params, handle, 5,98, 2,0);
}

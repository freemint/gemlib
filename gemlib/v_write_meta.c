/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** allows you to save application specific opcodes in a 
 *  metafile. Opcodes 0 to 100 are reserved, the range above it can be used.
 *
 *  @param handle Device handle
 *  @param numvdi_intin 
 *  @param avdi_intin 
 *  @param num_ptsin 
 *  @param a_ptsin 
 *
 *  @since all VDI versions
 *
 *  The opcode is stored in a_intin[0].
 *
 */

void
v_write_meta (short handle, short numvdi_intin, short *avdi_intin,
              short num_ptsin, short *a_ptsin)
{
	short vdi_control[VDI_CNTRLMAX]; 

	VDI_PARAMS(vdi_control, avdi_intin, a_ptsin, vdi_dummy, vdi_dummy );
	
	VDI_TRAP_ESC (vdi_params, handle, 5,99, num_ptsin,numvdi_intin);
}

/*
 *   special graphic funkcion
 */

#include "gem_vdiP.h"


void
v_form_adv (short handle)
{
	VDI_TRAP_ESC (vdi_params, handle, 5,20, 0,0);
}

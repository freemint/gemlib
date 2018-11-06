#include "gem_vdiP.h"
#include "mt_gemx.h"
#include "vdi_userdef.h"


/** UDEF version of vqt_fontheader(). See \ref overviewUDEF for details about UDEF feature
 */

void
udef_vqt_fontheader (short handle, char *buffer, char *pathname)
{
	VDI_PARAMS(_VDIParBlk.vdi_control, (short*)&buffer, 0L, _VDIParBlk.vdi_intout, vdi_dummy);
		
	VDI_TRAP (vdi_params, handle, 232, 0,2);
	
	vdi_array2str (_VDIParBlk.vdi_intout, pathname, _VDIParBlk.vdi_control[4]);
}

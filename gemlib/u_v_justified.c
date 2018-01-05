/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "vdi_userdef.h"


/** UDEF version of v_justified(). See \ref overviewUDEF for details about UDEF feature
 */

void
udef_v_justified (short handle, short x, short y,
             const char *str, short len, short word_space, short char_space)
{
	short n = 2 + vdi_str2array_n (str, _VDIParBlk.vdi_intin + 2, VDI_INTINMAX-2);

	_VDIParBlk.vdi_ptsin[0] = x;
	_VDIParBlk.vdi_ptsin[1] = y;

	if(n<VDI_INTINMAX) /* v_justified can be used */
	{
		VDI_PARAMS(_VDIParBlk.vdi_control, _VDIParBlk.vdi_intin, _VDIParBlk.vdi_ptsin, vdi_dummy, vdi_dummy );

		_VDIParBlk.vdi_intin[0] = word_space;
		_VDIParBlk.vdi_intin[1] = char_space;
		_VDIParBlk.vdi_ptsin[2] = len;
		_VDIParBlk.vdi_ptsin[3] = 0;

		VDI_TRAP_ESC (vdi_params, handle, 11,10, 2,n);
	}
	else /* gemlib limitation use v_gtext in replacement */
	{
		VDI_PARAMS(_VDIParBlk.vdi_control, &_VDIParBlk.vdi_intin[2], _VDIParBlk.vdi_ptsin, vdi_dummy, vdi_dummy );
		VDI_TRAP (vdi_params, handle, 8, 1,n);
	}
}


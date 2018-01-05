/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"
#include "vdi_userdef.h"


static inline void
_v_bez (short count, short *xyarr, char *bezarr, short *vdi_intin, short *vdi_ptsin)
{
	char  *opbd = (char*)vdi_intin;
	short *optr = vdi_ptsin;
	short *end;

	end = (short*)(bezarr + count);
	while (bezarr < (char*)end) {
		*(opbd +1) = *bezarr++;
		if (bezarr >= (char*)end)
			break;
		*opbd = *bezarr++;
		opbd += 2;
	}
	end = optr + (count *2);
	while (optr < end) {
		*(optr++) = *(xyarr++);
	}
}


/** UDEF version of v_bez(). See \ref overviewUDEF for details about UDEF feature
 */

void
udef_v_bez (short handle, short count, short *xyarr, char *bezarr,
       short *extent, short *totpts, short *totmoves)
{
	VDI_PARAMS( _VDIParBlk.vdi_control, _VDIParBlk.vdi_intin, _VDIParBlk.vdi_ptsin, _VDIParBlk.vdi_intout, extent);
	if(count>VDI_INTINMAX) return;
	
	
	_v_bez (count, xyarr, bezarr, _VDIParBlk.vdi_intin, _VDIParBlk.vdi_ptsin);
	
	VDI_TRAP_ESC (vdi_params, handle, 6,13, count,(count +1) /2);
	
	*totpts   = _VDIParBlk.vdi_intout[0];
	*totmoves = _VDIParBlk.vdi_intout[1];
}

/** UDEF version of v_bez_fill(). See \ref overviewUDEF for details about UDEF feature
 */


void
udef_v_bez_fill (short handle, short count, short *xyarr, char *bezarr,
            short *extent, short *totpts, short *totmoves)
{


	VDI_PARAMS (_VDIParBlk.vdi_control, _VDIParBlk.vdi_intin, _VDIParBlk.vdi_ptsin, _VDIParBlk.vdi_intout, extent);
	if(count>VDI_INTINMAX) return;
	
	
	_v_bez (count, xyarr, bezarr, _VDIParBlk.vdi_intin, _VDIParBlk.vdi_ptsin);
	
	VDI_TRAP_ESC (vdi_params, handle, 9,13, count,(count +1) /2);
	
	*totpts   = _VDIParBlk.vdi_intout[0];
	*totmoves = _VDIParBlk.vdi_intout[1];
}

/*
 *   NOTE: requires NVDI version 2.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


static inline void
_v_bez (short count, short *xyarr, char *bezarr)
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


void
v_bez (short handle, short count, short *xyarr, char *bezarr,
       short *extent, short *totpts, short *totmoves)
{
	vdi_params.ptsout = extent;
	
	_v_bez (count, xyarr, bezarr);
	
	VDI_TRAP_ESC (vdi_params, handle, 6,13, count,(count +1) /2);
	
	vdi_params.ptsout = vdi_ptsout;
	
	*totpts   = vdi_intout[0];
	*totmoves = vdi_intout[1];
}


void
v_bez_fill (short handle, short count, short *xyarr, char *bezarr,
            short *extent, short *totpts, short *totmoves)
{
	vdi_params.ptsout = extent;
	
	_v_bez (count, xyarr, bezarr);
	
	VDI_TRAP_ESC (vdi_params, handle, 9,13, count,(count +1) /2);
	
	vdi_params.ptsout = vdi_ptsout;
	
	*totpts   = vdi_intout[0];
	*totmoves = vdi_intout[1];
}

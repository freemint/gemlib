
#include "gemx.h"


static inline void
_v_bez (short ctrl0, short handle, short count, short *xyarr, char *bezarr,
	short *extent, short *totpts, short *totmoves)
{
	short *end;
	char *pbd = bezarr;
	char *opbd = (char *) vdi_intin;
	short *optr;

	end = (short *) (pbd + count);
	while (pbd < (char *) end)
	{
		*(opbd + 1) = *pbd++;
		if (pbd >= (char *) end)
			break;
		*opbd = *pbd++;
		opbd += 2;
	}
	optr = vdi_ptsin;
	end = optr + count + count;
	while (optr < end)
		*optr++ = *xyarr++;

	vdi_control[0] = ctrl0;
	vdi_control[1] = count;
	vdi_control[3] = ((count + 1) >> 1);
	vdi_control[5] = 13;
	vdi_control[6] = handle;
	vdi (&vdi_params);

	extent[0] = vdi_ptsout[0];
	extent[1] = vdi_ptsout[1];
	extent[2] = vdi_ptsout[2];
	extent[3] = vdi_ptsout[3];
	*totpts = vdi_intout[0];
	*totmoves = vdi_intout[1];
}

/*
 * * NOTE: requires NVDI version 2.x or higher
 */

void
v_bez (short handle, short count, short *xyarr, char *bezarr, short *extent,
       short *totpts, short *totmoves)
{
	_v_bez (6, handle, count, xyarr, bezarr, extent, totpts, totmoves);
}

void
v_bez_fill (short handle, short count, short *xyarr, char *bezarr, short *extent,
	    short *totpts, short *totmoves)
{
	_v_bez (9, handle, count, xyarr, bezarr, extent, totpts, totmoves);
}


#include "gemx.h"


void
v_bez_fill (int handle, int count, int *xyarr, char *bezarr, int *extent,
	    int *totpts, int *totmoves)
{
	_v_bez (9, handle, count, xyarr, bezarr, extent, totpts, totmoves);
}

/*
 * * NOTE: requires NVDI version 2.x or higher
 */


#include <macros.h>
#include "gem.h"


short
rc_intersect (GRECT * r1, GRECT * r2)
{
	short tx, ty, tw, th, ret;

	tx = max (r2->g_x, r1->g_x);
	tw = min (r2->g_x + r2->g_w, r1->g_x + r1->g_w) - tx;
	
	ret = (0 < tw);
	if (ret)
	{
		ty = max (r2->g_y, r1->g_y);
		th = min (r2->g_y + r2->g_h, r1->g_y + r1->g_h) - ty;
		
		ret = (0 < th);
		if (ret)
		{
			r2->g_x = tx;
			r2->g_y = ty;
			r2->g_w = tw;
			r2->g_h = th;
		}
	}
	
	return ret;
}

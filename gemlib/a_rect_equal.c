
#include "gem.h"


short
rc_equal (GRECT * p1, GRECT * p2)
{
	return ((p1->g_x == p2->g_x) &&
		(p1->g_y == p2->g_y) &&
		(p1->g_w == p2->g_w) && (p1->g_h == p2->g_h));
}

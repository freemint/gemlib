
#include "gem.h"


short *
grect_to_array (GRECT * area, short *array)
{
	short *ip = array;

	*ip = area->g_x;
	ip[2] = *ip;
	ip++;
	*ip = area->g_y;
	ip[2] = *ip;
	ip++;
	*ip++ += area->g_w - 1;
	*ip += area->g_h - 1;
	
	return array;
}

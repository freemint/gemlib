
#include "gem.h"


int *
grect_to_array (GRECT * area, int *array)
{
	int *ip = array;

	*ip = area->g_x;
	ip[2] = *ip;
	ip++;
	*ip = area->g_y;
	ip[2] = *ip;
	ip++;
	*ip++ += area->g_w - 1;
	*ip += area->g_h - 1;
	return (array);
}

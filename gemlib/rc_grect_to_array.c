#include "gem.h"


short *
grect_to_array (const GRECT * area, short *array)
{
	long *p = (long*)array;
	
	p[0] = p[1] = *(const long*)area;
	array[2] += area->g_w -1;
	array[3] += area->g_h -1;
	
	return array;
}

#include "gem.h"


GRECT *
array_to_grect (const short *array, GRECT * area)
{
	long *p = (long*)area;
	
	p[0] = p[1] = *(const long*)array;
	area->g_w -= array[0] -1;
	area->g_h -= array[1] -1;
	
	return area;
}

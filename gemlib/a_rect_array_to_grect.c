
#include "gem.h"


void
array_to_grect (int *array, GRECT * area)
{
	area->g_x = array[0];
	area->g_y = array[1];
	area->g_w = array[2] - array[0] + 1;
	area->g_h = array[3] - array[1] + 1;
}

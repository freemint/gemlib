/*
 *  $Id$
 */

#include "gem.h"

/** transform a GRECT structure to a PXY-array structure
 *
 *  @param area specify the area using a GRECT structure
 *  @param array will then contain the area in a PXY-array
 *
 *  @return \p array is returned.
 *
 *  @sa array_to_grect()
 *
 */

short *
grect_to_array (const GRECT * area, short *array)
{
	long *p = (long*)array;
	
	p[0] = p[1] = *(const long*)area;
	array[2] += area->g_w -1;
	array[3] += area->g_h -1;
	
	return array;
}

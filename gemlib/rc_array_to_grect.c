/*
 *  $Id$
 */

#include "mt_gem.h"
#include "gem.h"

/** transform a PXY-array structure to a GRECT structure
 *
 *  @param array specify the area using a PXY-array
 *  @param area will then contain the area in a GRECT structure
 *
 *  @return \p area is returned.
 *
 *  @sa 
 *
 */

GRECT *
array_to_grect (const short *array, GRECT * area)
{
	long *p = (long*)area;
	
	p[0] = p[1] = *(const long*)array;
	area->g_w -= array[0] -1;
	area->g_h -= array[1] -1;
	
	return area;
}

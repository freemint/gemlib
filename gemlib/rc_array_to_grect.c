/*
 *  $Id$
 */

#include "mt_gem.h"

/** transform a PXY-array structure to a GRECT structure
 *
 *  @param array specify the area using a PXY-array
 *  @param area will then contain the area in a GRECT structure
 *
 *  @return \p area is returned.
 *
 *  @sa grect_to_array() 
 *
 */

GRECT *
array_to_grect (const short *array, GRECT * area)
{
	area->g_x = array[0];
	area->g_y = array[1];
	area->g_w = array[2]-array[0]+1;
	area->g_w = array[3]-array[1]+1;
	
	return area;
}

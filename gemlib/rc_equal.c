/*
 *  $Id$
 */

#include "mt_gem.h"

/** return non-zero value if both area are equal
 *
 *  @param p1 an area
 *  @param p2 an other area
 *
 *  @return 0 if \p p1 and \p p2 are not the same area, any other
 *          value (not 0) otherwise (\p p1 equal \p p2).
 *
 */
 
short
rc_equal (const GRECT * p1, const GRECT * p2)
{
	const long * a = (const long*)p1,
	           * b = (const long*)p2;
	
	return ((a[0] == b[0]) && (a[1] == b[1]));
}

#include "gem.h"


short
rc_equal (const GRECT * p1, const GRECT * p2)
{
	const long * a = (const long*)p1,
	           * b = (const long*)p2;
	
	return ((a[0] == b[0]) && (a[1] == b[1]));
}

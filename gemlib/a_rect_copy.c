
#include "gem.h"


short
rc_copy (GRECT * src, GRECT * dst)
{
	*dst = *src;
	return 1;
}

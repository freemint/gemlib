#include "gem.h"


short
rc_copy (const GRECT * src, GRECT * dst)
{
	*dst = *src;
	return 1;
}

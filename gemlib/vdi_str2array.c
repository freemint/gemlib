
#include "gem.h"


short
vdi_str2array (const char *src, short *des)
{
	short                 len = 0;
	const unsigned char *c  = (const unsigned char *) src;

	while (*c)
	{
		*(des++) = *(c++);
		len++;
	}
	return len;
}

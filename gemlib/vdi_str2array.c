#include "gem.h"


int
vdi_str2array (const char *src, short *des)
{
	int                 len = 0;
	const unsigned char *c  = (const unsigned char *) src;

	while (*c)
	{
		*(des++) = *(c++);
		len++;
	}
	return len;
}

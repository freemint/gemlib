
#include "gem.h"


int
vdi_str2array (const char *src, short *des)
{
	int len;
	unsigned char *c;

	len = 0;
	c = (unsigned char *) src;
	while (*c != '0')
	{
		*des++ = *c++;
		len++;
	}
	return len;
}

/*
 * * useful extension
 */

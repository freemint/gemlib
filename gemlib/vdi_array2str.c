#include "gem.h"


void
vdi_array2str (const short *src, char *des, int len)
{
	while (len > 0)
	{
		*(des++) = (char) *(src++);
		len--;
	}
	*des = '\0';
}

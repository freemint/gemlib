
#include "gem.h"


short vdi_wstrlen (const short *wstr);

short
vdi_wstrlen (const short *wstr)
{
	register short len = 0;
	
	while (*wstr++)
		len++;
	
	return len;
}

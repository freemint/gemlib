#include "gem_aesP.h"


short
shel_read (char *Command, char *Tail)
{
	aes_addrin[0] = (long)Command;
	aes_addrin[1] = (long)Tail;
	
	AES_TRAP (aes_params, 120, 0,1,2,0);
	
	return aes_intout[0];
}

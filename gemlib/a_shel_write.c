#include "gem_aesP.h"


short
shel_write (short wodex, short wisgr, short wiscr, void *cmd, char *tail)
{
	aes_intin[0]  = wodex;
	aes_intin[1]  = wisgr;
	aes_intin[2]  = wiscr;
	aes_addrin[0] = (long)cmd;
	aes_addrin[1] = (long)tail;
	
	AES_TRAP (aes_params, 121, 3,1,2,0);
	
	return aes_intout[0];
}

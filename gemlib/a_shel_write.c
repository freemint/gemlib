
#include "gem.h"


short
shel_write (short wodex, short wisgr, short wiscr, void *cmd, char *tail)
{
	aes_intin[0] = wodex;
	aes_intin[1] = wisgr;
	aes_intin[2] = wiscr;
	
	aes_addrin[0] = (long) cmd;
	aes_addrin[1] = (long) tail;
	
	aes_control[0] = 121;
	aes_control[1] = 3;
	aes_control[2] = 1;
	aes_control[3] = 2;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return aes_intout[0];
}

#include "gem_aesP.h"


short
graf_watchbox (OBJECT *Tree, short Object, short InState, short OutState)
{
	aes_addrin[0] = (long) Tree;
	
	aes_intin[0] = 0;
	aes_intin[1] = Object;
	aes_intin[2] = InState;
	aes_intin[3] = OutState;
	
	AES_TRAP (aes_params, 75, 4,1,1,0);
	
	return aes_intout[0];
}

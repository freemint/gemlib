
#include "gem.h"


short
graf_watchbox (OBJECT *Tree, short Object, short InState, short OutState)
{
	aes_addrin[0] = (long) Tree;
	
	aes_intin[0] = 0;
	aes_intin[1] = Object;
	aes_intin[2] = InState;
	aes_intin[3] = OutState;
	
	aes_control[0] = 75;
	aes_control[1] = 4;
	aes_control[2] = 1;
	aes_control[3] = 1;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return aes_intout[0];
}

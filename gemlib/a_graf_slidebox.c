#include "gem_aesP.h"


short
graf_slidebox (OBJECT *Tree, short Parent, short Object, short Direction)
{
	aes_addrin[0] = (long) Tree;
	
	aes_intin[0] = Parent;
	aes_intin[1] = Object;
	aes_intin[2] = Direction;
	
	AES_TRAP (aes_params, 76, 3,1,1,0);
	
	return aes_intout[0];
}


#include "gem.h"


int
graf_slidebox (void *Tree, int Parent, int Object, int Direction)
{
	aes_addrin[0] = (long) Tree;
	aes_intin[0] = Parent;
	aes_intin[1] = Object;
	aes_intin[2] = Direction;
	aes_control[0] = 76;
	aes_control[1] = 3;
	aes_control[2] = 1;
	aes_control[3] = 1;
	aes_control[4] = 0;
	aes (&aes_params);
	return aes_intout[0];
}

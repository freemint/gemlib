
#include "gem.h"


int
objc_add (void *Tree, int Parent, int Child)
{
	aes_intin[0] = Parent;
	aes_intin[1] = Child;
	aes_addrin[0] = (long) Tree;
	aes_control[0] = 40;
	aes_control[1] = 2;
	aes_control[2] = 1;
	aes_control[3] = 1;
	aes_control[4] = 0;
	aes (&aes_params);
	return aes_intout[0];
}

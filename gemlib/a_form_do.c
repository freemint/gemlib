
#include "gem.h"


int
form_do (void *Tree, int StartObj)
{
	aes_intin[0] = StartObj;
	aes_addrin[0] = (long) Tree;
	aes_control[0] = 50;
	aes_control[1] = 1;
	aes_control[2] = 1;
	aes_control[3] = 1;
	aes_control[4] = 0;
	aes (&aes_params);
	return aes_intout[0];
}

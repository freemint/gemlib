
#include "gem.h"


int
rsrc_obfix (void *Tree, int Index)
{
	aes_intin[0] = Index;
	aes_addrin[0] = (long) Tree;
	aes_control[0] = 114;
	aes_control[1] = 1;
	aes_control[2] = 1;
	aes_control[3] = 1;
	aes_control[4] = 0;
	aes (&aes_params);
	return aes_intout[0];
}


#include "gem.h"


int
objc_edit (void *Tree, int Object, int Char, int *Index, int Kind)
{
	aes_intin[0] = Object;
	aes_intin[1] = Char;
	aes_intin[2] = *Index;
	aes_intin[3] = Kind;
	aes_addrin[0] = (long) Tree;
	aes_control[0] = 46;
	aes_control[1] = 4;
	aes_control[2] = 2;
	aes_control[3] = 1;
	aes_control[4] = 0;
	aes (&aes_params);
	*Index = aes_intout[1];
	return aes_intout[0];
}

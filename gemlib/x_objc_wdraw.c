#include "gem_aesP.h"
#include "gemx.h"


void
objc_wdraw (OBJECT *tree, short start, short depth, GRECT *clip, short whandle)
{
	aes_intin[0] = start;
	aes_intin[1] = depth;
	aes_intin[2] = whandle;

	aes_addrin[0] = (long) tree;
	aes_addrin[1] = (long) clip;

	aes_control[0] = 60;
	aes_control[1] = 3;
	aes_control[2] = 0;
	aes_control[3] = 2;
	aes_control[4] = 0;

	aes (&aes_params);
}

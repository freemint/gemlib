
#include "gemx.h"


void
objc_wdraw (OBJECT * tree, int start, int depth, GRECT * clip, int whandle)
{
#ifndef __MSHORT__
	short srect[4];

	srect[0] = clip->g_x;
	srect[1] = clip->g_y;
	srect[2] = clip->g_w;
	srect[3] = clip->g_h;
	aes_addrin[1] = (long) srect;
#else
	aes_addrin[1] = (long) clip;
#endif
	aes_intin[0] = start;
	aes_intin[1] = depth;
	aes_intin[2] = whandle;
	aes_addrin[0] = (long) tree;
	aes_control[0] = 60;
	aes_control[1] = 3;
	aes_control[2] = 0;
	aes_control[3] = 2;
	aes_control[4] = 0;
	aes (&aes_params);
}

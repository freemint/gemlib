
#include "gemx.h"


int
objc_xedit (OBJECT * tree, int obj, int key, int *xpos, int subfn, GRECT * r)
{
#ifndef __MSHORT__
	short srect[4];

	srect[0] = r->g_x;
	srect[1] = r->g_y;
	srect[2] = r->g_w;
	srect[3] = r->g_h;
	aes_addrin[1] = (long) srect;
#else
	aes_addrin[1] = (long) r;
#endif
	aes_intin[0] = obj;
	aes_intin[1] = key;
	aes_intin[2] = *xpos;
	aes_intin[3] = subfn;
	aes_addrin[0] = (long) tree;
	aes_control[0] = 46;
	aes_control[1] = 4;
	aes_control[2] = 2;
	aes_control[3] = 2;
	aes_control[4] = 0;
	aes (&aes_params);
	*xpos = aes_intout[1];
	return aes_intout[0];
}

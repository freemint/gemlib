#include "gemx.h"
#include "gem_aesP.h"


short
objc_xedit (OBJECT *tree, short obj, short key, short *xpos, short subfn, GRECT *r)
{
	aes_intin[0] = obj;
	aes_intin[1] = key;
	aes_intin[2] = *xpos;
	aes_intin[3] = subfn;

	aes_addrin[0] = (long) tree;
	aes_addrin[1] = (long) r;

	aes_control[0] = 46;
	aes_control[1] = 4;
	aes_control[2] = 2;
	aes_control[3] = 2;
	aes_control[4] = 0;

	aes (&aes_params);

	*xpos = aes_intout[1];

	return aes_intout[0];
}

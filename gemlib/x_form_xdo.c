#include "gemx.h"
#include "gem_aesP.h"


short
form_xdo (OBJECT * tree, short startob, short *lastcrsr, XDO_INF * tabs,
	  void *flydial)
{
	aes_intin[0] = startob;
	aes_addrin[0] = (long) tree;
	aes_addrin[1] = (long) tabs;
	aes_addrin[2] = (long) flydial;
	aes_control[0] = 50;
	aes_control[1] = 1;
	aes_control[2] = 2;
	aes_control[3] = 3;
	aes_control[4] = 0;
	aes (&aes_params);
	*lastcrsr = aes_intout[1];
	return aes_intout[0];
}

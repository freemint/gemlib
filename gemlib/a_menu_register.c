
#include "gem.h"


int
menu_register (int ApId, char *MenuText)
{
	aes_intin[0] = ApId;
	aes_addrin[0] = (long) MenuText;
	aes_control[0] = 35;
	aes_control[1] = 1;
	aes_control[2] = 1;
	aes_control[3] = 1;
	aes_control[4] = 0;
	aes (&aes_params);
	return aes_intout[0];
}

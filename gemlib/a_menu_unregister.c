
#include "gem.h"


int
menu_unregister (int id)
{
	aes_intin[0] = id;
	aes_control[0] = 36;
	aes_control[1] = 1;
	aes_control[2] = 1;
	aes_control[3] = 0;
	aes_control[4] = 0;
	aes (&aes_params);
	return aes_intout[0];
}

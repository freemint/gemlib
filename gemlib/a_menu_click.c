
#include "gem.h"


int
menu_click (int click, int setit)
{
	aes_intin[0] = click;
	aes_intin[1] = setit;
	aes_control[0] = 37;
	aes_control[1] = 2;
	aes_control[2] = 1;
	aes_control[3] = 0;
	aes_control[4] = 0;
	aes (&aes_params);
	return aes_intout[0];
}

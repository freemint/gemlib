
#include "gem.h"


int
menu_ienable (void *Tree, int Item, int EnableFlag)
{
	aes_addrin[0] = (long) Tree;
	aes_intin[0] = Item;
	aes_intin[1] = EnableFlag;
	aes_control[0] = 32;
	aes_control[1] = 2;
	aes_control[2] = 1;
	aes_control[3] = 1;
	aes_control[4] = 0;
	aes (&aes_params);
	return aes_intout[0];
}

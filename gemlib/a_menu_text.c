
#include "gem.h"


short
menu_text (void *Tree, short Item, char *Text)
{
	aes_addrin[0] = (long) Tree;
	aes_addrin[1] = (long) Text;
	
	aes_intin[0] = Item;
	
	aes_control[0] = 34;
	aes_control[1] = 1;
	aes_control[2] = 1;
	aes_control[3] = 2;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return aes_intout[0];
}

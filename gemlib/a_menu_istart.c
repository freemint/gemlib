
#include "gem.h"


int
menu_istart (int me_flag, OBJECT * me_tree, int me_imenu, int me_item)
{
	aes_intin[0] = me_flag;
	aes_intin[1] = me_imenu;
	aes_intin[2] = me_item;
	aes_addrin[0] = (long) me_tree;
	aes_control[0] = 38;
	aes_control[1] = 3;
	aes_control[2] = 1;
	aes_control[3] = 1;
	aes_control[4] = 0;
	aes (&aes_params);
	return aes_intout[0];
}

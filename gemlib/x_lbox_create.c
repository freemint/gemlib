
#include "gemx.h"


LIST_BOX *
lbox_create (OBJECT *tree, SLCT_ITEM slct, SET_ITEM set, LBOX_ITEM *items,
short visible_a, short first_a, short *ctrl_objs, short *objs,
short flags, short pause_a, void *user_data, void *dialog,
short visible_b, short first_b, short entries_b, short pause_b)
{
	aes_intin[0] = visible_a;
	aes_intin[1] = first_a;
	aes_intin[2] = flags;
	aes_intin[3] = pause_a;
	aes_intin[4] = visible_b;
	aes_intin[5] = first_b;
	aes_intin[6] = entries_b;
	aes_intin[7] = pause_b;
	
	aes_addrin[0] = (long) tree;
	aes_addrin[1] = (long) slct;
	aes_addrin[2] = (long) set;
	aes_addrin[3] = (long) items;
	aes_addrin[4] = (long) ctrl_objs;
	aes_addrin[5] = (long) objs;
	aes_addrin[6] = (long) user_data;
	aes_addrin[7] = (long) dialog;
	
	aes_control[0] = 170;
	aes_control[1] = 8;
	aes_control[2] = 0;
	aes_control[3] = 8;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return (LIST_BOX *) aes_addrout[0];
}

# include "extdef.h"

long
objc_edit(void *tree, short obj, short ch, short idx, short mode)
{
	GEM_ARRAY *gem;

	gem = gem_control();
	gem->addr_in[0] = (long)tree;
	gem->int_in[0] = obj;
	gem->int_in[1] = ch;
	gem->int_in[2] = idx;
	gem->int_in[3] = mode;

	return call_aes(gem, 46);
}

/* EOF */
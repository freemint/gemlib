# include "extdef.h"

long
objc_offset(void *tree, short obj, short *xo, short *yo)
{
	GEM_ARRAY *gem;
	long r;

	gem = gem_control();
	gem->addr_in[0] = (long)tree;
	gem->int_in[0] = obj;

	r = call_aes(gem, 44);

	if ((long)xo)
		*xo = gem->int_out[1];
	if ((long)yo)
		*yo = gem->int_out[2];

	return r;
}

/* EOF */

# include "extdef.h"

long
form_center(void *tree, short *cx, short *cy, short *cw, short *ch)
{
	long r;
# ifdef GEMMA_MULTIPROC
	GEM_ARRAY *gem;

	gem = gem_control();
# endif
	gem->addr_in[0] = (long)tree;

	r = (long)call_aes(gem, 54);

	*cx = gem->int_out[1];
	*cy = gem->int_out[2];
	*cw = gem->int_out[3];
	*ch = gem->int_out[4];

	return r;
}

/* EOF */

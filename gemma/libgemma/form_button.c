# include "extdef.h"

long
form_button(void *tree, short obj, short clks, short *nxobj)
{
	long r;
# ifdef GEMMA_MULTIPROC
	GEM_ARRAY *gem;

	gem = gem_control();
# endif
	gem->int_in[0] = obj;
	gem->int_in[1] = clks;

	gem->addr_in[0] = (long)tree;

	r = (long)call_aes(gem, 56);

	*nxobj = gem->int_out[1];

	return r;
}

/* EOF */

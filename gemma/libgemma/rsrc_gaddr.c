# include "extdef.h"

long
rsrc_gaddr(short type, short index, void **addr)
{
	long r;
# ifdef GEMMA_MULTIPROC
	GEM_ARRAY *gem;

	gem = gem_control();
# endif
	gem->int_in[0] = type;
	gem->int_in[1] = index;

	r = call_aes(gem, 112);

	*addr = (void *)gem->addr_out[0];

	return r;
}

/* EOF */

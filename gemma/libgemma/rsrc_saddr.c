# include "extdef.h"

long
rsrc_saddr(short type, short index, void *addr)
{
# ifdef GEMMA_MULTIPROC
	GEM_ARRAY *gem;

	gem = gem_control();
# endif
	gem->int_in[0] = type;
	gem->int_in[1] = index;

	gem->addr_in[0] = (long)addr;

	return call_aes(gem, 112);
}

/* EOF */

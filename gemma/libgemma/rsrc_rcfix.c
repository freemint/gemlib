# include "extdef.h"

long
rsrc_rcfix(void *header)
{
# ifdef GEMMA_MULTIPROC
	GEM_ARRAY *gem;

	gem = gem_control();
# endif
	gem->addr_in[0] = (long)header;

	return call_aes(gem, 115);
}

/* EOF */

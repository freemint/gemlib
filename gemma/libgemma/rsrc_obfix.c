# include "extdef.h"

long
rsrc_obfix(void *tree, short obj)
{
# ifdef GEMMA_MULTIPROC
	GEM_ARRAY *gem;

	gem = gem_control();
# endif
	gem->int_in[0] = obj;
	gem->addr_in[0] = (long)tree;

	return call_aes(gem, 114);
}

/* EOF */

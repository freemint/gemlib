# include "extdef.h"

long
form_do(void *tree, short obj)
{
# ifdef GEMMA_MULTIPROC
	GEM_ARRAY *gem;

	gem = gem_control();
# endif
	gem->int_in[0] = obj;
	gem->addr_in[0] = (long)tree;

	return (long)call_aes(gem, 50);
}

/* EOF */

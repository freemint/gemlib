# include "extdef.h"

long
graf_watchbox(void *tree, short obj, short inst, short outst)
{
# ifdef GEMMA_MULTIPROC
	GEM_ARRAY *gem;

	gem = gem_control();
# endif

	gem->int_in[0] = 0;
	gem->int_in[1] = obj;
	gem->int_in[2] = inst;
	gem->int_in[3] = outst;

	gem->addr_in[0] = (long)tree;

	return call_aes(gem, 75);
}

/* EOF */

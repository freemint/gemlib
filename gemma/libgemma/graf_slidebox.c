# include "extdef.h"

long
graf_slidebox(void *tree, short parent, short obj, short slvh)
{
# ifdef GEMMA_MULTIPROC
	GEM_ARRAY *gem;

	gem = gem_control();
# endif

	gem->int_in[0] = parent;
	gem->int_in[1] = obj;
	gem->int_in[2] = slvh;

	gem->addr_in[0] = (long)tree;

	return call_aes(gem, 76);
}

/* EOF */

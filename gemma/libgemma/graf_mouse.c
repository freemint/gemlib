# include "extdef.h"

long
graf_mouse(short num, void *addr)
{
# ifdef GEMMA_MULTIPROC
	GEM_ARRAY *gem;

	gem = gem_control();
# endif
	gem->int_in[0] = num;
	gem->addr_in[0] = (long)addr;

	return call_aes(gem, 78);
}

/* EOF */

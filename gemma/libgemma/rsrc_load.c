# include "extdef.h"

long
rsrc_load(char *fname)
{
# ifdef GEMMA_MULTIPROC
	GEM_ARRAY *gem;

	gem = gem_control();
# endif
	gem->addr_in[0] = (long)fname;

	return call_aes(gem, 110);
}

/* EOF */

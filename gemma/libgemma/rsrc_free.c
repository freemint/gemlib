# include "extdef.h"

long
rsrc_free(void)
{
# ifdef GEMMA_MULTIPROC
	GEM_ARRAY *gem;

	gem = gem_control();
# endif
	return call_aes(gem, 111);
}

/* EOF */

# include "extdef.h"

/* PC GEM call, emulated by the library */

long
scrp_clear(void)
{
# ifdef GEMMA_MULTIPROC
	GEM_ARRAY *gem;

	gem = gem_control();
# endif

	return call_aes(gem, 82);
}

/* EOF */

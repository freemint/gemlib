# include "extdef.h"

long
wind_update(short begend)
{
# ifdef GEMMA_MULTIPROC
	GEM_ARRAY *gem;

	gem = gem_control();
# endif
	gem->int_in[0] = begend;

	return call_aes(gem, 107);
}

/* EOF */

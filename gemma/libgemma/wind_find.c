# include "extdef.h"

long
wind_find(short fmx, short fmy)
{
# ifdef GEMMA_MULTIPROC
	GEM_ARRAY *gem;

	gem = gem_control();
# endif
	gem->int_in[0] = fmx;
	gem->int_in[1] = fmy;

	return call_aes(gem, 106);
}

/* EOF */

# include "extdef.h"

long
wind_delete(short handle)
{
# ifdef GEMMA_MULTIPROC
	GEM_ARRAY *gem;

	gem = gem_control();
# endif
	gem->int_in[0] = handle;

	return call_aes(gem, 103);
}

/* EOF */

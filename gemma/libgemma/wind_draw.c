# include "extdef.h"

long
wind_draw(short handle, short obj)
{
# ifdef GEMMA_MULTIPROC
	GEM_ARRAY *gem;

	gem = gem_control();
# endif
	gem->int_in[0] = handle;
	gem->int_in[1] = obj;

	return call_aes(gem, 99);
}

/* EOF */

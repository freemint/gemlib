# include "extdef.h"

long
appl_exit(void)
{
	GEM_ARRAY *gem;

	gem = gem_control();

	return call_aes(gem, 19);
}

/* EOF */

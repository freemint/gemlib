# include "extdef.h"

long
appl_init(void)
{
	GEM_ARRAY *gem;

	gem = gem_control();

	return call_aes(gem, 10);
}

/* EOF */
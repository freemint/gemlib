# include "extdef.h"

long
appl_find(char *name)
{
	GEM_ARRAY *gem;

	gem = gem_control();
	gem->addr_in[0] = (long)name;

	return call_aes(gem, 13);
}

/* EOF */

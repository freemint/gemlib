# include "extdef.h"

long
appl_trecord(void *mem, short count)
{
	GEM_ARRAY *gem;

	gem = gem_control();
	gem->addr_in[0] = (long)mem;
	gem->int_in[0] = count;

	return call_aes(gem, 15);
}

/* EOF */
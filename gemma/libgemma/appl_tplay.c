# include "extdef.h"

long
appl_tplay(void *mem, short num, short scale)
{
	GEM_ARRAY *gem;

	gem = gem_control();
	gem->addr_in[0] = (long)mem;
	gem->int_in[0] = num;
	gem->int_in[1] = scale;

	return call_aes(gem, 14);
}

/* EOF */
# include "extdef.h"

long
appl_search(short mode, char *fname, short *type, short *apid)
{
	GEM_ARRAY *gem;
	long r;

	gem = gem_control();
	gem->int_in[0] = mode;
	gem->addr_in[0] = (long)fname;

	r = call_aes(gem, 18);

	*type = gem->int_out[1];
	*apid = gem->int_out[2];

	return r;
}

/* EOF */

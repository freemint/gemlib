# include "extdef.h"

long
appl_control(short cid, short cwhat, void *out)
{
	GEM_ARRAY *gem;

	gem = gem_control();
	gem->int_in[0] = cid;
	gem->int_in[1] = cwhat;
	gem->addr_in[0] = (long)out;

	return call_aes(gem, 129);
}

/* EOF */

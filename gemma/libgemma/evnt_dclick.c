# include "extdef.h"

long
evnt_dclick(short dnew, short dset)
{
	GEM_ARRAY *gem;

	gem = gem_control();
	gem->int_in[0] = dnew;
	gem->int_in[1] = dset;

	return call_aes(gem, 26);
}

/* EOF */
# include "extdef.h"

long
wind_get(short handle, short field, short *gw1, short *gw2, short *gw3, short *gw4)
{
	long r;
# ifdef GEMMA_MULTIPROC
	GEM_ARRAY *gem;

	gem = gem_control();
# endif
	gem->int_in[0] = handle;
	gem->int_in[1] = field;

	r = call_aes(gem, 104);

	*gw1 = gem->int_out[1];
	*gw2 = gem->int_out[2];
	*gw3 = gem->int_out[3];
	*gw4 = gem->int_out[4];

	return r;
}

/* EOF */

# include "extdef.h"

long
wind_set(short handle, short field, short sw1, short sw2, short sw3, short sw4)
{
# ifdef GEMMA_MULTIPROC
	GEM_ARRAY *gem;

	gem = gem_control();
# endif
	gem->int_in[0] = handle;
	gem->int_in[1] = field;
	gem->int_in[2] = sw1;
	gem->int_in[3] = sw2;
	gem->int_in[4] = sw3;
	gem->int_in[5] = sw4;
	
	return call_aes(gem, 105);
}

/* EOF */

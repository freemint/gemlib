# include "extdef.h"

long
wind_open(short handle, short wx, short wy, short ww, short wh)
{
# ifdef GEMMA_MULTIPROC
	GEM_ARRAY *gem;

	gem = gem_control();
# endif
	gem->int_in[0] = handle;
	gem->int_in[1] = wx;
	gem->int_in[2] = wy;
	gem->int_in[3] = ww;
	gem->int_in[4] = wh;

	return call_aes(gem, 101);
}

/* EOF */

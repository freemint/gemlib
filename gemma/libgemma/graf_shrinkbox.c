# include "extdef.h"

long
graf_shrinkbox(short fx, short fy, short fw, short fh, \
		short sx, short sy, short sw, short sh)
{
# ifdef GEMMA_MULTIPROC
	GEM_ARRAY *gem;

	gem = gem_control();
# endif

	gem->int_in[0] = fx;
	gem->int_in[1] = fy;
	gem->int_in[2] = fw;
	gem->int_in[3] = fh;
	gem->int_in[4] = sx;
	gem->int_in[5] = sy;
	gem->int_in[6] = sw;
	gem->int_in[7] = sh;

	return call_aes(gem, 74);
}

/* EOF */

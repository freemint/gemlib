# include "extdef.h"

long
graf_growbox(short sx, short sy, short sw, short sh, \
		short fx, short fy, short fw, short fh)
{
# ifdef GEMMA_MULTIPROC
	GEM_ARRAY *gem;

	gem = gem_control();
# endif

	gem->int_in[0] = sx;
	gem->int_in[1] = sy;
	gem->int_in[2] = sw;
	gem->int_in[3] = sh;
	gem->int_in[4] = fx;
	gem->int_in[5] = fy;
	gem->int_in[6] = fw;
	gem->int_in[7] = fh;

	return call_aes(gem, 73);
}

/* EOF */

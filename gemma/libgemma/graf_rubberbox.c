# include "extdef.h"

long
graf_rubberbox(short gx, short gy, short mw, short mh, \
		short *lw, short *lh)
{
	long r;
# ifdef GEMMA_MULTIPROC
	GEM_ARRAY *gem;

	gem = gem_control();
# endif

	gem->int_in[0] = gx;
	gem->int_in[1] = gy;
	gem->int_in[2] = mw;
	gem->int_in[3] = mh;

	r = call_aes(gem, 70);

	*lw = gem->int_out[1];
	*lh = gem->int_out[2];

	return r;
}

/* EOF */

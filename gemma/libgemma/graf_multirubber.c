# include "extdef.h"

long
graf_multirubber(short gx, short gy, short mw, short mh, GRECT *rec, \
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

	gem->addr_in[0] = (long)rec;

	r = call_aes(gem, 69);

	*lw = gem->int_out[1];
	*lh = gem->int_out[2];

	return r;
}

/* EOF */

# include "extdef.h"

long
graf_movebox(short mw, short mh, short msx, short msy, \
		short mdx, short mdy)
{
# ifdef GEMMA_MULTIPROC
	GEM_ARRAY *gem;

	gem = gem_control();
# endif

	gem->int_in[0] = mw;
	gem->int_in[1] = mh;
	gem->int_in[2] = msx;
	gem->int_in[3] = msy;
	gem->int_in[4] = mdx;
	gem->int_in[5] = mdy;

	return call_aes(gem, 72);
}

/* EOF */

# include "extdef.h"

long
graf_mkstate(short *mx, short *my, short *mks, short *kks)
{
	long r;
# ifdef GEMMA_MULTIPROC
	GEM_ARRAY *gem;

	gem = gem_control();
# endif

	r = call_aes(gem, 79);

	*mx  = gem->int_out[1];
	*my  = gem->int_out[2];
	*mks = gem->int_out[3];
	*kks = gem->int_out[4];

	return r;
}

/* EOF */

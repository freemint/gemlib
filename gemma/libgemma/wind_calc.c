# include "extdef.h"

long
wind_calc(short type, short kind, short inx, short iny, short inw, short inh, \
		short *outx, short *outy, short *outw, short *outh)
{
	long r;
# ifdef GEMMA_MULTIPROC
	GEM_ARRAY *gem;

	gem = gem_control();
# endif
	gem->int_in[0] = type;
	gem->int_in[1] = kind;
	gem->int_in[2] = inx;
	gem->int_in[3] = iny;
	gem->int_in[4] = inw;
	gem->int_in[5] = inh;

	r = call_aes(gem, 108);

	*outx = gem->int_out[1];
	*outy = gem->int_out[2];
	*outw = gem->int_out[3];
	*outh = gem->int_out[4];

	return r;
}

/* EOF */

# include "extdef.h"

long
appl_getinfo(short cwhat, \
		short *out1, short *out2, short *out3, short *out4)
{
	GEM_ARRAY *gem;
	long r;

	gem = gem_control();
	gem->int_in[0] = cwhat;

	r = call_aes(gem, 130);

	*out1 = gem->int_out[1];
	*out2 = gem->int_out[2];
	*out3 = gem->int_out[3];
	*out4 = gem->int_out[4];

	return r;
}

/* EOF */

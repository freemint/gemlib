# include "extdef.h"

long
evnt_button(short bclicks, short bmask, short bstate, \
		short *mx, short *my, short *bbutton, short *kstate)
{
	GEM_ARRAY *gem;
	long r;

	gem = gem_control();
	gem->int_in[0] = bclicks;
	gem->int_in[1] = bmask;
	gem->int_in[2] = bstate;

	r = call_aes(gem, 24);

	*mx = gem->int_out[1];
	*my = gem->int_out[2];
	*bbutton = gem->int_out[3];
	*kstate = gem->int_out[4];

	return r;
}

/* EOF */
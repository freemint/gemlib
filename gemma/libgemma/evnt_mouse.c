# include "extdef.h"

long
evnt_mouse(short mof, short mox, short moy, short mow, short moh, \
		short *momx, short *momy, short *mobutton, short *mokstate)
{
	GEM_ARRAY *gem;
	long r;

	gem = gem_control();
	gem->int_in[0] = mof;
	gem->int_in[1] = mox;
	gem->int_in[2] = moy;
	gem->int_in[3] = mow;
	gem->int_in[4] = moh;

	r = call_aes(gem, 22);

	*momx = gem->int_out[1];
	*momy = gem->int_out[2];
	*mobutton = gem->int_out[3];
	*mokstate = gem->int_out[4];

	return r;
}

/* EOF */
# include "extdef.h"

long
graf_dragbox(short sw, short sh, short sx, short sy, \
		short bx, short by, short bw, short bh, \
		short *fx, short *fy)
{
	long r;
# ifdef GEMMA_MULTIPROC
	GEM_ARRAY *gem;

	gem = gem_control();
# endif

	gem->int_in[0] = sw;
	gem->int_in[1] = sh;
	gem->int_in[2] = sx;
	gem->int_in[3] = sy;
	gem->int_in[4] = bx;
	gem->int_in[5] = by;
	gem->int_in[6] = bw;
	gem->int_in[7] = bh;

	r = call_aes(gem, 71);

	*fx = gem->int_out[1];
	*fy = gem->int_out[2];

	return r;
}

/* EOF */

# include "extdef.h"

long
form_dial(short flag, short dix, short diy, short diw, short dih, \
		short cx, short cy, short cw, short ch)
{
# ifdef GEMMA_MULTIPROC
	GEM_ARRAY *gem;

	gem = gem_control();
# endif
	gem->int_in[0] = flag;
	gem->int_in[1] = dix;
	gem->int_in[2] = diy;
	gem->int_in[3] = diw;
	gem->int_in[4] = dih;
	gem->int_in[5] = cx;
	gem->int_in[6] = cy;
	gem->int_in[7] = cw;
	gem->int_in[8] = ch;

	return (long)call_aes(gem, 51);
}

/* EOF */

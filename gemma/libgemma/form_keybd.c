# include "extdef.h"

long
form_keybd(void *tree, short obj, short nobj, short thechar, short *nxobj, short *pchar)
{
	long r;
# ifdef GEMMA_MULTIPROC
	GEM_ARRAY *gem;

	gem = gem_control();
# endif
	gem->int_in[0] = obj;
	gem->int_in[1] = thechar;
	gem->int_in[2] = nobj;

	gem->addr_in[0] = (long)tree;

	r = (long)call_aes(gem, 55);

	*nxobj = gem->int_out[1];
	*pchar = gem->int_out[2];

	return r;
}

/* EOF */

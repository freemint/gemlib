# include "extdef.h"

long
form_error(short num)
{
# ifdef GEMMA_MULTIPROC
	GEM_ARRAY *gem;

	gem = gem_control();
# endif
	gem->int_in[0] = num;

	return (long)call_aes(gem, 53);
}

/* EOF */

# include "extdef.h"

long
form_alert(short button, char *string)
{
# ifdef GEMMA_MULTIPROC
	GEM_ARRAY *gem;

	gem = gem_control();
# endif
	gem->int_in[0] = button;
	gem->addr_in[0] = (long)string;

	return (long)call_aes(gem, 52);
}

/* EOF */

# include "extdef.h"

/* As of AES 1.40 */

void
wind_new(void)
{
# ifdef GEMMA_MULTIPROC
	GEM_ARRAY *gem;

	gem = gem_control();
# endif
	call_aes(gem, 109);
}

/* EOF */

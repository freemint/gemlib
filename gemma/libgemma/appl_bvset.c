# include "extdef.h"

long
appl_bvset(short bvdisk, short bvhard)
{
# ifdef GEMMA_MULTIPROC
	GEM_ARRAY *gem;

	gem = gem_control();
# endif
	gem->int_in[0] = bvdisk;
	gem->int_in[1] = bvhard;

	return call_aes(gem, 16);
}

/* EOF */

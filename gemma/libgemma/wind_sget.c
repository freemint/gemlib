# include "extdef.h"

long
wind_sget(short handle, short field, char *buff)
{
# ifdef GEMMA_MULTIPROC
	GEM_ARRAY *gem;

	gem = gem_control();
# endif
	gem->control[1] = 4;
	gem->control[2] = 1;
	gem->control[3] = 0;
	gem->control[4] = 0;

	gem->int_in[0] = handle;
	gem->int_in[1] = field;
	gem->int_in[2] = (unsigned long)buff >> 16;
	gem->int_in[3] = (unsigned long)buff & 0xffff;

	return call_aes(gem, 104+512);
}

/* EOF */

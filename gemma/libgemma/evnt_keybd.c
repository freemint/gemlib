# include "extdef.h"

long
evnt_keybd(void)
{
	GEM_ARRAY *gem;

	gem = gem_control();

	return call_aes(gem, 20);
}

/* EOF */
# ifdef FAST_YIELD
#  include <mintbind.h>
# else
#  include "extdef.h"
# endif


long
appl_yield(void)
{
# ifdef FAST_YIELD
	return Syield();
# else
	GEM_ARRAY *gem;

	gem = gem_control();

	return call_aes(gem, 17);
# endif
}

/* EOF */

# include "extdef.h"

/* PC GEM. Warning: the same opcode as menu_popup()! */

long
menu_unregister(short apid)
{
# ifdef GEMMA_MULTIPROC
	GEM_ARRAY *gem;

	gem = gem_control();
# endif
	gem->control[1] = 1;
	gem->control[2] = 1;
	gem->control[3] = 0;
	gem->control[4] = 0;

	gem->int_in[0] = apid;

	/* Adding 512 informs the library that the
	 * control[] array is already filled
	 */
	return call_aes(gem, 36+512);
}

/* EOF */

# include "extdef.h"

/* PC GEM. Warning: the same opcode as menu_attach()! */

long
menu_click(short click, short setit)
{
# ifdef GEMMA_MULTIPROC
	GEM_ARRAY *gem;

	gem = gem_control();
# endif
	gem->control[1] = 2;
	gem->control[2] = 1;
	gem->control[3] = 0;
	gem->control[4] = 0;

	gem->int_in[0] = click;
	gem->int_in[1] = setit;

	/* See menu_unregister() */
	return (long)call_aes(gem, 37+512);
}

/* EOF */

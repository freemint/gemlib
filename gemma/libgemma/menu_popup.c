# include "extdef.h"

long
menu_popup(MENU *menu, short xp, short yp, MENU *data)
{
	GEM_ARRAY *gem;

	gem = gem_control();
	gem->int_in[0] = xp;
	gem->int_in[1] = yp;
	gem->addr_in[0] = (long)menu;
	gem->addr_in[1] = (long)data;

	return (long)call_aes(gem, 36);
}

/* EOF */

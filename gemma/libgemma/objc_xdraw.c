# include "extdef.h"

long
objc_xdraw(WINDIAL *wd, short obj)
{
	GEM_ARRAY *gem;

	gem = gem_control();

	gem->addr_in[0] = (long)wd->wb_treeptr;
	gem->int_in[0] = obj;
	gem->int_in[1] = 7;
	gem->int_in[2] = wd->wb_work_x;
	gem->int_in[3] = wd->wb_work_y;
	gem->int_in[4] = wd->wb_work_w;
	gem->int_in[5] = wd->wb_work_h;

	return call_aes(gem, 42);
}

/* EOF */

#include "gem.h"


short
vq_page_name (short handle, short page_id, const char *page_name,
	      long *page_width, long *page_height)
{
	vdi_intin[0] = page_id;
	*((const char **) (&vdi_intin[1])) = page_name;
	vdi_control[0] = 5;
	vdi_control[1] = 0;
	vdi_control[3] = 3;
	vdi_control[5] = 38;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	*page_width = *((long *) (&vdi_intout[1]));
	*page_height = *((long *) (&vdi_intout[3]));
	return vdi_intout[0];
}

/*
 * * special graphic funkcion
 */

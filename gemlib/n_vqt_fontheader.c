
#include "gemx.h"


void
vqt_fontheader (int handle, char *buffer, char *pathname)
{
	*((char **) (&vdi_intin[0])) = buffer;
	vdi_control[0] = 232;
	vdi_control[1] = 0;
	vdi_control[3] = 2;
	vdi_control[5] = 0;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	vdi_array2str (vdi_intout, pathname, vdi_control[4]);
}

/*
 * * NOTE: requires NVDI version 3.x or higher
 */

int
vqt_name_and_id (int handle, int font_format, char *font_name, char *ret_name)
{
	short i;

	vdi_intin[0] = font_format;
	i = vdi_str2array (font_name, vdi_intin);
	vdi_control[0] = 230;
	vdi_control[1] = 0;
	vdi_control[3] = i;
	vdi_control[5] = 100;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	vdi_array2str (vdi_intin, ret_name, vdi_control[4]);
	return vdi_intout[0];
}

/*
 * * NOTE: requires NVDI version 3.x or higher
 */

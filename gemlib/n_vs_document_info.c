
#include "gemx.h"


short
vs_document_info (short vdi_handle, short type, char *s, short wchar)
{
	short cnt;

	vdi_intout[0] = 0;
	vdi_intin[0] = type;
	if (wchar)
	{
		/* 16bit strings not yet supported! */
		return 0;
	}
	else
		cnt = vdi_str2array (s, vdi_intin + 1);

	vdi_control[0] = 5;
	vdi_control[1] = 0;
	vdi_control[3] = 1 + cnt;
	vdi_control[5] = 2103;
	vdi_control[6] = vdi_handle;
	vdi (&vdi_params);
	return vdi_intout[0];
}

/*
 * * NOTE: requires NVDI version 5.x or higher
 */

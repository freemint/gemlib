
#include "gemx.h"


int
fnts_get_name (FNT_DIALOG * fnt_dialog, long id, char *full_name,
	       char *family_name, char *style_name)
{
	unsigned short *i;

	aes_intin[0] = 2;
	i = (unsigned short *) &id;
	aes_intin[1] = i[0];
	aes_intin[2] = i[1];
	aes_addrin[0] = (long) fnt_dialog;
	aes_addrin[1] = (long) full_name;
	aes_addrin[2] = (long) family_name;
	aes_addrin[3] = (long) style_name;
	aes_control[0] = 184;
	aes_control[1] = 3;
	aes_control[2] = 1;
	aes_control[3] = 4;
	aes_control[4] = 0;
	aes (&aes_params);
	return aes_intout[0];
}

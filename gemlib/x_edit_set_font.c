#include "gem_aesP.h"
#include "gemx.h"


void
edit_set_font (OBJECT *tree, short obj, short fontID, short fontH,
short fontPix, short mono)
{
	aes_intin[0] = obj;
	aes_intin[1] = 3;
	aes_intin[2] = fontID;
	aes_intin[3] = fontH;
	aes_intin[4] = mono;
	aes_intin[5] = fontPix;
	
	aes_addrin[0] = (long) tree;
	
	aes_control[0] = 217;
	aes_control[1] = 6;
	aes_control[2] = 0;
	aes_control[3] = 1;
	aes_control[4] = 0;
	
	aes (&aes_params);
}

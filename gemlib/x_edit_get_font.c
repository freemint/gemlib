
#include "gemx.h"


short
edit_get_font (OBJECT *tree, short obj, short *fontID, short *fontH,
short *fontPix, short *mono)
{
	aes_intin[0] = obj;
	aes_intin[1] = 3;
	
	aes_addrin[0] = (long) tree;
	
	aes_intout[4] = 0;
	
	aes_control[0] = 216;
	aes_control[1] = 2;
	aes_control[2] = 5;
	aes_control[3] = 1;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	*fontID = aes_intout[1];
	*fontH = aes_intout[2];
	*fontPix = aes_intout[4];
	*mono = aes_intout[3];
	return aes_intout[0];
}

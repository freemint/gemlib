#include "gemx.h"
#include "gem_aesP.h"


void
edit_set_dirty (OBJECT *tree, short obj, short dirty)
{
	aes_intin[0] = obj;
	aes_intin[1] = 7;
	aes_intin[2] = dirty;
	
	aes_addrin[0] = (long) tree;
	
	aes_control[0] = 217;
	aes_control[1] = 2;
	aes_control[2] = 0;
	aes_control[3] = 2;
	aes_control[4] = 0;
	
	aes (&aes_params);
}

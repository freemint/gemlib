/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** Draw object(tree)
 *
 *  @param tree as for mt_objc_draw()
 *  @param start  as for mt_objc_draw()
 *  @param depth  as for mt_objc_draw()
 *  @param clip NULL => whole window
 *  @param whandle window handle
 *  @param global_aes global AES array
 *
 *  @since MagiC 5.10
 *
 */

void 
mt_objc_wdraw(OBJECT *tree, short start, short depth, GRECT *clip, short whandle, short *global_aes)
{
	AES_PARAMS(60,3,0,2,0);

	aes_intin[0] = start;
	aes_intin[1] = depth;
	aes_intin[2] = whandle;

	aes_addrin[0] = (long)tree;
	aes_addrin[1] = (long)clip;

	AES_TRAP(aes_params);
}

#include "gem_aesP.h"
#include "mt_gemx.h"

/** 
 *
 *  @param tree see mt_objc_edit()
 *  @param obj  see mt_objc_edit()
 *  @param key  see mt_objc_edit()
 *  @param xpos  see mt_objc_edit()
 *  @param subfn see mt_objc_edit()
 *  @param r is the clipping area used when drawing
 *  @param global_aes global AES array
 *
 *  @return 
 *
 *  @since 
 *
 *
 *
 */

short 
mt_objc_xedit(OBJECT *tree, short obj, short key, short *xpos, short subfn,
              GRECT *r, short *global_aes)
{
	AES_PARAMS(46,4,2,2,0);

	aes_intin[0] = obj;
	aes_intin[1] = key;
	aes_intin[2] = *xpos;
	aes_intin[3] = subfn;

	aes_addrin[0] = (long)tree;
	aes_addrin[1] = (long)r;

	AES_TRAP(aes_params);

	*xpos = aes_intout[1];
	
	return aes_intout[0];
}

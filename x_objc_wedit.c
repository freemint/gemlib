#include "gem_aesP.h"
#include "mt_gemx.h"

/** Text field input for window dialogs
 *
 *  @param tree as for mt_objc_edit()
 *  @param obj  as for mt_objc_edit()
 *  @param key  as for mt_objc_edit()
 *  @param idx as for mt_objc_edit()
 *  @param kind  as for mt_objc_edit()
 *  @param whandle window handle
 *  @param global_aes global AES array
 *
 *  @return  as for mt_objc_edit()
 *
 *  @since MagiC 5.10
 *
 */

short 
mt_objc_wedit(OBJECT *tree, short obj, short key, short *idx, short kind,
              short whandle, short *global_aes)
{
	AES_PARAMS(65,5,2,1,0);

	aes_intin[0] = obj;
	aes_intin[1] = key;
	aes_intin[2] = *idx;
	aes_intin[3] = kind;
	aes_intin[4] = whandle;

	aes_addrin[0] = (long)tree;

	AES_TRAP(aes_params);

	*idx = aes_intout[1];
	
	return aes_intout[0];
}

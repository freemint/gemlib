/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** 
 *
 *  @param tree
 *  @param x
 *  @param y
 *  @param firstscrlob
 *  @param lastscrlob
 *  @param nlines
 *  @param init
 *  @param param
 *  @param lastscrlpos
 *  @param global_aes global AES array
 *
 *  @return 
 *
 *  @since MagiC 5.03
 *
 */

short
mt_xfrm_popup (OBJECT *tree, short x, short y, short firstscrlob, short lastscrlob, short nlines,
			   void __CDECL (*init)(struct POPUP_INIT_args),
			   void *param, short *lastscrlpos, short * global_aes)
{
	AES_PARAMS(135,6,2,3,0);
	
	aes_intin[0] = x;
	aes_intin[1] = y;
	aes_intin[2] = firstscrlob;
	aes_intin[3] = lastscrlob;
	aes_intin[4] = nlines;
	aes_intin[5] = *lastscrlpos;
	
	aes_addrin[0] = (long)tree;
	aes_addrin[1] = (long)init;
	aes_addrin[2] = (long)param;
	
	aes_intout[1] = *lastscrlpos;
	
	AES_TRAP(aes_params);
	
	*lastscrlpos = aes_intout[1];

	return aes_intout[0];
}

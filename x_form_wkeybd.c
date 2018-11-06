#include "gem_aesP.h"
#include "mt_gemx.h"

/** 
 *
 *  @param fo_ktree as for mt_form_keybd()
 *  @param fo_kobject as for mt_form_keybd()
 *  @param fo_kobnext as for mt_form_keybd()
 *  @param fo_kchar as for mt_form_keybd()
 *  @param fo_knxtobject as for mt_form_keybd() \n
 *             [option CHECK_NULLPTR] fo_knxtobject may be NULL
 *  @param fo_knxtchar as for mt_form_keybd() \n
 *             [option CHECK_NULLPTR] fo_knxtchar may be NULL
 *  @param whandle window handle
 *  @param global_aes global AES array
 *
 *  @return  as for mt_form_keybd()
 *
 *  @since MagiC 5.10
 *
 *
 *
 */

short 
mt_form_wkeybd( OBJECT *fo_ktree, short fo_kobject, short fo_kobnext, short fo_kchar, 
			    short *fo_knxtobject, short *fo_knxtchar, short whandle, short *global_aes)
{
	AES_PARAMS(64,4,3,1,0);
                    
	aes_intin[0] = fo_kobject;
	aes_intin[1] = fo_kchar;
	aes_intin[2] = fo_kobnext;
	aes_intin[3] = whandle;
	
	aes_addrin[0] =(long)fo_ktree;

	AES_TRAP(aes_params);

#if CHECK_NULLPTR
	if (fo_knxtobject)
#endif
	*fo_knxtobject = aes_intout[1];
#if CHECK_NULLPTR
	if (fo_knxtchar)
#endif
	*fo_knxtchar   = aes_intout[2];
	
	return aes_intout[0];
}

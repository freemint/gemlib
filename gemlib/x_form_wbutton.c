/*
 *  $Id$
 */

#include "gemx.h"
#include "gem_aesP.h"

/** Service button event for window dialogs
 *
 *  @param fo_btree as for mt_form_button()
 *  @param fo_bobject as for mt_form_button()
 *  @param fo_bclicks as for mt_form_button()
 *  @param fo_bnxtobj as for mt_form_button()
 *  @param whandle window handle
 *  @param global_aes global AES array
 *
 *  @return as for mt_form_button()
 *
 *  @since MagiC 5.10
 *
 */

short 
mt_form_wbutton(OBJECT *fo_btree, short fo_bobject, short fo_bclicks, short *fo_bnxtobj,
                short whandle, short *global_aes)
{
	AES_PARAMS(63,3,2,1,0);
                    
	aes_intin[0] = fo_bobject;
	aes_intin[1] = fo_bclicks;
	aes_intin[2] = whandle;
	
	aes_addrin[0] = (long)fo_btree;

	AES_TRAP(aes_params);

	*fo_bnxtobj = aes_intout[1];
	
	return aes_intout[0];
}

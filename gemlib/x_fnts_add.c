/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** add user fonts
 *
 *  @param fnt_dialog Pointer to management structure
 *  @param user_fonts Pointer to user fonts
 *  @param global_aes global AES array
 *
 *  @return 0: Error   1: All OK
 *
 *  @since mt_appl_getinfo(7) give informations on mt_fnts_xx() functions availability
 *
 *  With ADD USER FONTS a program can add its own user fonts to those
 *  displayed by the font selector. The IDs of these fonts must be higher 
 *  than 65535. In addition the pointer to a display function must be 
 *  entered into the structure element FNTS_ITEM::display.
 */

short 
mt_fnts_add(FNT_DIALOG *fnt_dialog, FNTS_ITEM *user_fonts, short *global_aes)
{
	AES_PARAMS(185,1,1,2,0);
                    
	aes_intin[0] = 0;
	
	aes_addrin[0] = (long)fnt_dialog;
	aes_addrin[1] = (long)user_fonts;

	AES_TRAP(aes_params);
	
	return aes_intout[0];
}

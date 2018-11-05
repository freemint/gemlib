/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** returns the full name, the family name and the style for the font given in parameter
 *
 *  @param fnt_dialog Pointer to management structure
 *  @param id specifies the Font ID
 *  @param full_name Pointer to the full name or 0L
 *  @param family_name Pointer to the family name or 0L
 *  @param style_name Pointer to den style name or 0L
 *  @param global_aes global AES array
 *
 *  @return 0 (Error) or 1 (All OK)
 *
 *  @since mt_appl_getinfo(7) give informations on mt_fnts_xx() functions availability
 *
 */

short 
mt_fnts_get_name(FNT_DIALOG *fnt_dialog, long id, char *full_name, char *family_name,
                 char *style_name, short *global_aes)
{
	AES_PARAMS(184,3,1,4,0);
                    
	aes_intin[0] = 2;
	aes_intin_long(1) = id;
	aes_addrin[0] = (long)fnt_dialog;
	aes_addrin[1] = (long)full_name;
	aes_addrin[2] = (long)family_name;
	aes_addrin[3] = (long)style_name;
	aes_intout[0] = 0;

	AES_TRAP(aes_params);

	return aes_intout[0];
}

/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** font selector - get style id
 *
 *  @param fnt_dialog Pointer to management structure
 *  @param id ID of a font of the family
 *  @param index Index within the family. \p index must be a number 
 *         between 1 and the result of mt_fnts_get_no_styles().
 *  @param global_aes global AES array
 *
 *  @return ID of the \p index -th font of the family
 *
 *  @since mt_appl_getinfo(7) give informations on mt_fnts_xx() functions availability
 */

long 
mt_fnts_get_style(FNT_DIALOG *fnt_dialog, long id, short index, short *global_aes)
{
	AES_PARAMS(184,4,2,1,0);
                    
	aes_intin[0] = 1;
	aes_intin_long(1) = id;
	aes_intin[3] = index;
	aes_addrin[0] = (long)fnt_dialog;
	aes_intout_long(0) = 0;

	AES_TRAP(aes_params);

	return aes_intout_long(0);
}

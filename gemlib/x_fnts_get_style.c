/*
 *  $Id$
 */

#include "gemx.h"
#include "gem_aesP.h"

/** font selector - get style id
 *
 *  @param fnt_dialog Pointer to management structure
 *  @param id ID of a font of the family
 *  @param index Index within the family. \p index must be a number 
 *         between 1 and the result of mt_fnts_get_no_styles().
 *  @param global_aes global AES array
 *
 *  @return ID of the <index>-th font of the family
 *
 *  @since mt_appl_getinfo(7) give informations on mt_fnts_xx() functions availability
 */

long 
mt_fnts_get_style(FNT_DIALOG *fnt_dialog, long id, short index, short *global_aes)
{
	unsigned short *i;
	
	AES_PARAMS(184,4,2,1,0);
                    
	aes_intin[0] = 1;
	i = (unsigned short *)&id;
	aes_intin[1] = i[0];
	aes_intin[2] = i[1];
	aes_intin[3] = index;
	aes_addrin[0] = (long)fnt_dialog;

	AES_TRAP(aes_params);

	i = (unsigned short *)&aes_intout[0];
	
	return *(long *)i;
}

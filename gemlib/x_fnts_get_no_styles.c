/*
 *  $Id$
 */

#include "gemx.h"
#include "gem_aesP.h"

/** returns the number of fonts that belong to the same 
 *  family as the font given as parameter.
 *
 *  @param fnt_dialog Pointer to management structure
 *  @param id ID of a font of the family, that may have been returned 
 *          by mt_fnts_evnt() for instance.
 *  @param global_aes global AES array
 *
 *  @return Number of styles belonging to the family.
 *
 *  @since mt_appl_getinfo(7) give informations on mt_fnts_xx() functions availability
 *
 */

short 
mt_fnts_get_no_styles(FNT_DIALOG *fnt_dialog, long id, short *global_aes)
{
	unsigned short *i;
	
	AES_PARAMS(184,3,1,1,0);
                    
	aes_intin[0] = 0;
	i = (unsigned short *)&id;
	aes_intin[1] = i[0];
	aes_intin[2] = i[1];
	aes_addrin[0] = (long)fnt_dialog;

	AES_TRAP(aes_params);

	return aes_intout[0];
}

/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** get font info
 *
 *  @param fnt_dialog Pointer to management structure
 *  @param id specifies the Font ID
 *  @param mono will contain the Flag for mono-spaced font
 *  @param outline will contain the Flag for vector font
 *  @param global_aes global AES array
 *
 *  @return 0 (Error) or >0 (Index for vqt_name())
 *
 *  @since mt_appl_getinfo(7) give informations on mt_fnts_xx() functions availability
 *
 */

short 
mt_fnts_get_info(FNT_DIALOG *fnt_dialog, long id, short *mono, short *outline, short *global_aes)
{
	unsigned short *i;
	
	AES_PARAMS(184,3,3,1,0);
                    
	aes_intin[0]  = 3;
	i = (unsigned short *)&id;
	aes_intin[1]  = i[0];
	aes_intin[2]  = i[1];
	aes_addrin[0] = (long)fnt_dialog;

	AES_TRAP(aes_params);

	*mono    = aes_intout[1];
	*outline = aes_intout[2];
	
	return aes_intout[0];
}

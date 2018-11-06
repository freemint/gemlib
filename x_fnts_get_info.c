#include "gem_aesP.h"
#include "mt_gemx.h"

/** get font info
 *
 *  @param fnt_dialog Pointer to management structure
 *  @param id specifies the Font ID
 *  @param mono will contain the Flag for mono-spaced font \n
 *             [option CHECK_NULLPTR] mono may be NULL
 *  @param outline will contain the Flag for vector font \n
 *             [option CHECK_NULLPTR] outline may be NULL
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
	AES_PARAMS(184,3,3,1,0);
                    
	aes_intin[0]  = 3;
	aes_intin_long(1) = id;
	aes_addrin[0] = (long)fnt_dialog;
	aes_intout[0] = 0;

	AES_TRAP(aes_params);

#if CHECK_NULLPTR
	if (mono)
#endif
	*mono    = aes_intout[1];
#if CHECK_NULLPTR
	if (outline)
#endif
	*outline = aes_intout[2];
	
	return aes_intout[0];
}

#include "gem_aesP.h"
#include "mt_gemx.h"

/** form xdialog space
 *
 *  @param fo_diflag specifies the action to take and the meaning of
 *               other parameters, as specified in mt_form_dial()
 *               documentation. This function performs some additionnal
 *               actions (compared to mt_form_dial()) when called with
 *               the following values (this is
 *               related to the extra \a flydial parameter) :
 *         - #FMD_START memory is reserved to save the background covered by the dialog
 *         - #FMD_FINISH restore the screen background and free the memory 
 *           previously reserved
 *  @param fo_dilittlx 
 *  @param fo_dilittly 
 *  @param fo_dilittlw 
 *  @param fo_dilittlh position and dimension of the little rectangle
 *  @param fo_dibigx 
 *  @param fo_dibigy 
 *  @param fo_dibigw 
 *  @param fo_dibigh position and dimension of the big rectangle
 *  @param flydial 0 if you don't want to use the flydial feature, or a pointer
 *           to a (void*) variable. See below.
 *  @param global_aes global AES array
 *
 *  @return non-zero if succeeded.
 *
 *  @since The presence of the flydial support can be checked by calling mt_appl_getinfo()
 *         with parameter #AES_FORM.
 *
 *  If \a flydial is not equal to 0, it is tested whether sufficiant memory is available
 *  in order to save the background of the dialog box. A pointer on the saved data (screen
 *  memory under the dialog) is then saved in \a flydial.
 *
 */

short 
mt_form_xdial(short fo_diflag, short fo_dilittlx, short fo_dilittly, short fo_dilittlw, 
			  short fo_dilittlh, short fo_dibigx, short fo_dibigy, short fo_dibigw,
			  short fo_dibigh, void **flydial, short *global_aes)
{
	AES_PARAMS(51,9,1,2,0);
                    
	aes_intin[0] = fo_diflag;
	aes_intin[1] = fo_dilittlx;
	aes_intin[2] = fo_dilittly;
	aes_intin[3] = fo_dilittlw;
	aes_intin[4] = fo_dilittlh;
	aes_intin[5] = fo_dibigx;
	aes_intin[6] = fo_dibigy;
	aes_intin[7] = fo_dibigw;
	aes_intin[8] = fo_dibigh;

	aes_addrin[0] = (long)flydial;
	aes_addrin[1] = 0;

	AES_TRAP(aes_params);

	return aes_intout[0];
}

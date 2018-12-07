#include "gem_aesP.h"
#include "mt_gemx.h"

/** 
 *
 *  @param fo_diflag see mt_form_xdial()
 *  @param fo_dilittl  see mt_form_xdial()
 *  @param fo_dibig  see mt_form_xdial()
 *  @param flydial  see mt_form_xdial()
 *  @param global_aes global AES array
 *
 *  @return  see mt_form_xdial()
 *
 *  @since  see mt_form_xdial()
 *
 *
 *
 */

short 
mt_form_xdial_grect(short fo_diflag, const GRECT *fo_dilittl, const GRECT *fo_dibig, void **flydial, short *global_aes)
{
	AES_PARAMS(51,9,1,1,0);
                    
	aes_intin[0] = fo_diflag;
	if (fo_dilittl)
	{
		aes_intin[1] = fo_dilittl->g_x;
		aes_intin[2] = fo_dilittl->g_y;
		aes_intin[3] = fo_dilittl->g_w;
		aes_intin[4] = fo_dilittl->g_h;
	} else
	{
		aes_intin[1] = 0;
		aes_intin[2] = 0;
		aes_intin[3] = 0;
		aes_intin[4] = 0;
	}
	aes_intin[5] = fo_dibig->g_x;
	aes_intin[6] = fo_dibig->g_y;
	aes_intin[7] = fo_dibig->g_w;
	aes_intin[8] = fo_dibig->g_h;

	aes_addrin[0] = (long)flydial;

	AES_TRAP(aes_params);

	return aes_intout[0];
}

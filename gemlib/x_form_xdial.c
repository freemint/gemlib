/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** 
 *
 *  @param fo_diflag 
 *  @param fo_dilittlx 
 *  @param fo_dilittly 
 *  @param fo_dilittlw 
 *  @param fo_dilittlh 
 *  @param fo_dibigx 
 *  @param fo_dibigy 
 *  @param fo_dibigw 
 *  @param fo_dibigh 
 *  @param flydial 
 *  @param global_aes global AES array
 *
 *  @return 
 *
 *  @since 
 *
 *
 *
 */

short 
mt_form_xdial(short fo_diflag, short fo_dilittlx, short fo_dilittly, short fo_dilittlw, 
			  short fo_dilittlh, short fo_dibigx, short fo_dibigy, short fo_dibigw,
			  short fo_dibigh, void **flydial, short *global_aes)
{
	AES_PARAMS(51,9,1,1,0);
                    
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

	AES_TRAP(aes_params);

	return aes_intout[0];
}

/*
 *  $Id$
 */
 
#include "gem_aesP.h"

/** returns size information for a specific window.
 *
 *  @param Type specifies the mode of this call.
 *  @param Parts is a bit mask of window 'widgets' present with the
 *         window. For a detailed listing of these elements see
 *         mt_wind_create().
 *  @param In the input area
 *  @param Out the output area
 *  @param global_aes global AES array
 *
 *  see mt_wind_calc() documentation for more details
 */

short 
mt_wind_calc_grect(short Type, short Parts, const GRECT *In, GRECT *Out, short *global_aes)
{
	AES_PARAMS(108,6,5,0,0);
                    
	aes_intin[0]		    = Type;
	aes_intin[1]		    = Parts;
	*(GRECT*)(aes_intin +2) = *In;

	AES_TRAP(aes_params);

	*Out = *(GRECT*)(aes_intout +1);
	
	return aes_intout[0];
}

/*
 *  $Id$
 */

#include "gem_aesP.h"

/** 
 *
 *  @param click specifies if the AES shall manage menu as
 *         - 0 : Drop down menu
 *         - 1 : PullDown
 *  @param setit is one of the following value:
 *         - 0	=	Menu prompting query
 *         - 1	=	Menu prompting set	
 *  @param global_aes global AES array
 *
 *  @return adjusted menu prompting (0 = drop down, 1 = Pulldown)
 *
 *  @since PC/GEM3, mt_appl_getinfo() with parameter #AES_PCGEM gives the
 *         availability of this function.
 *
 *  @sa 
 *
 */

short
mt_menu_click(short click, short setit, short *global_aes)
{
	AES_PARAMS(37,2,1,0,0);
                    
	aes_intin[0] = click;
	aes_intin[1] = setit;

	AES_TRAP(aes_params);

	return aes_intout[0];
} 

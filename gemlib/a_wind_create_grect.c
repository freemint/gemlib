/*
 *  $Id$
 */

#include "gem_aesP.h"

/** initializes a new window structure and allocates any necessary memory.
 *
 *  @param Parts is a bit array whose elements determine the presence of
 *         any 'widgets' on the window.
 *  @param r specify the maximum extents of the window.
 *  @param global_aes global AES array
 *
 *  see mt_wind_create() documentation for more details
 */

short 
mt_wind_create_grect(short Parts, const GRECT *r, short *global_aes)
{
	AES_PARAMS(100,5,1,0,0);
                    
	aes_intin[0] = Parts;
	*(GRECT*)(aes_intin +1) = *r;

	AES_TRAP(aes_params);

	return aes_intout[0];
}

#ifdef wind_create_grect
#undef wind_create_grect
#endif
short 
wind_create_grect(short Parts, const GRECT *r)
{
	return(mt_wind_create_grect( Parts, r, aes_global));
}


/*
 *  $Id$
 */

#include <string.h>
#include "gem_aesP.h"

/** Application Initialisation
 *
 *  @return add return description here
 *
 *  add detailled description here.  
 */

short 
mt_appl_init(short *global_aes)
{
#ifndef __MINT__
	int ff;
	short *pts;
	long *ptl;
#endif		
   	static short 	aes_control[AES_CTRLMAX]={10,0,1,0,0};
	short			aes_intin[AES_INTINMAX],
					aes_intout[AES_INTOUTMAX];
	long			aes_addrin[AES_ADDRINMAX],
					aes_addrout[AES_ADDROUTMAX];

	AESPB aes_params;
  	aes_params.control = &aes_control[0];   /* AES Control Array             */
  	aes_params.global  = &global_aes[0];    /* AES Global Array              */
  	aes_params.intin   = &aes_intin[0];     /* input integer array           */
  	aes_params.intout  = &aes_intout[0];    /* output integer array          */
  	aes_params.addrin  = &aes_addrin[0];    /* input address array           */
  	aes_params.addrout = &aes_addrout[0];   /* output address array          */
                    
	/* clear all binding arrays */
#ifdef __MINT__  /* mintlib have bzero() */
	bzero (&aes_control[0], AES_CTRLMAX * sizeof (short));
	bzero (&aes_intin[0], AES_INTINMAX * sizeof (short));
	bzero (&aes_intout[0], AES_INTOUTMAX * sizeof (short));
	bzero (&aes_addrin[0], AES_ADDRINMAX * sizeof (short));
	bzero (&aes_addrout[0], AES_ADDROUTMAX * sizeof (short));
	bzero (&aes_global[0], AES_GLOBMAX * sizeof (short));
#else
	for(ff=0,pts=&aes_intin[0];ff<AES_INTINMAX;ff++) *(pts++)=0;
	for(ff=0,pts=&aes_intout[0];ff<AES_INTOUTMAX;ff++) *(pts++)=0;
	for(ff=0,ptl=&aes_addrin[0];ff<AES_ADDRINMAX;ff++) *(ptl++)=0L;
	for(ff=0,ptl=&aes_addrout[0];ff<AES_ADDROUTMAX;ff++) *(ptl++)=0L;
	for(ff=0,pts=&global_aes[0];ff<AES_GLOBMAX;ff++) *(pts++)=0;
#endif

	AES_TRAP(aes_params);

	gl_ap_version = aes_global[0];
	gl_apid = aes_intout[0];
	
	return aes_intout[0];
}

#ifdef appl_init
#undef appl_init
#endif
short 
appl_init(void)
{
	return(mt_appl_init(aes_global));
}


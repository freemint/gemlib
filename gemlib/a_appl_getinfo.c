/*
 *  $Id$
 */
 
#include "gem_aesP.h"

/** Application Get Info
 *
 *  @param type add parameter description here
 *  @param out1 add parameter description here
 *  @param out2 add parameter description here
 *  @param out3 add parameter description here
 *  @param out4 add parameter description here
 *  @param global_aes global AES array
 *  @return add return description here
 *
 *  add detailled description here.  
 *
 *  is appl_getinfo() is not implemented (gl_ap_version < 0X0401 and the
 *  application "?AGI\0\0\0\0" (Winx) is not found), the trap is not performed
 *  (may crash on some system)
 */

short 
mt_appl_getinfo (short type, short *out1, short *out2, short *out3, short *out4, short *global_aes)
{
	static short aes_control[AES_CTRLMAX]={130,1,5,0,0};
	short aes_intin[AES_INTINMAX], aes_intout[AES_INTOUTMAX];
	long aes_addrin[AES_ADDRINMAX], aes_addrout[AES_ADDROUTMAX];

	AESPB aes_params;

	static int first = 1;
	static int is_appl_getinfo_avaible = 0;		/* if 1 appl_getinfo() avaible search in appl_init() */

	if (first)
	{
		if (gl_ap_version >= 0x0401)
			is_appl_getinfo_avaible = 1;
		else
		{
			if (mt_appl_find ("?AGI\0\0\0\0", global_aes) != -1)
				is_appl_getinfo_avaible = 1;
			else
				is_appl_getinfo_avaible = 0;
		}
		first = 0;
	}

	if (is_appl_getinfo_avaible == 0)
		return (1);								/* appl_getinfo() not implemented */

	aes_params.control = &aes_control[0];   /* AES Control Array             */
	aes_params.global  = &global_aes[0];    /* AES Global Array              */
	aes_params.intin   = &aes_intin[0];     /* input integer array           */
	aes_params.intout  = &aes_intout[0];    /* output integer array          */
	aes_params.addrin  = &aes_addrin[0];    /* input address array           */
	aes_params.addrout = &aes_addrout[0];   /* output address array          */

	aes_intin[0] = type;

	AES_TRAP(aes_params);

	*out1 = aes_intout[1];
	*out2 = aes_intout[2];
	*out3 = aes_intout[3];
	*out4 = aes_intout[4];

	return (aes_intout[0]);
}

#ifdef appl_getinfo
#undef appl_getinfo
#endif
short 
appl_getinfo(short type, short *out1, short *out2, short *out3, short *out4)
{
	return(mt_appl_getinfo(type,out1, out2, out3, out4, aes_global));
}


#include "gem_aesP.h"

/** returns various information about a window.
 *
 *  @param WindowHandle specifies the handle of the window to return
 *         information about (0 is the desktop window)
 *  @param What specifies the attribute to return 
 *  @param W1
 *  @param global_aes global AES array
 *
 *  see mt_wind_get() documentation for more details.
 */

short 
mt_wind_get_int (short WindowHandle, short What, short *W1, short *global_aes)
{
	short *ptr;
	short aes_control[AES_CTRLMAX],
	      aes_intin[AES_INTINMAX],
		  aes_intout[AES_INTOUTMAX];
	long  aes_addrin[AES_ADDRINMAX], 
	      aes_addrout[AES_ADDROUTMAX];
	AESPB aes_params;

	aes_params.control = &aes_control[0];				/* AES Control Array */
	aes_params.global  = &global_aes[0];				/* AES Global Array */
	aes_params.intin   = &aes_intin[0];				/* input integer array */
	aes_params.intout  = &aes_intout[0];				/* output integer array */
	aes_params.addrin  = &aes_addrin[0];				/* input address array */
	aes_params.addrout = &aes_addrout[0];				/* output address array */

	aes_intin[0] = WindowHandle;
	aes_intin[1] = What;

	ptr = aes_control;
	*(ptr ++) = 104;									/* aes_control[0] */

	switch (What) {
		case WF_DCOLOR:
		case WF_COLOR:
			aes_intin[2] = *W1;
			*(ptr ++) = 3;								/* aes_control[1] */
			break;
		default:
			*(ptr ++) = 2;								/* aes_control[1] */
	}

	*(ptr ++) = 5;										/* aes_control[2] */
	*(ptr ++) = 0;										/* aes_control[3] */
	*(ptr ++) = 0;				 						/* aes_control[4] */

	/* ol: this line is required for WF_FIRSTXYWH and WF_NEXTXYWH because
	   lot of programmers doesn't verify the return value and espect W or H
	   will be 0 it's not true for NAES */
	aes_intout[3] = aes_intout[4] = 0;

	AES_TRAP(aes_params);
	
	if (What == WF_INFO || What == WF_NAME) {
		/* special case where W1 shall not be overwritten */
	} else {
#if CHECK_NULLPTR
		if (W1)	*W1 = aes_intout[1];
#else
		ptr = &aes_intout[1];
		*W1 = *ptr;									/* aes_intout[1] */
#endif
	}

	return (aes_intout[0]);
}

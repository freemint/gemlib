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
 *  @param InX  X-position of the input area
 *  @param InY  Y-position of the input area
 *  @param InW  Width of the input area
 *  @param InH  Height of the input area
 *  @param OutX X-position of the output area \n
 *         [option CHECK_NULLPTR] \a OutX may be NULL
 *  @param OutY Y-position of the output area \n
 *         [option CHECK_NULLPTR] \a OutY may be NULL
 *  @param OutW Width of the output area \n
 *         [option CHECK_NULLPTR] \a OutW may be NULL
 *  @param OutH Height of the output area \n
 *         [option CHECK_NULLPTR] \a OutH may be NULL
 *  @param global_aes global AES array
 *
 *  @return 0 if an error occurred or non-zero otherwise.
 *
 *  @since All AES versions.
 *
 *  @sa mt_wind_create()
 *
 *  If \a Type is #WC_BORDER (0), \a InX, \a InY, \a InW, and \a InH specify
 *  the work area of a window of type \a Parts. The call then fills
 *  in the WORDs pointed to by \a OutX, \a OutY, \a OutW, and \a OutH with the full
 *  extent of the window.
 *
 *  If \a Type is #WC_WORK (1), \a InX, \a InY, \a InW, and \a  InH specify the
 *  full extent of a window of type \a Parts. The call fills in the
 *  WORDs pointed to by \a OutX, \a OutY, \a OutW, and \a OutH with the work area
 *  of the window.
 *
 *  mt_wind_calc() is unable to calculate correct values when
 *  a toolbar is attached to a window. This can be corrected,
 *  though, by adjusting the values output by this function
 *  with the height of the toolbar.
 *
 */

short 
mt_wind_calc (short Type, short Parts, short InX,  short InY, short InW, short InH,
              short *OutX, short *OutY, short *OutW, short *OutH, short *global_aes)
{
	short *ptr;

	AES_PARAMS(108,6,5,0,0);
                    
	ptr = aes_intin;
	*(ptr ++) = Type;						   /* aes_intin[0] */
	*(ptr ++) = Parts;						   /* aes_intin[1] */
	*(ptr ++) = InX;						   /* aes_intin[2] */
	*(ptr ++) = InY;						   /* aes_intin[3] */
	*(ptr ++) = InW;						   /* aes_intin[4] */
	*(ptr)    = InH;						   /* aes_intin[5] */
	
	AES_TRAP(aes_params);

#if CHECK_NULLPTR
	if (OutX)	*OutX = aes_intout[1];
	if (OutY)	*OutY = aes_intout[2];
	if (OutW)	*OutW = aes_intout[3];
	if (OutH)	*OutH = aes_intout[4];
#else
	ptr = &aes_intout[1];
	*OutX = *(ptr ++);						   /* aes_intout[1] */
	*OutY = *(ptr ++);						   /* aes_intout[2] */
	*OutW = *(ptr ++);						   /* aes_intout[3] */
	*OutH = *(ptr);							   /* aes_intout[4] */
#endif

	return (aes_intout[0]);
}

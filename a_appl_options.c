#include "gem_aesP.h"

/**  let application set/get options available to it, such as the extended objc_edit mode.
 *
 *  @param mode select the mode. If mode is AOPT_CLEAR (0), then the selected
 *         options found in aopts0-aopts3 are cleared, disabling them. If
 *         AOPT_SET (1), then the selected option bit is set, enabling them.
 *  @param aopts0 The first group of 16 options which have the following meaning:
 *         - #AO0_WF_SLIDE     (0x01)
 *         - #AO0_OBJC_EDIT    (0x02)
 *  @param aopts1 The second group of 16 options, none of which is defined yet.
 *         Always reads 0.
 *  @param aopts2 The second group of 16 options, none of which is defined yet.
 *         Always reads 0.
 *  @param aopts3 The second group of 16 options, none of which is defined yet.
 *         Always reads 0.
 *  @param out1 1st return value. Adjusted option bit (0 = disabled, 1 = enabled)
 *         of the first group of 16 options
 *         [option CHECK_NULLPTR] out1 may be NULL
 *  @param out2 2nd return value. Adjusted option bit (0 = disabled, 1 = enabled)
 *         of the second group of 16 options. Currently always 0.
 *         [option CHECK_NULLPTR] out2 may be NULL
 *  @param out3 3rd return value. Always 0. \n
 *         [option CHECK_NULLPTR] out3 may be NULL
 *  @param out4 4th return value. Always 0. \n
 *         [option CHECK_NULLPTR] out4 may be NULL
 *  @param global_aes global AES array
 *
 *  @return 0 if an error occurred or non-zero otherwise.
 *
 *  @since The presence of this function can be determined by mt_appl_getinfo() (Opcode 98).
 *
 */

short
mt_appl_options (short mode, short aopts0, short aopts1, short aopts2, short aopts3, short *out1, short *out2, short *out3, short *out4, short *global_aes)
{
	short *ptr;

	AES_PARAMS(137,5,5,0,0);

	ptr = aes_intin;
	*(ptr ++) = mode;				 /* aes_intin[0] */
	*(ptr ++) = aopts0; 			 /* aes_intin[1] */
	*(ptr ++) = aopts1; 			 /* aes_intin[2] */
	*(ptr ++) = aopts2; 			 /* aes_intin[3] */
	*(ptr ++) = aopts3; 			 /* aes_intin[4] */

	AES_TRAP(aes_params);

#if CHECK_NULLPTR
	if (out1)
#endif
	*out1 = aes_intout[1];
#if CHECK_NULLPTR
	if (out2)
#endif
	*out2 = aes_intout[2];
#if CHECK_NULLPTR
	if (out3)
#endif
	*out3 = aes_intout[3];
#if CHECK_NULLPTR
	if (out4)
#endif
	*out4 = aes_intout[4];

	return (aes_intout[0]);
}

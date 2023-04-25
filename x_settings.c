#include "gem_aesP.h"
#include "mt_gemx.h"

/** Get or alter a window's OBJECT tree and gadget control flags.
 *
 *  @param getset
 *  @param length
 *  @param user
 *  @param global_aes global AES array
 *
 *  @return 0 if an error has occurred or a value>0 otherwise.
 *
 *  @since Geneva
 *
 */

short
mt_x_settings(short getset, short length, SETTINGS *user, short *global_aes)
{
	AES_PARAMS(0x7180,2,1,1,0);

	aes_intin[0] = getset;
	aes_intin[1] = length;
	aes_addrin[0] = (long)user;

	AES_TRAP(aes_params);

	return aes_intout[0];
}

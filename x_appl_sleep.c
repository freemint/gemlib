#include "gem_aesP.h"
#include "mt_gemx.h"

/** Put an application "to sleep", so that it will not receive any events.
 *
 *  @param id Application ID of the app to affect
 *  @param sleep the type of control
 *  @param global_aes global AES array
 *
 *  @return -1 if an error has occurred or a value>0 otherwise.
 *
 *  @since Geneva
 *
 */

short
mt_x_appl_sleep(short id, short sleep, short *global_aes)
{
	AES_PARAMS(0x7102,2,1,0,0);

	aes_intin[0] = id;
	aes_intin[1] = sleep;

	AES_TRAP(aes_params);

	return (aes_intout[0]);
}

#include "gem_aesP.h"
#include "mt_gemx.h"

/** Inform the Help display program of a request for help text.
 *
 *  @param sensitive
 *  @param topic
 *  @param helpfile
 *  @param global_aes global AES array
 *
 *  @return An error code (0) is returned if either the help program could not be loaded, or there was insufficient free memory to send the message. 
 *
 *  @since Geneva
 *
 */

short
mt_x_help(const char *topic, const char *helpfile, short sensitive, short *global_aes)
{
	AES_PARAMS(0x7185,1,1,2,0);

	aes_intin[0] = sensitive;
	aes_addrin[0] = (long)topic;
	aes_addrin[1] = (long)helpfile;

	AES_TRAP(aes_params);

	return aes_intout[0];
}

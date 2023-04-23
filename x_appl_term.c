#include "gem_aesP.h"
#include "mt_gemx.h"

/** Terminate an application and remove it from memory.
 *
 *  @param apid Application ID of program to terminate
 *  @param retrn Return value to be received by parent
 *  @param set_me Must always be non-zero 
 *  @param global_aes global AES array
 *
 *  @return 0: The application was not found
 *
 *  @since Geneva
 *
 */

short
mt_x_appl_term(short apid, short retrn, short set_me, short *global_aes)
{
	AES_PARAMS(0x7103,3,1,0,0);

	aes_intin[0] = apid;
	aes_intin[1] = retrn;
	aes_intin[2] = set_me;

	AES_TRAP(aes_params);

	return (aes_intout[0]);
}

/*
 *  $Id$
 */

#include "gem_aesP.h"

/** is used to determine the current application's
 *  parent and the command tail used to call it.
 *
 *  @param Command points to a buffer which upon exit will be filled in
 *         with the complete file specification of the application
 *         which launched the current process.
 *  @param Tail will likewise be filled in with the initial command
 *         line. The first BYTE of the command line indicates the
 *         length of the string which actually begins at &Tail[1].
 *  @param global_aes global AES array
 *
 *  @return 0 if an error occurred or non-zero otherwise.
 *
 *  @since All AES versions.
 *
 */
 
short 
mt_shel_read(char *Command, char *Tail, short *global_aes)
{
	AES_PARAMS(120,0,1,2,0);
                    
	aes_addrin[0] = (long)Command;
	aes_addrin[1] = (long)Tail;

	AES_TRAP(aes_params);
	
	return aes_intout[0];
}

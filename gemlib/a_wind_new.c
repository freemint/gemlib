/*
 *  $Id$
 */
 
#include "gem_aesP.h"

/** closes and deletes all of the application's
 *  windows. In addition, the state of mt_wind_update(), and the
 *  mouse pointer hide count is reset.
 *
 *  @param global_aes global AES array
 *
 *  @return The return value is reserved and currently unused
 *
 *  @since Available as of AES version 0x0140.
 *
 *  @sa mt_wind_delete(), mt_graf_mouse(), mt_wind_update()
 *
 *  This function should not be relied upon to clean up after
 *  an application. It was designed for parent processes that
 *  wish to ensure that a poorly written child process has
 *  properly cleaned up after itself.
 *
 */

short 
mt_wind_new (short *global_aes)
{
	AES_PARAMS(109,0,0,0,0);

	AES_TRAP(aes_params);

	return (1);
}	

/*
 *  $Id$
 */

#include "gem_aesP.h"

/** destroys the specified window and releases any memory allocated for it.
 *
 *  @param WindowHandle specifies the window handle of the window to
 *         destroy.
 *  @param global_aes global AES array
 *
 *  @return 0 if an error occurred or non-zero otherwise.
 *
 *  @since All AES versions.
 *
 *  @sa mt_wind_create(), mt_wind_open(), mt_wind_close(), mt_wind_new()
 *
 *  A window should by closed with wind_close() before deleting
 *  it.
 *
 */
 
short 
mt_wind_delete (short WindowHandle, short *global_aes)
{
	AES_PARAMS(103,1,1,0,0);

	aes_intin[0] = WindowHandle;

	AES_TRAP(aes_params);

	return (aes_intout[0]);
}

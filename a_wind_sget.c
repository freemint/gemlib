#include "gem_aesP.h"

/** returns the current window title or the current info line of a window.
 *
 *  @param WindowHandle specifies the handle of the window to return
 *         information about (0 is the desktop window)
 *  @param What specifies the information to return and the value
 *         placed into \a str. Can be WF_INFO or WF_NAME
 *  @param str is a pointer to a memory buffer where the window title or the
 *         current info line should be copied to
 *
 *  @param global_aes global AES array
 *
 *  see mt_wind_get() documentation for more details.
 */

short
mt_wind_sget (short WindowHandle, short What,
             char *str, short *global_aes)
{
	AES_PARAMS(104,4,1,0,0);

	aes_intin[0] = WindowHandle;
	aes_intin[1] = What;
	aes_intin_ptr(2, char *) = str;

	AES_TRAP(aes_params);

	return (aes_intout[0]);
}

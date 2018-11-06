#include "gem_aesP.h"

/** removes a window from the display screen.
 *
 *  @param WindowHandle specifies the window handle of the window to close.
 *  @param global_aes global AES array
 *
 *  @return 0 if an error occurred or non-zero otherwise.
 *
 *  @since All AES versions.
 *
 *  @sa mt_wind_create(), mt_wind_open(), mt_wind_delete()
 *
 *  Upon calling mt_wind_close() a redraw message for the portion
 *  of the screen changed will be sent to all applications.
 *  Calling mt_wind_close() does not release the memory allocated
 *  to the window structure. mt_wind_delete() must be called to
 *  permanently destroy the window and free any memory
 *  allocated by the AES for the window. Until mt_wind_delete() is
 *  called, the window may be re-opened at any time with
 *  mt_wind_open().
 *
 */

short 
mt_wind_close (short WindowHandle, short *global_aes)
{
	AES_PARAMS(102,1,1,0,0);

	aes_intin[0] = WindowHandle;

	AES_TRAP(aes_params);

	return (aes_intout[0]);
}

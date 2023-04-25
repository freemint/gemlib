#include "gem_aesP.h"
#include "mt_gemx.h"
#include "gem.h"
#include <stdarg.h>

/** Read formatted data from a string, with extended formats.
 *
 *  @param buf
 *  @param fmt
 *  @param global_aes global AES array
 *
 *  @since Geneva
 *
 */

/* this is only available with -mshort, because otherwise size of int does not match */
#ifdef __MSHORT__
#define global_aes aes_global
void
mt_x_sscanf(const char *buf, const char *fmt, ...)
{
	va_list args;
	AES_PARAMS(0x7184,0,0,3,0);

	va_start(args, fmt);
	aes_addrin[0] = (long)buf;
	aes_addrin[1] = (long)fmt;
	aes_addrin[2] = (long)args;
	va_end(args);

	AES_TRAP(aes_params);
}
#undef global_aes
#endif

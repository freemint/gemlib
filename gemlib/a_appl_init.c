/*
 *  $Id$
 */

#include "gem_aesP.h"

/** should be the first function called in any application that intends
 *  to use GEM calls.
 *
 *  @param global_aes global AES array
 *
 *  @return the applications' global identifier if
 *			successful or -1 if the AES cannot register the
 *			application. If successful, the global identifier should
 *			be stored in a global variable for later use.
 *			GEM applications may not make any AES or VDI calls unless
 *			appl_init() succeeds.
 *			Besides the return value, the AES fills in the
 *			application's global array (to reference the global array
 *			see your programming languages' manual).
<pre>
       Name       global[x] Meaning

       _AESversion    0     AES version number.

       _AESnumapps    1     Number of concurrent applications
                            possible (normally 1). MultiTOS
                            will return -1.

       _AESapid       2     Application identifier (same as
                            appl_init() return value).

       _AESappglobal  3-4   LONG global available for use by the
                            application.

       _AESrscfile    5-6   Pointer to the base of the resource
                            loaded via rsrc_load().

       (reserved)     7-12  Reserved

       _AESmaxchar    13    Current maximum character used by the
                            AES to do vst_height() prior to
                            writing to the screen. This entry is
                            only present as of AES version 0x0400.

       _AESminchar    14    Current minimum character used by the
                            AES to do vst_height() prior to
                            writing to the screen. This entry is
                            only present as of AES version 0x0400.
</pre>
 *
 *  @since All AES versions.
 *
 *  @sa mt_appl_exit()
 *
 */

short
mt_appl_init(short *global_aes)
{
	AES_PARAMS(10,0,1,0,0);

	AES_TRAP(aes_params);

	return aes_intout[0];
}

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
 *			mt_appl_init() succeeds.
 *			Besides the return value, the AES fills in the
 *			application's global array ( \a global_aes) as following:
 * <table>
 * <tr><td> Name <td> index of \a global_aes[] <td> Meaning
 *
 * <tr><td> mt_AESversion()  <td>  0  <td>
 *                           AES version number.
 *
 * <tr><td>  mt_AESnumapps() <td>	1	 <td>
 *                            Number of concurrent applications
 *							  possible (normally 1). MultiTOS
 *							  will return -1.
 *
 * <tr><td>  mt_AESapid()	<td>	2	  <td>
 *                           Application identifier (same as
 *		    			     mt_appl_init() return value).
 *
 * <tr><td> mt_AESappglobal() <td> 3-4   <td>
 *                           LONG global available for use by the
 *		    			     application.
 *
 * <tr><td> mt_AESrscfile()<td>	5-6  <td>
 *                            Pointer to the base of the resource
 *		    			      loaded via mt_rsrc_load().
 *
 * <tr><td> (reserved)   <td>  7-9  <td>
 *                           Reserved
 *                           
 * <tr><td> (reserved)   <td>  10  <td>
 *                           Number of planes of the VDI workstation
 *                           opened by the AES (used by BubbleGEM)
 *                           
 * <tr><td> (reserved)   <td>  11-12  <td>
 *                           Reserved
 *
 * <tr><td> mt_AESmaxchar()  <td>  13	 <td>
 *                           Current maximum character used by the
 *							 AES to do vst_height() prior to
 *							 writing to the screen. This entry is
 *							 only present as of AES version 0x0400.
 *
 * <tr><td> mt_AESminchar() <td>	14    <td>
 *                           Current minimum character used by the
 *							 AES to do vst_height() prior to
 *							 writing to the screen. This entry is
 *							 only present as of AES version 0x0400.
 * </table>
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
	
	/* clear some variable that may be used to check if an AES is loaded */
	global_aes[0] = 0;  /* AES version number */
	global_aes[2] = -1;  /* AES application ID */
	aes_intout[0] = -1;  /* AES application ID */

	AES_TRAP(aes_params);

	return aes_intout[0];
}

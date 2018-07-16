/*
 *  $Id$
 */

#include "gem_aesP.h"

/** returns information about the AES.
 *
 *  @param type specifies the type of information to be returned
 *         in the strings pointed to by \a out1, \a out2, \a out3
 *         and \a out4.
 *  @param out1 pointer to a string or NULL
 *  @param out2 pointer to a string or NULL
 *  @param out3 pointer to a string or NULL
 *  @param out4 pointer to a string or NULL
 *  @param global_aes global AES array
 *
 *  @return 0 if an error occurred or non-zero otherwise.
 *
 *  @since Available as of AES version 4.00.
 *
 *  @sa mt_appl_init()
 *
 *  The table hereafter summaries the values returned in
 *  \a out1, \a out2, \a out3 and \a out4 depending on the
 *  \a type of information requested.
 *
 *  <table>
 *  <tr><td> Name <td> Value <td> Returns
 *  <tr><td> #AES_VERSION <td>  96    <td>
 *                    Additional AES functions
 *                    - \a out1 :  will be filled in with the identifiant
 *                      of the AES. This is a character string with a fixed
 *                      lenght of 8 bytes, into which the AES will write
 *                      its unique AES ID. The AES ID is a left-aligned,
 *                      space padded string, and can be considered to be
 *                      the current AES's short name. For XaAES this string
 *                      is filled with "XaAES   ". This string is not null-terminated.
 *                    - \a out2 : will be filled with the long name of the AES.
 *                      the buffer provided in \a out2 should take up to 256 (255 +
 *                      0 termination) characters. This buffer may contain CR
 *                      (ascii 13) for change of line. For XaAES, this
 *                      buffer contains "XaAES Ain't the AES, a free MultiTasking AES for
 *                      FreeMiNT".
 *                    - \a out3 : will be filled with an info string that describe the AES.
 *                      the buffer provided in \a out3 should take up to 256 (255 +
 *                      0 termination) characters. This buffer may contain CR
 *                      (ascii 13) for change of line. For XaAES, this
 *                      buffer contains "asci version|development status|architecture target|
 *                      build date & time|compiler used" with character "|" (ascii 0x7c) as delimiter.
 *                      An example of string : "0.992|Alpha|m68k|Dec 17 2004 22:58:52|gcc 2.95.3".
 *  </table>
 *
 *  @note
 *  If mt_appl_getinfo_str() is not implemented (mt_AESversion() < 0X0400 and the
 *  application "?AGI" (Winx, Magic>2) is not found), the trap is not performed
 *  (may crash on some system).
 *
 *  @note
 *  MagiC 2 have this AES call implemented, but "?AGI" is here since MagiC3 only...
 *  so this call will not work as expected with Magic2. One way is to check the magx cookie
 *  but i don't want to create dependencies between gemlib and any standard libc. So ATM,
 *  mt_appl_getinfo() is not executed on Magic2. Is it a real problem ?
 *  
 */

short
mt_appl_getinfo_str (short type, char *out1, char *out2, char *out3, char *out4, short *global_aes)
{
	static int has_agi = -1; /* do the check only once */

	AES_PARAMS(130,1,1,4,0);

	if (has_agi < 0) {
		has_agi = global_aes[0] >= 0x400 || 
		          mt_appl_find("?AGI\0\0\0\0",global_aes) >= 0;
	}
	if (!has_agi) {
		return 0;
	}

	aes_intin[0] = type;
	
	aes_addrin[0] = (long)out1;
	aes_addrin[1] = (long)out2;
	aes_addrin[2] = (long)out3;
	aes_addrin[3] = (long)out4;
	
	AES_TRAP(aes_params);

	return (aes_intout[0]);
}

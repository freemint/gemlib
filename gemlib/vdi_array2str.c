/*
 *  $Id$
 */

#include "mt_gem.h"

/** transform VDI-string (each character is 16-bit wide, the string is not
 *  null-terminated and len is in another parameter) to standard C-string.
 *
 *  @param src input str, each char is 16-bit wide.
 *         (src[0] is the 1st character, src[1] is the 2nd char, etc...)
 *  @param des output string, each char is 8-bit wide (standard NULL-terminated
 *         C-string)
 *  @param len is the len of the input string.
 *
 *  
 */

void
vdi_array2str (const short *src, char *des, short len)
{
	while (len > 0)
	{
		*(des++) = (char) *(src++);
		len--;
	}
	*des = '\0';
}

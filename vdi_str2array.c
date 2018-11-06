#include "mt_gem.h"

/** 
 *
 *  @param src input string (standard null-terminated C-string)
 *  @param des output string (VDI format, each char occupied 16 bits)
 *
 *  @return the len of the string
 *
 */

short
vdi_str2array (const char *src, short *des)
{
	short                 len = 0;
	const unsigned char *c  = (const unsigned char *) src;

	while (*c)
	{
		*(des++) = *(c++);
		len++;
	}
	return len;
}

/** 
 *
 *  @param src input string (standard null-terminated C-string)
 *  @param des output string (VDI format, each char occupied 16 bits)
 *  @param nmax maximum of char to translate in the output string
 *
 *  @return the len of the string
 *
 */

short
vdi_str2array_n (const char *src, short *des, int nmax)
{
	short                 len = 0;
	const unsigned char *c  = (const unsigned char *) src;

	while (*c && (len<nmax))
	{
		*(des++) = *(c++);
		len++;
	}
	return len;
}



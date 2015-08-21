/*
 *  $Id$
 */

#include "mt_gem.h"

/** 
 *
 *  @param src input string (standard null-terminated C-string)
 *  @param des outpur string (VDI format, each char occupied 16 bits)
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



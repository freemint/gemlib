/*
 *  $Id$
 */

#include "mt_gem.h"
#include "gem.h"

/** return the length of a w-string
 *
 *  @param wstr a string with 16 bits per character, null-terminated.
 *
 *  @return the length of the string
 *
 *
 */

short
vdi_wstrlen (const short *wstr)
{
	register short len = 0;
	
	while (*wstr++)
		len++;
	
	return len;
}

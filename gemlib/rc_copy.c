/*
 *  $Id$
 */

#include "mt_gem.h"
#include "gem.h"

/** copy a GRECT structure
 *
 *  @param src
 *  @param dst
 *
 *  @return always 1.
 *
 */
 
short
rc_copy (const GRECT * src, GRECT * dst)
{
	*dst = *src;
	return 1;
}

/*
 *  $Id$
 */

#include "gem_aesP.h"

/** provides a method of identifying all of the
 *  currently running processes.
 *
 *  @param mode specifies the search mode as follows:
 *         - APP_FIRST (0) Return the filename of the first process
 *         - APP_NEXT (1) Return the filename of subsequent processes
 *  @param fname should point to a memory location at least 9 bytes
 *		   long to hold the 8 character process filename found and
 *		   the NULL byte.
 *  @param type is a pointer to a WORD into which will be
 *		   placed the process type as follows:
 *	       - APP_SYSTEM        (0x01)   System process
 *	       - APP_APPLICATION   (0x02)   Application
 *	       - APP_ACCESSORY     (0x04)   Accessory
 *	       - APP_SHELL         (0x08)
 *  @param ap_id is a pointer to a word into which will be placed the
 *	       processes' application identifier.
 *  @param global_aes global AES array
 *
 *  @return 0 if no more applications exist or 1
 *          when more processes exist that meet the search criteria.
 *
 *  @since Available only in AES versions 4.0 and above when
 *         mt_appl_getinfo() indicates its presence.
 *
 *  The \p type parameter is actually a bit mask so it is possible
 *  that a process containing more than one characteristic will
 *  appear. The currently running shell process (usually the
 *  desktop) will return a value of APP_APPLICATION | APP_SHELL
 *  (0x0A).
 */

short
mt_appl_search(short mode, char *fname, short *type, short *ap_id, short *global_aes)
{
	AES_PARAMS(18,1,3,1,0);

	aes_intin[0]  = mode;
	aes_addrin[0] = (long)fname;

	AES_TRAP(aes_params);

	*type  = aes_intout[1];
	*ap_id = aes_intout[2];

	return aes_intout[0];
}

#ifdef appl_search
#undef appl_search
#endif
short
appl_search(short mode, char *fname, short *type, short *ap_id)
{
	return(mt_appl_search( mode, fname, type, ap_id, aes_global));
}


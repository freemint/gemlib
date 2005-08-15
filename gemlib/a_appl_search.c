/*
 *  $Id$
 */

#include "gem_aesP.h"

/** provides a method of identifying all of the
 *  currently running processes.
 *
 *  @param mode specifies the search mode as follows:
 *         - #APP_FIRST (0) Return the filename of the first process
 *         - #APP_NEXT (1) Return the filename of subsequent processes
 *         - #APP_DESK (2) Return the filename of the desktop
 *  @param fname should point to a memory location at least 9 bytes
 *		   long to hold the 8 character process filename found and
 *		   the NULL byte.
 *  @param type is a pointer to a WORD into which will be
 *		   placed the process type as follows:
 *	       - #APP_SYSTEM        (0x01)   System process
 *	       - #APP_APPLICATION   (0x02)   Application
 *	       - #APP_ACCESSORY     (0x04)   Accessory
 *	       - #APP_SHELL         (0x08)
 *	       .
 *         [option CHECK_NULLPTR] type may be NULL
 *  @param ap_id is a pointer to a word into which will be placed the
 *	       processes' application identifier. \n
 *         [option CHECK_NULLPTR] ap_id may be NULL
 *  @param global_aes global AES array
 *
 *  @return 0 if no more applications exist or 1
 *          when more processes exist that meet the search criteria.
 *
 *  @since Available only in AES versions 4.0 and above when
 *         mt_appl_getinfo() indicates its presence.
 *
 *  The \a type parameter is actually a bit mask so it is possible
 *  that a process containing more than one characteristic will
 *  appear. For example, the desktop may return a value of
 *  #APP_APPLICATION | #APP_SHELL (0x0A).
 *
 *  @note  This function may be used to obtan other values if the
 *         AES support it. The availability of this extension is given
 *         by mt_appl_getinfo() with #AES_EXTENDED mode. This extension
 *         is used by putting an AES-ID (with the minus sign) as
 *         \a mode parameter. Then :
 *         - \a fname will contain a description of the application
 *           (previoulsy registered by the application by calling
 *           mt_menu_register())
 *         - \a type meaning is unchanged.
 *         - \a ap_id will contain the process ID given by MiNT.
 */

short
mt_appl_search(short mode, char *fname, short *type, short *ap_id, short *global_aes)
{
	AES_PARAMS(18,1,3,1,0);

	aes_intin[0]  = mode;
	aes_addrin[0] = (long)fname;

	AES_TRAP(aes_params);

#if CHECK_NULLPTR
	if (type)
#endif
	*type  = aes_intout[1];
#if CHECK_NULLPTR
	if (ap_id)
#endif
	*ap_id = aes_intout[2];

	return aes_intout[0];
}

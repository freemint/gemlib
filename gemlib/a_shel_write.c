/*
 *  $Id$
 */

#include "gem_aesP.h"

/** is a multi-purpose function which handles the
 *  manipulation and launching of processes.
 *
 *  @param wodex specifies the meaning of the rest of the parameters as
 *         follows:<pre>
Name         mode  Meaning

SWM_LAUNCH     0   Launch a GEM or TOS application or GEM
                   desk accessory depending on the
                   extension of the file. This mode is only
                   available as of AES version 4.0. \p wisgr
                   is not used in mode SWM_LAUNCH (0). When
                   the lower eight bits of mode are
                   SWM_LAUNCH (0), SWM_LAUNCHNOW (1), or
                   SWM_LAUNCHACC (3), appropriate bits in
                   the upper byte may be set to enter
                   'extended' mode. The bits in the upper
                   byte are assigned as follows:

                   Name         Mask   Meaning
                   SW_PSETLIMIT 0x100  Initial Psetlimit()
                   SW_PRENICE   0x200  Initial Prenice()
                   SW_DEFDIR    0x400  Default Directory
                   SW_ENVIRON   0x800  Environment

                   If the upper byte is empty, extended
                   mode is not entered and \p cmd specifies
                   the filename (to search for the file
                   with shel_find() ) or the complete
                   file specification. Otherwise, if any
                   extended bits are set, \p cmd points to
                   a structure as shown below.

                   typedef struct _shelw
                   {
                    char *newcmd;
                    LONG psetlimit;
                    LONG prenice;
                    char *defdir;
                    char *env;
                   } SHELW;

                   _shelw.newcmd points to the filename
                   formatted in the manner indicated
                   above.
                   If bit 8 (SW_PSETLIMIT) of mode is set,
                   _shelw.psetlimit contains the maximum
                   memory size available to the process.
                   If bit 9 of mode is (SW_PRENICE) set,
                   _shelw.prenice contains the process
                   priority of the process to launch.
                   If bit 10 of mode (SW_DEFDIR) is set,
                   _shelw.defdir points to a character
                   string containing the default directory
                   for the application begin launched.
                   If bit 11 of mode (SW_ENVIRON) is set,
                   _shelw.env points to a valid environment
                   string for the process.
                   tail points to a buffer containing the
                   command tail to pass to the process. If
                   \p wiscr is set to CL_NORMAL (0), tail is
                   passed normally, otherwise, if \p wiscr is
                   set to CL_PARSE (1), the AES will parse
                   tail and set up an ARGV environment
                   string.
                   modes SWM_LAUNCH (0), SWM_LAUNCHNOW
                   (1), and SWM_LAUNCHACC (3) return the
                   AES id of the started process. If a 0 is
                   returned, then the process was not
                   launched.
                   Under MultiTOS, processes are launched
                   concurrently with their parent. An exit
                   code is returned in a CH_EXIT message
                   when the child terminates. See
                   evnt_mesag().
                   In AES versions 4.0 and above,
                   mt_appl_getinfo() should be used to
                   determine the exact result of this call.

SWM_LAUNCHNOW  1   Launch a GEM or TOS application based on
                   the value of \p wisgr. If \p wisgr is TOSAPP
                   (0), the application will be launched as
                   a TOS application, otherwise if \p wisgr is
                   GEMAPP (1), the application will be
                   launched as a GEM application. For the
                   meaning of other parameters, see mode
                   SWM_LAUNCH (0). The extended bits in
                   mode are only supported by AES versions
                   of at least 4.0.
                   Parent applications which launch
                   children using this mode are suspended
                   under MultiTOS.
                   In AES versions 4.0 and above,
                   mt_appl_getinfo() should be used to
                   determine the exact result of this call.

SWM_LAUNCHACC  3   Launch a GEM desk accessory. For the
                   meaning of other parameters, see mode
                   SWM_LAUNCH (0). This mode is only
                   supported by AES versions of at least
                   4.0.

SWM_SHUTDOWN   4   Manipulate 'Shutdown' mode. Shutdown
                   mode is usually used prior to
                   a resolution change to cause system
                   processes to terminate. \p wisgr, \p cmd, and
                   \p tail are ignored by this call. The value
                   of \p wiscr determines the action this call
                   takes as follows:

                   Name      wiscr Meaning
                   SD_ABORT    0   Abort shutdown mode
                   SD_PARTIAL  1   Partial shutdown mode
                   SD_COMPLETE 2   Complete shutdown mode

                   During a shutdown, processes which
                   have registered themselves as accepting
                   AP_TERM messages will be sent them and
                   all accessories will be sent AC_CLOSE
                   messages. In addition, in complete
                   shutdown mode, AP_TERM messages will
                   also be sent to accessories.
                   Shutdown mode may be aborted but only
                   by the original caller.
                   The status of the shutdown is sent to
                   the calling processes by AES messages.
                   See mt_evnt_mesag().
                   This mode is only supported by AES
                   versions greater than or equal to 4.0.

SWM_RESCHANGE  5   Change screen resolution. \p wisgr is the
                   work station ID (same as in AES
                   global_aes[13]) of the new resolution. No
                   other parameters are utilized.
                   This mode is only recognized as of AES
                   version 4.0.

SWM_BROADCAST  7   Broadcast an AES message to all
                   processes. \p cmd should point to an 8 WORD
                   message buffer containing the message to
                   send. All other parameters are ignored.
                   This mode is only recognized as of AES
                   version 4.0.

SWM_ENVIRON    8   Manipulate the AES environment. If \p wisgr
                   is ENVIRON_SIZE (0), the current size of
                   the environment string is returned.
                   If \p wisgr is ENVIRON_CHANGE (1), \p cmd
                   should point to a environment variable
                   to modify. If \p cmd points to
                   "TOSEXT=TOS,TTP", that string will be
                   added. Likewise, "TOSEXT=" will remove
                   that environment variable.
                   If \p wisgr is ENVIRON_COPY (2), the AES
                   will copy as many as \p wiscr bytes of the
                   current environment string into a buffer
                   pointer to by \p cmd. The function will
                   return the number of bytes not copied.
                   This mode is only recognized as of AES
                   version 4.0.

SWM_NEWMSG     9   Inform the AES of a new message the
                   current application understands. \p wisgr
                   is a bit mask which specifies which new
                   messages the application understands.
                   Currently only bit 0 (NM_APTERM) has
                   a meaning. Setting this bit when calling
                   this function will inform the AES that
                   the application understands AP_TERM
                   messages. No other parameters are used.
                   This mode is only recognized as of AES
                   version 4.0.

SWM_AESMSG     10  Send a message to the AES. \p cmd points to
                   an 8 WORD message buffer containing the
                   message to send. No other parameters are
                   needed.
                   This mode is only recognized as of AES
                   version 4.0.</pre>

 *  @param wisgr see above
 *  @param wiscr see above
 *  @param cmd see above
 *  @param tail see above
 *  @param global_aes global AES array
 *
 *  @return The value mt_shel_write() differs depending on the mode which
 *          was invoked. See above for details.
 *
 *  @since All AES versions. In AES versions 4.0 and above,
 *         appl_getinfo() can be used to determine the highest legal
 *         value for mode as well as the functionality of extended
 *         mode bits.
 *
 *  Many new features were added as of AES version 4.0. For
 *  details of each, see above.
 *
 */
 
short 
mt_shel_write(short wodex, short wisgr, short wiscr, void *cmd, char *tail, short *global_aes)
{
	AES_PARAMS(121,3,1,2,0);
                    
	aes_intin[0] = wodex;
	aes_intin[1] = wisgr;
	aes_intin[2] = wiscr;
	aes_addrin[0] = (long)cmd;
	aes_addrin[1] = (long)tail;

	AES_TRAP(aes_params);

	return aes_intout[0];
}

/*
 *  $Id$
 */

#include "gem_aesP.h"

/** is a multi-purpose function which handles the
 *  manipulation and launching of processes.
 *
 *  @param wodex specifies the action to perform. See the table hereafter.
 *  @param wisgr its meaning depends on \a wodex. See the table hereafter.
 *  @param wiscr its meaning depends on \a wodex. See the table hereafter.
 *  @param cmd its meaning depends on \a wodex. See the table hereafter.
 *  @param tail its meaning depends on \a wodex. See the table hereafter.
 *  @param global_aes global AES array
 *
 *  @return The value returned differs depending on the mode \a wodex which
 *          was invoked. See above for details.
 *
 *  <table>
 *  <tr><td> Name <td> Mode <td> Meaning
 *
 *  <tr><td> #SWM_LAUNCH  <td>   0  <td>
 *			 Launch a GEM or TOS application or GEM
 *			 desk accessory depending on the
 *			 extension of the file. This mode is only
 *			 available as of AES version 4.0. \n
 *			 - \a wisgr is not used.
 *			 - \a tail points to a buffer containing the
 *			   command tail to pass to the process.
 *			 - \a wiscr may be :
 *			   - #CL_NORMAL, tail is passed normally,
 *			   - #CL_PARSE, the AES will parse
 *			     tail and set up an ARGV environment
 *			     string.
 *
 *			 This function returns the AES id of the started
 *			 process. If 0 is returned then the process was not
 *			 launched.
 *
 *			 Under MultiTOS, processes are launched
 *			 concurrently with their parent. An exit
 *			 code is returned in a #CH_EXIT message
 *			 when the child terminates.
 *			 In AES versions 4.0 and above,
 *			 mt_appl_getinfo() should be used to
 *			 determine the exact result of this call.
 *
 *  <tr><td> #SWM_LAUNCHNOW <td> 1 <td>
 *			 Launch a GEM or TOS application based on
 *			 the value of \a wisgr.
 *			 - \a wisgr may be:
 *			   - #TOSAPP : the application will be launched as
 *			     a TOS application
 *			   - #GEMAPP, the application will be
 *			     launched as a GEM application.
 *			 - For the meaning of other parameters and the meaning
 *             of returned value, see mode #SWM_LAUNCH.
 *
 *			 Parent applications which launch
 *			 children using this mode are suspended
 *			 under MultiTOS.
 *
 *			 In AES versions 4.0 and above,
 *			 mt_appl_getinfo() should be used to
 *			 determine the exact result of this call.
 *
 *  <tr><td> #SWM_LAUNCHACC <td> 3 <td>
 *			 Launch a GEM desk accessory.
 *
 *           For the meaning of other parameters and the meaning of
 *           the return value, see mode #SWM_LAUNCH.
 *
 *           This mode is only
 *			 supported by AES versions of at least
 *			 4.0.
 *
 *  <tr><td> #SWM_SHUTDOWN  <td> 4 <td>
 *			 Manipulate 'Shutdown' mode. Shutdown
 *			 mode is usually used prior to
 *			 a resolution change to cause system
 *			 processes to terminate.
 *			 - \a wisgr, \a cmd, and
 *			   \a tail are ignored by this call.
 *			 - \a wiscr determines the action this call
 *			   takes as follows:
 *			   - #SD_ABORT : Abort shutdown mode
 *			   - #SD_PARTIAL : Partial shutdown mode
 *			   - #SD_COMPLETE : Complete shutdown mode
 *
 *			 During a shutdown, processes which
 *			 have registered themselves as accepting
 *			 #AP_TERM messages will be sent them and
 *			 all accessories will be sent #AC_CLOSE
 *			 messages. In addition, in complete
 *			 shutdown mode, #AP_TERM messages will
 *			 also be sent to accessories.
 *
 *			 Shutdown mode may be aborted but only
 *			 by the original caller.
 *
 *			 The status of the shutdown is sent to
 *			 the calling processes by AES messages.
 *			 This mode is only supported by AES
 *			 versions greater than or equal to 4.0.
 *
 *  <tr><td> #SWM_REZCHANGE <td> 5 <td>
 *			 Change screen resolution.
 *			 - \a wisgr is the work station ID of the new resolution.
 *           - No other parameters are utilized.
 *
 *			 This mode is only recognized as of AES
 *			 version 4.0.
 *
 *  <tr><td> #SWM_BROADCAST <td> 7 <td>
 *			 Broadcast an AES message to all processes.
 *			 - \a cmd should point to an 8 WORD
 *			    message buffer containing the message to
 *			    send. 
 *			 - All other parameters are ignored.
 *
 *			 This mode is only recognized as of AES
 *			 version 4.0.
 *
 *  <tr><td> #SWM_ENVIRON  <td>  8 <td>
 *           Manipulate the AES environment. 
 *           - \a wisgr may be:
 *             - #ENVIRON_SIZE, the current size of
 *			     the environment string is returned.
 *			   - #ENVIRON_CHANGE, \a cmd
 *			     should point to a environment variable
 *			     to modify. If \a cmd points to
 *			     <tt>"TOSEXT=TOS,TTP"</tt>, that string will be
 *			     added. Likewise, <tt>"TOSEXT="</tt> will remove
 *			     that environment variable.
 *			   - #ENVIRON_COPY, the AES
 *			     will copy as many as \a wiscr bytes of the
 *			     current environment string into a buffer
 *			     pointer to by \a cmd. The function will
 *			     return the number of bytes not copied.
 *
 *			 This mode is only recognized as of AES
 *			 version 4.0.
 *
 *  <tr><td> #SWM_NEWMSG   <td>  9  <td>
 *           Inform the AES of a new message the
 *			 current application understands.
 *           - \a wisgr is a bit mask which specifies which new
 *			   messages the application understands.
 *			   Currently only bit 0 (#NM_APTERM) has
 *			   a meaning. Setting this bit when calling
 *			   this function will inform the AES that
 *			   the application understands #AP_TERM
 *			   messages. 
 *           - No other parameters are used.
 *
 *			 This mode is only recognized as of AES
 *			 version 4.0.
 *
 *  <tr><td> #SWM_AESMSG    <td> 10 <td>
 *           Send a message to the AES.
 *           - \a cmd points to
 *			   an 8 WORD message buffer containing the
 *			   message to send. 
 *           - No other parameters are needed.
 *
 *			 This mode is only recognized as of AES
 *			 version 4.0.
 *
 *  <tr><td> #SWM_THRCREATE <td> 20 <td>
 *           (Magic 4.5 ? Doc wanted !!!)		  
 *	</table>
 *
 *  The parameter \a wodex have extended bits, only supported
 *  by AES versions of at least 4.0. When the lower eight bits
 *  of mode are #SWM_LAUNCH, #SWM_LAUNCHNOW, or #SWM_LAUNCHACC,
 *  appropriate bits in the upper byte may be set to enter
 *	'extended' mode. The bits in the upper byte are assigned
 *   as follows:
 *   - #SW_PSETLIMIT 
 *   - #SW_PRENICE   
 *   - #SW_DEFDIR    
 *   - #SW_ENVIRON   
 *
 *	If the upper byte is empty, extended mode is not entered and 
 *  \a cmd specifies the filename (to search for the file
 *	with mt_shel_find() ) or the complete file specification. Otherwise,
 *  if any extended bits are set, \a cmd points to a #SHELW structure.
 *
 *  @since All AES versions. In AES versions 4.0 and above,
 *         mt_appl_getinfo() with parameter #AES_SHELL can be used to determine the highest legal
 *         value for mode as well as the functionality of extended
 *         mode bits.
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

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
 *           - \a wiscr may be (MagiC extension):
 *             - #SHW_IMMED (not supported by MagiC)
 *             - #SHW_CHAIN : This is the procedure under TOS. The program makes the call, and 
 *				 after terminating itself the AES launches the new program. #SHW_CHAIN
 *				 does not work with desk accessories, as these must never be permitted
 *				 to terminate. \n
 *				 The new program inherits the standard paths and files that the
 *				 previous program had at the time of its launch. In general these are
 *				 in turn the ones that the program had that earlier launched the
 *				 "ancestor" of the application with #SHW_PARALLEL. In the case of
 *				 application #0 therefore the new program gets the standard paths of
 *				 the  AES. \n
 *				 If \c DESKTOP.APP (shell of GEM 2.2) is installed as a shell, then
 *				 Mag!X will insert the current path and drive before the filename.
 *             - #SHW_DOS (not supported by MagiC)
 *             - #SHW_PARALLEL : A new application will be created. It inherits all standard paths 
 *				 and files from the current application. The new application runs in
 *				 parallel to the previous one. One will only get an error code if a
 *				 memory shortage occured during set-up. There is no message at the
 *				 termination of the new application (no "death-of-child").
 *             - #SHW_SINGLE Works like #SHW_CHAIN, with the exception that before calling the 
 *				 program all applications apart from application 0 and 1 (SCRENMGR)
 *				 are frozen. The programs are unfrozen once more after the program
 *				 terminates as long as it did not make a new mt_shel_write() call with
 *				 #SHW_SINGLE on its part. \n
 *				 One should add that from Mag!X 2.00 onward when calling mt_shel_write()
 *				 in #SHW_SINGLE mode the current paths of the caller are passed to the
 *				 parent and hence to the new program. Warning: The paths of the
 *				 calling program are destroyed after this, though this is not critical
 *				 as the call following mt_shel_write() is generally a Pterm.
 *			 - For the meaning of returned value, see mode #SWM_LAUNCH.
 *
 *			 How do I launch a program in "single mode" under MagiC ?
 *			  -#   Ensure that I am application 0 (i.e. ap_id == 0).
 *			  -#   Set paths and drive for the new program.
 *			  -#   mt_shel_write(1, isgr, #SHW_SINGLE, cmd, path);
 *			  -#   All important settings to temporary file or shell-buffer.
 *			  -#   mt_appl_exit()/v_clsvwk()/Pterm0.
 *
 *			 How do I launch a program in "chain mode" under MagiC ?
 *			  -#   If appropriate set paths and drive for the new program and make a call
 *			 	   mt_shel_write(1, dummy, #SHW_SINGLE, dummy2, dummy3);
 *			 	   in order to set the paths for the new program (incompatible to TOS).
 *			  -#   shel_write(1, isgr, #SHW_CHAIN, cmd, path);
 *			  -#   All important settings to temporary file or shell-buffer.
 *			  -#   mt_appl_exit()/v_clsvwk()/Pterm0.
 *
 *			 After the program terminates the shell will be reloaded automatically.
 *			 When calling the shell one gets in the command line (-> mt_shel_read() ) the
 *			 "magic" sequence #SHELTAIL.
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
 *           The application produces a new Thread
 *           - \a wisgr	can be:
 *             - 0 = Start program in the VT52 window of the application, if one is opened.	
 *             - 1 = do not open a VT52 window	
 *             - 2 = open new VT52-Fenster	
 *           - \a wiscr shall be set to 0 	
 *           - \a cmd Pointer on #THREADINFO structure.	
 *           - \a tail Parameter of the type (void *) for the Thread function (see THREADINFO::proc).
 *           
 *            The function returns either 0 (error) or the application ID of the new thread
 *            ( > 0).
 *
 *            The launched thread executes the function THREADINFO::proc, and the parameter 
 *            \a tail is passed on the stack.
 *            THREADINFO::proc may alter the CPU registers d0-d2/a0-a2.
 *
 *  <tr><td> #SWM_THREXIT <td> 21 <td>
 *           This mode allows a thread to terminate itself.
 *           - \a wisgr, \a wiscr and \a tail shall be set to 0
 *           - \a cmd shall be set to the error code which will be returned to the parent process
 *           
 *           Returns 0 if an error occured (the function does not return when succeed !). An error
 *           can occur if
 *           -  the callers is not a thread but something else
 *           -  the thread has made a Pexec() call in the meantime
 *
 *           Normally implementing of this function is not necessary, since the thread
 *           is automatically terminated with the end of its procedure (i.e. with the CPU
 *           instruction RTS).
 *
 *			 If the thread has made a Pexec() call, then the running process must be
 *			 first terminated with Pterm() before the thread can terminate itself.
 *
 *
 *  <tr><td> #SWM_THRKILL <td> 22 <td>
 *          This mode allows the main program to terminate a thread.
 *          - \a wiscr contains the application ID of the thread
 *          - \a wisgr, \a tail and \a cmd shall be set to 0
 *
 *          Normally this function is not necessary, since with main program terminates,
 *          then all associated Threads are terminated as well.
 *
 *          Returns 0 (error) or 1 (OK). An error can occur if:
 *			-	the ap_id is invalid
 *			-	the thread has already terminated itself
 *			-	it's not a thread running under the ap_id, but something else
 *			-	the thread does not belong to the caller
 *
 *			Even if the return value is 1, one should note that in cases where the
 *			thread has launched another program with Pexec() in the meantime, only
 *			this program will be terminated with Pterm(EBREAK). The thread will
 *			only be terminated when the caller has received #THR_EXIT.
 *
 *			Warning:  One should note that the memory that the thread allocates
 *			belongs to the process, i.e. it is not released automatically
 *			when the thread terminates. The same applies for open files,
 *			which are closed only on program termination.
 *          
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
 *   - #SW_UID (XaAES only extension)
 *   - #SW_GID (XaAES only extension)
 *   - #SHW_XMDFLAGS (MagiC6 only extension)
 *
 *	If the upper byte is empty, extended mode is not entered and 
 *  \a cmd specifies the filename (to search for the file
 *	with mt_shel_find() ) or the complete file specification. Otherwise,
 *  if any extended bits are set, \a cmd points to a #SHELW structure (or #XSHW_COMMAND
 *  structure if you use MagiC6 extension).
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

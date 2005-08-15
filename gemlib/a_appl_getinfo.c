/*
 *  $Id$
 */

#include "gem_aesP.h"

/** returns information about the AES.
 *
 *  @param type specifies the type of information to be returned
 *         in the shorts pointed to by \a out1, \a out2, \a out3
 *         and \a out4.
 *  @param out1 1st return value \n
 *         [option CHECK_NULLPTR] out1 may be NULL
 *  @param out2 2nd return value \n
 *         [option CHECK_NULLPTR] out2 may be NULL
 *  @param out3 3rd return value \n
 *         [option CHECK_NULLPTR] out3 may be NULL
 *  @param out4 4th return value \n
 *         [option CHECK_NULLPTR] out4 may be NULL
 *  @param global_aes global AES array
 *
 *  @return 0 if an error occurred or non-zero otherwise.
 *
 *  @since Available as of AES version 4.00.
 *
 *  @sa mt_appl_init()
 *
 *  The table hereafter summaries the values returned in
 *  \a out1, \a out2, \a out3 and \a out4 depending on the
 *  \a type of information requested.
 *
 *  <table>
 *  <tr><td> Name <td> Value <td> Returns
 *  <tr><td> #AES_LARGEFONT <td> 0  <td>
 *     	              AES Large Font Information:
 *                    - \a out1 is filled in with the AES font's point size.
 *                    - \a out2 is filled in with the font id.
 *                    - \a out3 is a code indicating the type of font:
 *                         - #SYSTEM_FONT (0) is the system font
 *                         - #OUTLINE_FONT (1) is an outline font
 *                    - \a out4 is unused.
 *
 *  <tr><td> #AES_SMALLFONT  <td>1    <td>
 *     	              AES Large Font Information:
 *                    Same as above for the current small
 *                    font.
 *
 *  <tr><td> #AES_SYSTEM    <td> 2    <td>
 *     	              AES System Specifics
 *                    - \a out1 is filled in with the
 *                         resolution number (as would
 *                         be returned by Getrez()).
 *                    - \a out2 is filled in with the number
 *                         of colors supported by the
 *                         AES object library.
 *                    - \a out3 is 0 if color icons are not
 *                         supported or 1 if they are.
 *                    - \a out4 is a bitmap variable:
 *                         - bit 0 (\a out4 & 0x0001) indicates that the
 *                           extended resource file format (AES4)
 *                           is supported.
 *                         - bit 1 (\a out4 & 0x0002) indicates that interface
 *                           resource file format (RSHDR::rsh_vrsn = 3)
 *                           is supported.
 *
 *  <tr><td> #AES_LANGUAGE  <td> 3    <td>
 *     	              AES Globalization
 *                    - \a out1 is filled in with the current
 *                         AES language code as follows:
 *                          <table>
 *                          <tr><td>  Name             <td> out1 <td>   Language
 *                          <tr><td> #AESLANG_ENGLISH  <td>	0   <td>   English
 *                          <tr><td> #AESLANG_GERMAN   <td>	1   <td>   German
 *                          <tr><td> #AESLANG_FRENCH   <td>	2   <td>   French
 *                          <tr><td>  (reserved)       <td>	3   <td>   (Reserved)
 *                          <tr><td> #AESLANG_SPANISH  <td>	4   <td>   Spanish
 *                          <tr><td> #AESLANG_ITALIAN  <td>	5   <td>   Italian
 *                          <tr><td> #AESLANG_SWEDISH  <td>	6   <td>   Swedish
 *                          </table>
 *                    - \a out2, \a out3, and \a out4 are unused.
 *
 *  <tr><td> #AES_PROCESS  <td>  4    <td>
 *     	              AES Multiple Process Support
 *                    - \a out1 is 0 to indicate the use of
 *                         non-pre-emptive multitasking and 1 to
 *                         indicate the use of pre-emptive
 *                         multitasking.
 *                    - \a out2 is 0 if mt_appl_find() cannot
 *                         convert between MiNT and AES id's and
 *                         1 to indicate that it can.
 *                    - \a out3 is 0 if mt_appl_search() is not
 *                         implemented and 1 if it is.
 *                    - \a out4 is 0 if mt_rsrc_rcfix() is not
 *                         implemented and 1 if it is.
 *
 *  <tr><td> #AES_PCGEM    <td>   5    <td>
 *     	              AES PC-GEM Features
 *                    - \a out1 is 0 if mt_objc_xfind() is not
 *                         implemented and 1 if it is.
 *                    - \a out2 is currently reserved.
 *                    - \a out3 is 0 if mt_menu_click() is not
 *                         implemented and 1 if it is.
 *                    - \a out4 is 0 if mt_shel_rdef() and
 *                         mt_shel_wdef() are not implemented and
 *                         1 if they are.
 *
 *  <tr><td> #AES_INQUIRE  <td>  6    <td>
 *     	              AES Extended Inquiry Functions
 *                    - \a out1 is 0 if -1 is not a valid
 *                         ap_id parameter to mt_appl_read() or 1
 *                         if it is.
 *                    - \a out2 is 0 if #SHEL_BUFSIZE is not a valid
 *                         length parameter to mt_shel_get() or 1
 *                         if it is.
 *                    - \a out3 is 0 if -1 is not a valid
 *                         mode parameter to mt_menu_bar() or 1
 *                         if it is.
 *                    - \a out4 is 0 if #MENU_INSTL is not
 *                         a valid mode parameter to mt_menu_bar()
 *                         or 1 if it is.
 *
 *  <tr><td> #(reserved)   <td>   7    <td>
 *     	              Currently reserved.
 *
 *  <tr><td> #AES_MOUSE    <td>   8    <td>
 *     	              AES Mouse Support
 *                    - \a out1 is 0 to indicate that mode
 *                         parameters of 258-260 are not
 *                         supported by mt_graf_mouse() and 1
 *                         if they are.
 *                    - \a out2 is 0 to indicate that the
 *                         application has control over the
 *                         mouse form and 1 to indicate that
 *                         the mouse form is maintained by
 *                         the AES on a per-application basis.
 *                    - \a out3 and \a out4 are currently
 *                         unused.
 *
 *  <tr><td> #AES_MENU    <td>   9    <td>
 *     	              AES Menu Support
 *                    - \a out1 is 0 to indicate that
 *                         sub-menus are not supported and 1
 *                         if MultiTOS style sub-menus are.
 *                    - \a out2 is 0 to indicate that popup
 *                         menus are not supported and 1 if
 *                         MultiTOS style popup menus are.
 *                    - \a out3 is 0 to indicate that
 *                         scrollable menus are not supported
 *                         and 1 if MultiTOS style scrollable
 *                         menus are.
 *                    - \a out4 is 0 to indicate that the
 *                         #MN_SELECTED message does not contain
 *                         object tree information in msg[5,6,7]
 *                         and 1 to indicate that it does.
 *
 *  <tr><td> #AES_SHELL    <td>   10    <td>
 *     	              AES Shell Support
 *                    - \a out1 & 0x00FF indicates the
 *                         highest legal value for the
 *                         mode parameter of mt_shel_write().
 *                         (parameter \a wodex & 0x00FF)
 *                    - \a out1 & 0xFF00 indicate which
 *                         extended mt_shel_write() mode bits
 *                         are supported. (parameter \a wodex & 0xFF00)
 *                    - \a out2 is 0 if mt_shel_write() with
 *                         a mode parameter of 0 (#SWM_LAUNCH) launches
 *                         an application or 1 if it cancels
 *                         the previous mt_shel_write().
 *                    - \a out3 is 0 if mt_shel_write() with
 *                         a mode parameter of 1 (#SWM_LAUNCHNOW) launches an
 *                         application immediately or 1 if
 *                         it takes effect when the current
 *                         application exits.
 *                    - \a out4 is 0 if ARGV style parameter
 *                         passing is not supported or
 *                         1 if it is.
 *
 *  <tr><td> #AES_WINDOW  <td>   11    <td>
 *     	              AES Window Features
 *                    - \a out1 is a bitmap of extended modes
 *                         supported by mt_wind_get() and/or
 *                         mt_wind_set() (if a bit is set, it is
 *                         supported) as follows:
 *                         <table>
 *                         <tr><td> Bit <td> mode
 *                         <tr><td>  0  <td> #WF_TOP returns window below the
 *                                           top also.
 *                         <tr><td>  1  <td> #WF_NEWDESK get.
 *                         <tr><td>  2  <td> #WF_COLOR get/set.
 *                         <tr><td>  3  <td> #WF_DCOLOR get/set.
 *                         <tr><td>  4  <td> #WF_OWNER get/set.
 *                         <tr><td>  5  <td> #WF_BEVENT get/set.
 *                         <tr><td>  6  <td> #WF_BOTTOM set.
 *                         <tr><td>  7  <td> #WF_ICONIFY set.
 *                         <tr><td>  8  <td> #WF_UNICONIFY set.
 *                         <tr><td>  9  <td> #WF_WHEEL set/get.
 *                         <tr><td>  10 <td> #WF_FIRSTAREAXYWH get.
 *                         <tr><td>  11 <td> #WF_OPTS set/get.
 *                         <tr><td>  12 <td> #WF_MENU set/get.
 *                         <tr><td>  13 <td> #WF_WORKXYWH set/get (and bug-free when AES toolbar is
 *                                            installed)
 *                         <tr><td> 14-15<td> Unused
 *                         </table>
 *                    - \a out2 is current unused.
 *                    - \a out3 is a bitmap of supported
 *                         window behaviors (if a bit is set,
 *                         it is supported) as follows:
 *                         <table>
 *                         <tr><td> Bit <td> Behaviour
 *                         <tr><td>  0  <td>  Iconifier gadget present.
 *                         <tr><td>  1  <td>  Bottomer gadget present.
 *                         <tr><td>  2  <td>  shift-click sends window
 *                                            to bottom.
 *                         <tr><td>  3  <td>  "hot" close box supported.
 *                         <tr><td> 4-15<td>  Unused
 *                         </table>
 *                    - \a out4 is currently unused.
 *
 *  <tr><td> #AES_MESSAGE  <td>  12    <td>
 *     	              AES Extended Messages
 *                    - \a out1 is a bitmap of extra messages
 *                         supported (if a bit is set, it is
 *                         supported) as follows:
 *                         <table>
 *                         <tr><td>  Bit  <td> Message
 *                         <tr><td> 0     <td> #WM_NEWTOP is meaningful.
 *                         <tr><td> 1     <td> #WM_UNTOPPED is sent.
 *                         <tr><td> 2     <td> #WM_ONTOP is sent.
 *                         <tr><td> 3     <td> #AP_TERM is sent.
 *                         <tr><td> 4     <td> Shutdown and resolution
 *                                             change messages.
 *                         <tr><td> 5     <td> #CH_EXIT is sent.
 *                         <tr><td> 6     <td> #WM_BOTTOMED is sent.
 *                         <tr><td> 7     <td> #WM_ICONIFY is sent.
 *                         <tr><td> 8     <td> #WM_UNICONIFY is sent.
 *                         <tr><td> 9     <td> #WM_ALLICONIFY is sent.
 *                         <tr><td> 10    <td> #WM_REPOSED is sent.
 *                         <tr><td> 11-15 <td> Unused
 *                         </table>
 *                    - \a out2 is a bitmap of extra messages
 *                         supported. Current all bits are
 *                         unused.
 *                    - \a out3 is a bitmap indicating
 *                         message behaviour (if a bit is set,
 *                         the behaviour exists) as follows:
 *                         <table>
 *                         <tr><td> Bit <td> Message
 *                         <tr><td>  0  <td>  #WM_ICONIFY message gives
 *                                            coordinates.
 *                         <tr><td> 1-15 <td> Unused
 *                         </table>
 *                    - \a out4 is currently unused.
 *
 *  <tr><td> #AES_OBJECT  <td>   13    <td>
 *     	              AES Extended Objects
 *                    - \a out1 is 0 if 3D objects are not
 *                         supported or 1 if they are.
 *                    - \a out2 is 0 if mt_objc_sysvar() is not
 *                         present, 1 if MultiTOS v1.01
 *                         mt_objc_sysvar() is present, or 2
 *                         if extended mt_objc_sysvar()
 *                         is present.
 *                    - \a out3 is 0 if the system font is
 *                         the only font supported or 1 if
 *                         GDOS fonts are also supported.
 *                    - \a out4 is reserved for OS
 *                         extensions.
 *
 *  <tr><td> #AES_FORM     <td>  14    <td>
 *     	              AES Form Support
 *                    - \a out1 is 0 if 'flying dialogs' are
 *                         not supported or 1 if they are.
 *                    - \a out2 is 0 if keyboard tables are
 *                         not supported or 1 if Mag!X style
 *                         keyboard tables are supported.
 *                    - \a out3 is 0 if the last cursor
 *                         position from mt_objc_edit() is not
 *                         returned or 1 if it is.
 *                    - \a out4 is currently reserved.
 *
 *  <tr><td> #AES_EXTENDED     <td>  64    <td>
 *     	              Extended functions
 *                    - \a out1 is 0 if mt_shel_write() with #AP_AESTERM
 *                         is not supported or 1 if it is.
 *                    - \a out2 is 0 if extended mt_shel_write() mode
 *                         #SWM_SHUTDOWN / #SWM_REZCHANGE are not supported,
 *                         or 1 if they are.
 *                    - \a out3 is 0 if mt_appl_search() with string description
 *                         is not supported, or 1 if it is.
 *                    - \a out4 is 0 if mt_form_error() doesn't support all
 *                         GEMDOS error codes, or 1 if it does.
 *
 *  <tr><td> #AES_NAES <td>  65    <td>
 *                    Additional N.AES functions
 *                    - \a out1 is 1 if mt_appl_control() is available, or
 *                         0 otherwise.
 *                    - \a out2 is filled with the highest Opcode for mt_appl_control()
 *                    - \a out3 is 1 if mt_shel_help() is available, or 0 otherwise.
 *                    - \a out4 is 1 if mt_wind_draw() is available, or 0 otherwise.
 *
 *  <tr><td> #AES_VERSION <td>  96    <td>
 *                    Additional AES functions
 *                    - \a out1 : major version of the AES (ex: 0 for version 0.992).
 *                    - \a out2 : minor version of the AES (ex: 992 for version 0.992).
 *                    - \a out3 : development status. The low byte indicates the release
 *                                status (0=alpha, 1=beta, 2=release). The high byte may be
 *                                1 to indicate a stable version (\a out3 & 0x100),
 *                                or 0 otherwise.
 *                    - \a out4 : target platform. May only be 0 (m68k) for now.
 *
 *  <tr><td> #AES_WOPTS <td>  97    <td>
 *                    return a bitmask of available #WF_OPTS settings. This bitmask
 *                    is identical to that use by the actual wind_set/get(WF_OPTS).
 *                    See mt_wind_set() with #WF_OPTS mode for details.
 *                    - \a out1 : available window options 0 
 *                    - \a out2 : available window options 1 
 *                    - \a out3 : available window options 2 
 *                    - \a out4 : always cleared 
 *  </table>
 *
 *  Using an \a ap_gtype value of 4 and above is only supported as
 *  of AES version 4.1
 *
 *  Many of the \a ap_gtype return values identify features of TOS
 *  not supported by Atari but for the benefit of third-party
 *  vendors. You should contact the appropriate third-party for
 *  documentation on these functions.
 *
 *  @note
 *  If mt_appl_getinfo() is not implemented (mt_AESversion() < 0X0400 and the
 *  application "?AGI" (Winx, Magic>2) is not found), the trap is not performed
 *  (may crash on some system).
 *
 *  @note
 *  MagiC 2 have this AES call implemented, but "?AGI" is here since MagiC3 only...
 *  so this call will not work as expected with Magic2. One way is to check the magx cookie
 *  but i don't want to create dependencies between gemlib and any standard libc. So ATM,
 *  mt_appl_getinfo() is not executed on Magic2. Is it a real problem ?
 *  
 */

short
mt_appl_getinfo (short type, short *out1, short *out2, short *out3, short *out4, short *global_aes)
{
	static int has_agi = -1; /* do the check only once */

	AES_PARAMS(130,1,5,0,0);

	if (has_agi < 0) {
		has_agi = global_aes[0] >= 0x400 || 
		          mt_appl_find("?AGI\0\0\0\0",global_aes) >= 0;
	}
	if (!has_agi) {
		return 0;
	}

	aes_intin[0] = type;

	AES_TRAP(aes_params);

#if CHECK_NULLPTR
	if (out1)
#endif
	*out1 = aes_intout[1];
#if CHECK_NULLPTR
	if (out2)
#endif
	*out2 = aes_intout[2];
#if CHECK_NULLPTR
	if (out3)
#endif
	*out3 = aes_intout[3];
#if CHECK_NULLPTR
	if (out4)
#endif
	*out4 = aes_intout[4];

	return (aes_intout[0]);
}

/*
 *  $Id$
 */

#include "gem_aesP.h"

/** returns information about the AES.
 *
 *  @param type specifies the type of information to be returned
 *         in the shorts pointed to by \p out1, \p out2, \p out3
 *         and \p out4.
 *  @param out1 1st return value
 *  @param out2 2nd return value
 *  @param out3 3rd return value
 *  @param out4 4th return value
\verbatim
    Name      Value               Returns

AES_LARGEFONT  0    AES Large Font Information:
                    out1 is filled in with the AES font's point size.
                    out2 is filled in with the font id.
                    out3 is a code indicating the type of font:
                         SYSTEM_FONT (0) is the system font
                         OUTLINE_FONT (1) is an outline font
                    out4 is unused.

AES_SMALLFONT  1    AES Large Font Information
                    Same as above for the current small
                    font.

AES_SYSTEM     2    AES System Specifics
                    out1 is filled in with the
                         resolution number (as would
                         be returned by Getrez()).
                    out2 is filled in with the number
                         of colors supported by the
                         AES object library.
                    out3 is 0 if color icons are not
                         supported or 1 if they are.
                    out4 is 0 to indicate that the
                         extended resource file format
                         is not supported or 1 if it is.

AES_LANGUAGE   3    AES Globalization
                    out1 is filled in with the current
                         AES language code as follows:

                          Name             out1  Language
                          AESLANG_ENGLISH   0      English
                          AESLANG_GERMAN    1      German
                          AESLANG_FRENCH    2      French
                          (reserved)        3      (Reserved)
                          AESLANG_SPANISH   4      Spanish
                          AESLANG_ITALIAN   5      Italian
                          AESLANG_SWEDISH   6      Swedish

                    out2, out3, and out4 are unused.

AES_PROCESS    4    AES Multiple Process Support
                    out1 is 0 to indicate the use of
                         non-pre-emptive multitasking and 1 to
                         indicate the use of pre-emptive
                         multitasking.
                    out2 is 0 if appl_find() cannot
                         convert between MiNT and AES id's and
                         1 to indicate that it can.
                    out3 is 0 if appl_search() is not
                         implemented and 1 if it is.
                    out4 is 0 if rsrc_rcfix() is not
                         implemented and 1 if it is.

AES_PCGEM       5    AES PC-GEM Features
                    out1 is 0 if objc_xfind() is not
                         implemented and 1 if it is.
                    out2 is currently reserved.
                    out3 is 0 if menu_click() is not
                         implemented and 1 if it is.
                    out4 is 0 if shel_rdef() and
                         shel_wdef() are not implemented and
                         1 if they are.

AES_INQUIRE    6    AES Extended Inquiry Functions
                    out1 is 0 if -1 is not a valid
                         ap_id parameter to appl_read() or 1
                         if it is.
                    out2 is 0 if -1 is not a valid
                         length parameter to shel_get() or 1
                         if it is.
                    out3 is 0 if -1 is not a valid
                         mode parameter to menu_bar() or 1
                         if it is.
                    out4 is 0 if MENU_INSTL is not
                         a valid mode parameter to menu_bar()
                         or 1 if it is.

(reserved)      7    Currently reserved.

AES_MOUSE       8    AES Mouse Support
                    out1 is 0 to indicate that mode
                         parameters of 258-260 are not
                         supported by graf_mouse() and 1
                         if they are.
                    out2 is 0 to indicate that the
                         application has control over the
                         mouse form and 1 to indicate that
                         the mouse form is maintained by
                         the AES on a per-application basis.
                    out3 and ap_gout4 are currently
                         unused.

AES_MENU       9    AES Menu Support
                    out1 is 0 to indicate that
                         sub-menus are not supported and 1
                         if MultiTOS style sub-menus are.
                    out2 is 0 to indicate that popup
                         menus are not supported and 1 if
                         MultiTOS style popup menus are.
                    out3 is 0 to indicate that
                         scrollable menus are not supported
                         and 1 if MultiTOS style scrollable
                         menus are.
                    out4 is 0 to indicate that the
                         MN_SELECTED message does not contain
                         object tree information in msg[57]
                         and 1 to indicate that it does.

AES_SHELL       10    AES Shell Support
                    out1 & 0x00FF indicates the
                         highest legal value for the
                         mode parameter of shel_write().
                    out1 & 0xFF00 indicate which
                         extended shel_write() mode bits
                         are supported.
                    out2 is 0 if shel_write() with
                         a mode parameter of 0 launches
                         an application or 1 if it cancels
                         the previous shel_write().
                    out3 is 0 if shel_write() with
                         a mode parameter of 1 launches an
                         application immediately or 1 if
                         it takes effect when the current
                         application exits.
                    out4 is 0 if ARGV style parameter
                         passing is not supported or
                         1 if it is.

AES_WINDOW     11    AES Window Features
                    out1 is a bitmap of extended modes
                         supported by wind_get() and
                         wind_set() (if a bit is set, it is
                         supported) as follows:
                         Bit  mode
                          0   WF_TOP returns window below the
                               top also.
                          1   wind_get( WF_NEWDESK, ... )
                               supported.
                          2   WF_COLOR get/set.
                          3   WF_DCOLOR get/set.
                          4   WF_OWNER get/set.
                          5   WF_BEVENT get/set.
                          6   WF_BOTTOM set.
                          7   WF_ICONIFY set.
                          8   WF_UNICONIFY set.
                         9-15 Unused

                    out2 is current unused.
                    out3 is a bitmap of supported
                         window behaviors (if a bit is set,
                         it is supported) as follows:

                         Bit   Behaviour
                          0    Iconifier gadget present.
                          1    Bottomer gadget present.
                          2    shift-click sends window
                               to bottom.
                          3    "hot" close box supported.
                         4-15  Unused

                    out4 is currently unused.

AES_MESSAGE    12    AES Extended Messages
                    out1 is a bitmap of extra messages
                         supported (if a bit is set, it is
                         supported) as follows:
                          Bit   Message
                          0     WM_NEWTOP is meaningful.
                          1     WM_UNTOPPED is sent.
                          2     WM_ONTOP is sent.
                          3     AP_TERM is sent.
                          4     Shutdown and resolution
                                change messages.
                          5     CH_EXIT is sent.
                          6     WM_BOTTOMED is sent.
                          7     WM_ICONIFY is sent.
                          8     WM_UNICONIFY is sent.
                          9     WM_ALLICONIFY is sent.
                          10-15 Unused

                    out2 is a bitmap of extra messages
                         supported. Current all bits are
                         unused.
                    out3 is a bitmap indicating
                         message behaviour (if a bit is set,
                         the behaviour exists) as follows:
                         Bit  Message
                          0   WM_ICONIFY message gives
                              coordinates.
                         1-15 Unused

                    out4 is currently unused.

AES_OBJECT     13    AES Extended Objects
                    out1 is 0 if 3D objects are not
                         supported or 1 if they are.
                    out2 is 0 if objc_sysvar() is not
                         present, 1 if MultiTOS v1.01
                         objc_sysvar() is present, or 2
                         if extended objc_sysvar()
                         is present.
                    out3 is 0 if the system font is
                         the only font supported or 1 if
                         GDOS fonts are also supported.
                    out4 is reserved for OS
                         extensions.

AES_FORM       14    AES Form Support
                    out1 is 0 if 'flying dialogs' are
                         not supported or 1 if they are.
                    out2 is 0 if keyboard tables are
                         not supported or 1 if Mag!X style
                         keyboard tables are supported.
                    out3 is 0 if the last cursor
                         position from objc_edit() is not
                         returned or 1 if it is.
                    out4 is currently reserved.
\endverbatim
 *  @param global_aes global AES array
 *
 *  @return 0 if an error occurred or non-zero otherwise.
 *
 *  @since Available as of AES version 4.00.
 *
 *  @sa mt_appl_init()
 *
 *  Using an ap_gtype value of 4 and above is only supported as
 *  of AES version 4.1
 *
 *  Many of the ap_gtype return values identify features of TOS
 *  not supported by Atari but for the benefit of third-party
 *  vendors. You should contact the appropriate third-party for
 *  documentation on these functions.
 *
 *  @note
 *  If mt_appl_getinfo() is not implemented (gl_ap_version < 0X0401 and the
 *  application "?AGI\0\0\0\0" (Winx) is not found), the trap is not performed
 *  (may crash on some system).
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

	*out1 = aes_intout[1];
	*out2 = aes_intout[2];
	*out3 = aes_intout[3];
	*out4 = aes_intout[4];

	return (aes_intout[0]);
}

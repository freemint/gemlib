/*
 *  $Id$
 */

#include "gem_aesP.h"

/** displays a standardized alert box and returns
 *  the user's selection.
 *
 *  @param default_button contains the number of the exit button which is to
 *               be made default (1-3)
 *  @param alert_string contains a formatted string
 *               as follows:
 *                              "[#][Alert Text][Buttons]".
 *               \n\n
 *               # specifies the icon to display in the alert as follows:
 *               - 0       No Icon
 *               - 1       Exclamation Icon
 *               - 2       Question Icon
 *               - 3       Stop Icon
 *               - 4       Info Icon
 *               - 5       Disk Icon
 *               \n\n
 *               'Alert Text' is a text string of as many as 5 lines composed
 *               of up to 30 characters each. Each line is separated by a '|'
 *               character.
 *               \n\n
 *               'Buttons' is a text string to define as many as 3 buttons
 *               up to 10 characters each. If only one button is used, its
 *               text may be as long as 30 characters. Again, each button is
 *               separated by a '|' character
 *
 *  @param global_aes global AES array
 *
 *  @return WORD indicating which button was used
 *               to exit by the user (A possible value of 1-3).
 *
 *  @since All AES versions. Icons #4-5 are only available as of AES
 *               version 4.1.
 *
 *  Several versions of the AES have special quirks related to
 *  this function. By following the quidelines below you should
 *  avoid any difficulty:
 *  1. All AES versions below 1.06 have some difficulty
 *     formatting alert strings padded with spaces.
 *     If you want your alerts to look right on all AES versions,
 *     do not pad any button or line with spaces with the
 *     exception below.
 *  2. Add one space to the end of the longest text line on an
 *     alert. This will prevent the right edge from touching the
 *     border in some AES versions.
 *
 */

short
mt_form_alert(short default_button, const char *alert_string, short *global_aes)
{
	AES_PARAMS(52,1,1,1,0);

	aes_intin[0] = default_button;
	aes_addrin[0] = (long)alert_string;

	AES_TRAP(aes_params);

	return aes_intout[0];
}

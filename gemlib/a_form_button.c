/*
 *  $Id$
 */

#include "gem_aesP.h"

/** is a utility function designed to aid in the
 *  creation of a custom mt_form_do() handler.
 *
 *  @param tree is a pointer to a valid object tree in memory you wish
 *               to process button events for.
 *  @param object is the object index into
 *               tree which was clicked on and which needs to be processed.
 *  @param clicks is the number of times the mouse button needs to be
 *               clicked.
 *  @param nextobj the next object to gain edit focus or 0 if
 *               there are no editable objects. If the top bit of \a nextobj is
 *               set, this indicates that a #OF_TOUCHEXIT object was
 *               double-clicked. \n
 *             [option CHECK_NULLPTR] \a nextobj may be NULL
 *  @param global_aes global AES array
 *
 *  @return 0 if it exits finding an #OF_EXIT or
 *               #OF_TOUCHEXIT object selected or 1 otherwise.
 *
 *  @since All AES versions.
 *
 *  @sa mt_form_do(), mt_form_keybd()
 *
 *  To use this function properly, the application should take
 *  the following steps:
 *    -# Monitor mouse clicks with mt_evnt_multi() or mt_evnt_button().
 *    -# When a click occurs, use mt_objc_find() to determine if
 *       the click occurred over the object.
 *    -# If so, call mt_form_button() with the appropriate
 *       values.
 *
 *  @note This function was not originally documented by Atari.
 *
 */

short
mt_form_button(OBJECT *tree, short object, short clicks, short *nextobj, short *global_aes)
{
	AES_PARAMS(56,2,2,1,0);

	aes_addrin[0] = (long)tree;
	aes_intin[0] = object;
	aes_intin[1] = clicks;

	AES_TRAP(aes_params);

#if CHECK_NULLPTR
	if (nextobj)
#endif
	*nextobj = aes_intout[1];

	return aes_intout[0];
}

#include "gem_aesP.h"
#include "mt_gemx.h"

/** Service file selector window
 *
 *  @param fsd Descriptor that was passed at a successful
 *         opening of a file selector 
 *         window.
 *  @param events EVENT structure as for wdlg_evnt and
 *		   fnts_evnt. The events are serviced by
 *		   the dialog if they are intended for the
 *		   associated window.
 *  @param path Pointer to the selected path if the 
 *		   dialog was quit successfully, i.e. by a
 *		   click on the OK button or by double-
 *		   clicking on a file.
 *  @param fname Pointer to the selected filename if the 
 *		   dialog was quit successfully, i.e. by a
 *		   click on the OK button or by double-
 *		   clicking on a file.
 *  @param button  \n
 *             [option CHECK_NULLPTR] button may be NULL
 *  @param nfiles  \n
 *             [option CHECK_NULLPTR] nfiles may be NULL
 *  @param sort_mode  \n
 *             [option CHECK_NULLPTR] sort_mode may be NULL
 *  @param pattern  \n
 *             [option CHECK_NULLPTR] pattern may be NULL
 *  @param global_aes global AES array
 *
 *  @return Is 0 if the dialog is to be quit, else 1
 *
 *  @since mt_appl_getinfo(7) give informations on mt_fslx_xx() functions availability
 *
 *  Events, i.e. mouse clicks, messages and keypresses are passed on to the 
 *  file selector window and serviced by it if appropriate. When an event 
 *  has been serviced then the corresponding bit in the EVENT structure will 
 *  be cleared.
 *
 */

short 
mt_fslx_evnt(void *fsd, EVNT *events, char *path, char *fname, short *button, 
			 short *nfiles, short *sort_mode, char **pattern, short *global_aes)
{
	AES_PARAMS(193,0,4,4,1);

	aes_addrin[0] = (long)fsd;
	aes_addrin[1] = (long)events;
	aes_addrin[2] = (long)path;
	aes_addrin[3] = (long)fname;

	AES_TRAP(aes_params);

#if CHECK_NULLPTR
	if (button)
#endif
	*button = aes_intout[1];
#if CHECK_NULLPTR
	if (nfiles)
#endif
	*nfiles = aes_intout[2];
#if CHECK_NULLPTR
	if (sort_mode)
#endif
	*sort_mode = aes_intout[3];
#if CHECK_NULLPTR
	if (pattern)
#endif
	*pattern = (char *)aes_addrout[0];
	
	return aes_intout[0];
}

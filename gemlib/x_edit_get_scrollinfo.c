/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** Examine settings: Scroll information
 *
 *  @param tree RSC-tree of object
 *  @param obj Object number
 *  @param nlines will be filled with the Number of lines in text \p
 *         [option CHECK_NULLPTR] nlines may be NULL
 *  @param yscroll will be filled with the First visible line \p
 *         [option CHECK_NULLPTR] yscroll may be NULL
 *  @param yvis will be filled with the Number of max. visible lines \p
 *         [option CHECK_NULLPTR] yvis may be NULL
 *  @param yval will be filled with the Number of currently visible lines \p
 *         [option CHECK_NULLPTR] yval may be NULL
 *  @param ncols will be filled with the Number of columns, or -1 (unknown) \p
 *         [option CHECK_NULLPTR] ncols may be NULL
 *  @param xscroll will be filled with the Horiz. scroll offset in pixels \p
 *         [option CHECK_NULLPTR] xscroll may be NULL
 *  @param xvis will be filled with the Number of visible columns (in pixels) \p
 *         [option CHECK_NULLPTR] xvis may be NULL
 *  @param global_aes global AES array
 *
 *  @since from MagiC 5.20 onwards. As it is 
 *         implemented as part of the shared library (SLB or SharedLib), 
 *         one only needs to open the library with:\n
 *         <pre>Slbopen("EDITOBJC.SLB", NULL, 0L, &slb, &slbexec);</pre>
 *         The library installs a new AES object-type G_EDIT (37)
 *         as well as the AES functions mt_edit_xx().
 *
 *  This information is required in order to set the horizontal and vertical 
 *  scroll bars. As the editable object would have to make a vq_extend() for 
 *  each individual line, actually at each alteration of a line, the number 
 *  of columns is currently not defined and the call returns -1.
 *  MGEDIT here simply assumes a fixed width, in the same way as other programs 
 *  e.g. VIEW.PRG and PC.PRG do as well.
 *  \p yval is always smaller or equal to \p yvis. If the text has fewer lines 
 *  that \p yvis, then \p yval is always smaller.
 *
 */

void 
mt_edit_get_scrollinfo( OBJECT *tree, short obj, long *nlines, long *yscroll,
                        short *yvis, short *yval,short *ncols, short *xscroll, short *xvis,
					    short *global_aes )
{
	AES_PARAMS(216,2,10,1,0);

	aes_intin[0]  = obj;
	aes_intin[1]  = 9;
	aes_addrin[0] = (long)tree;

	AES_TRAP(aes_params);

#if CHECK_NULLPTR
	if (nlines)
#endif
	*nlines = *((long *) (aes_intout+1));
#if CHECK_NULLPTR
	if (yscroll)
#endif
	*yscroll = *((long *) (aes_intout+3));
#if CHECK_NULLPTR
	if (yvis)
#endif
	*yvis = aes_intout[5];
#if CHECK_NULLPTR
	if (yval)
#endif
	*yval = aes_intout[6];
#if CHECK_NULLPTR
	if (ncols)
#endif
	*ncols = aes_intout[7];
#if CHECK_NULLPTR
	if (xscroll)
#endif
	*xscroll = aes_intout[8];
#if CHECK_NULLPTR
	if (xvis)
#endif
	*xvis = aes_intout[9];
}


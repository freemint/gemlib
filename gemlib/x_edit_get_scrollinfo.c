/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** Examine settings: Scroll information
 *
 *  @param tree RSC-tree of object
 *  @param obj Object number
 *  @param nlines will be filled with the Number of lines in text
 *  @param yscroll will be filled with the First visible line
 *  @param yvis will be filled with the Number of max. visible lines
 *  @param yval will be filled with the Number of currently visible lines
 *  @param ncols will be filled with the Number of columns, or -1 (unknown)
 *  @param xscroll will be filled with the Horiz. scroll offset in pixels
 *  @param xvis will be filled with the Number of visible columns (in pixels)
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
	AES_PARAMS(216,2,6,1,0);

	aes_intin[0]  = obj;
	aes_intin[1]  = 9;
	aes_addrin[0] = (long)tree;

	AES_TRAP(aes_params);

	*nlines = *((long *) (aes_intout+1));
	*yscroll = *((long *) (aes_intout+3));
	*yvis = aes_intout[5];
	*yval = aes_intout[6];
	*ncols = aes_intout[7];
	*xscroll = aes_intout[8];
	*xvis = aes_intout[9];
}


#include "gem_aesP.h"
#include "mt_gemx.h"

/** Alter settings: Formating
 *
 *  @param tree RSC-tree of object
 *  @param obj Object number
 *  @param tabwidth specifies the tabulator width in pixels, or -1.
 *  @param autowrap specifies the auto wrapping feature as follow:
 *         - -1: Do not change
 *         - >0: Pixel width for auto line wrap (generally == object width)
 *         - =0: No wrapping, but horiz. scrolling
 *  @param global_aes global AES array
 *
 *  @since from MagiC 5.20 onwards. As it is 
 *         implemented as part of the shared library (SLB or SharedLib), 
 *         one only needs to open the library with:\n
 *         <pre>Slbopen("EDITOBJC.SLB", NULL, 0L, &slb, &slbexec);</pre>
 *         The library installs a new AES object-type G_EDIT (37)
 *         as well as the AES functions mt_edit_xx().
 *
 *  If one of the two attributes is to remain unchanged then -1 can be passed.
 *  If the editable object was opened previously then one should generally 
 *  trigger a redraw when changing one of the attributes. From version 9 of 
 *  the SLB the number of lines is recalculated when the \p autowrap setting 
 *  is altered. In older versions this only happens with mt_edit_set_buf().
 *
 */

void 
mt_edit_set_format( OBJECT *tree, short obj, short tabwidth, short autowrap,
                    short *global_aes )
{
	AES_PARAMS(217,4,0,1,0);
	
	aes_intin[0]  = obj;
	aes_intin[1]  = 1;
	aes_intin[2]  = tabwidth;
	aes_intin[3]  = autowrap;
	aes_addrin[0] = (long)tree;

	AES_TRAP(aes_params);
}

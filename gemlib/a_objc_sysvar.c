/*
 *  $Id$
 */

#include "gem_aesP.h"

/** returns/modifies information about the color
 *  and placement of 3D object effects.
 *
 *  @param mode determines whether attributes should be read or
 *         modified. A value of SV_INQUIRE (0) will read the current
 *         values whereas a value of SV_SET (1) will modify the
 *         current values.
 *  @param which determines what attribute you wish to
 *         read or modify.
 *  @param in1 specifies the 1st new value when modifying values, unused otherwise.
 *  @param in2 specifies the 2nd new value when modifying values, unused otherwise.
 *  @param out1 will be filled by the 1st value when reading value, unused otherwise.
 *  @param out2 will be filled by the 2st value when reading value, unused otherwise. \p
 *          Here is the meanings of the two input/output values referred to as
 *          \p val1 and \p val2 are as follows:\p
 *          - LK3DIND (1) :   If \p val1 is 1, the text of indicator objects
 *                            does move when selected, otherwise, if 0,
 *                            it does not.
 *                            If \p val2 is 1, the color of indicator
 *                            objects does change when selected,
 *                            otherwise, if 0, it does not.
 *          - LK3DACT (2) :   Same as LK3DIND for activator objects.
 *          - INDBUTCOL (3) : \p val1 specifies the default color for
 *                            indicator objects. \p val2 is unused.
 *          - ACTBUTCOL (4) : \p val1 specifies the default color for
 *                            activator objects. \p val2 is unused.
 *          - BACKGRCOL (5) : \p val1 specifies the default color for
 *                            background objects. \p val2 is unused.
 *          - AD3DVAL (6) :   \p val1 specifies the number of extra pixels on
 *                            each horizontal side of an indicator or
 *                            activator object needed to accomodate 3D
 *                            effects.
 *                            \p val2 specifies the number of extra pixels
 *                            on each vertical side of an indicator or
 *                            activator object needed to accomodate 3D
 *                            effects.
 *                            This setting may only be read, not
 *                            modified.
 *  @param global_aes global AES array
 *
 *  @return 0 if an error occurred or non-zero otherwise.
 *
 *  @since All AES versions.
 *
 *  Applications should not use mt_objc_sysvar() to change these
 *  settings since all changes are global. Only CPXs or Desk
 *  Accessories designed to modify these parameters should.
 *
 */
 
short 
mt_objc_sysvar(short mode, short which, short in1, short in2,
               short *out1, short *out2, short *global_aes)
{
	AES_PARAMS(48,4,3,0,0);
                    
	aes_intin[0] = mode;
	aes_intin[1] = which;
	aes_intin[2] = in1;
	aes_intin[3] = in2;

	AES_TRAP(aes_params);

	*out1 = aes_intout[1];
	*out2 = aes_intout[2];
	
	return aes_intout[0];
}

#ifdef objc_sysvar
#undef objc_sysvar
#endif
short 
objc_sysvar(short mode, short which, short in1, short in2,
            short *out1, short *out2)
{
	return(mt_objc_sysvar(mode, which, in1, in2, out1, out2, aes_global));
}


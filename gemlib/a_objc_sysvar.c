/*
 *  $Id$
 */

#include "gem_aesP.h"

/** returns/modifies information about the color
 *  and placement of 3D object effects.
 *
 *  @param mode determines whether attributes should be read or
 *         modified. A value of #SV_INQUIRE (0) will read the current
 *         values whereas a value of #SV_SET (1) will modify the
 *         current values.
 *  @param which determines what attribute you wish to
 *         read or modify. see the table below.
 *  @param in1 specifies the 1st new value when modifying values, unused otherwise.
 *  @param in2 specifies the 2nd new value when modifying values, unused otherwise.
 *  @param out1 will be filled by the 1st value when reading value, unused otherwise. \n
 *         [option CHECK_NULLPTR] \a out1 may be NULL
 *  @param out2 will be filled by the 2st value when reading value, unused otherwise. \n
 *         [option CHECK_NULLPTR] \a out2 may be NULL \n
 *  @param global_aes global AES array
 *
 *  @return 0 if an error occurred or non-zero otherwise.
 *
 *  @since mt_appl_getinfo() with mode #AES_OBJECT gives the availability of this function.
 *
 *  <table>
 *  <tr><td>\a which <td> \a in1 / \a out1 <td> \a in2 / \a out2
 *  <tr><td>#LK3DIND (1)   <td>  If 1, the text of indicator objects
 *                               does move when selected, otherwise, if 0,
 *                               it does not.
 *                         <td>  If 1, the color of indicator
 *                               objects does change when selected,
 *                               otherwise, if 0, it does not.
 *  <tr><td>#LK3DACT (2)   <td>  Same as #LK3DIND for activator objects.
 *                         <td>  Same as #LK3DIND for activator objects.
 *  <tr><td>#INDBUTCOL (3) <td>  specifies the default color for
 *                               indicator objects.
 *                         <td>  unused.
 *  <tr><td>#ACTBUTCOL (4) <td>  specifies the default color for
 *                               activator objects.
 *                         <td>  unused.
 *  <tr><td>#BACKGRCOL (5) <td>  specifies the default color for
 *                               background objects.
 *                         <td>  unused.
 *  <tr><td>#AD3DVAL (6)   <td>  specifies the number of extra pixels on
 *                               each horizontal side of an indicator or
 *                               activator object needed to accomodate 3D
 *                               effects. This setting may only be read, not
 *                               modified.
 *                         <td>  specifies the number of extra pixels
 *                               on each vertical side of an indicator or
 *                               activator object needed to accomodate 3D
 *                               effects.
 *                               This setting may only be read, not
 *                               modified.
 *  <tr><td>#MX_ENABLE3D (10) <td> If 1, the 3D look is enabled. Set to 0 to disable
 *                                 the 3D-look.\n (Since MagiC 3)
 *                            <td> set to 0 to disable the 3D look \n (Since MagiC 3)
 *  <tr><td>#MENUCOL (11)  <td>  TO BE COMPLETED (TODO)
 *                         <td>  TO BE COMPLETED (TODO)
 *  </table>
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

#if CHECK_NULLPTR
	if (out1)
#endif
	*out1 = aes_intout[1];
#if CHECK_NULLPTR
	if (out2)
#endif
	*out2 = aes_intout[2];
	
	return aes_intout[0];
}

/*
 *  $Id$
 */

#include "gem_aesP.h"

/** Can be used to control the activity of applications.
 *
 *  @param ap_cid the AES ID (apid) of the application you want to control.
 *  @param ap_cwhat the type of control:
 *         - \p 0..9 : Reserved for N.AES
 *         - \p APC_HIDE (10): Hide (fade out) application. 
 *           If \p ap_cid is -1, the active application will be hidden.
 *         - \p APC_SHOW (11): Show (fade in) application.
 *           If \p ap_cid is -1, all hidden applications are shown.
 *         - \p APC_TOP (12): Bring application to front (the application
 *           becomes the active one).
 *         - \p APC_HIDENOT (13): Hide all applications except the one referred
 *           to by ap_cid (which becomes the active application).
 *           If ap_cid is -1, all applications except the active one will be
 *           hidden.
 *  @param ap_cout is filled by the AES dependent on ap_cwhat (currently unused, set
 *         it to NULL).
 *  @param global_aes global AES array
 *
 *  @return 0 if an error has occurred or a value>0 otherwise.
 *
 *  @since N.AES
 *
 *  @sa SM_M_SPECIAL
 *
 *  Hidden application have a '*' placed in front of their names in
 *  the applications menu, unless they did not have a window open during
 *  hiding. If the latter is the case only the active application is
 *  changed.
 *
 *  So the '*' in front of the name means: One ore more windows of
 *  this application are hidden.
 */

short
mt_appl_control(short ap_cid, short ap_cwhat, void *ap_cout, short *global_aes)
{
	AES_PARAMS(129,2,1,1,0);

	aes_intin[0]  = ap_cid;
	aes_intin[1]  = ap_cwhat;
	aes_addrin[0] = (long)ap_cout;

	AES_TRAP(aes_params);

	return aes_intout[0];
}

#ifdef appl_control
#undef appl_control
#endif
short
appl_control(short ap_cid, short ap_cwhat, void *ap_cout)
{
	return(mt_appl_control(ap_cid,ap_cwhat,ap_cout, aes_global));
}

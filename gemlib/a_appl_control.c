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
 *         - \p APC_INFO (14): Get the application parameter of the application
 *           \p ap_cid. If \p ap_cid is set to -1, the parameters of the active
 *           application are returned. \p ap_cout must  point to a short variable.
 *           This variable is a bitmap variable:
 *           - \p APCI_HIDDEN (1) : bit 0 is set if the application is hidden
 *           - \p APCI_HASMBAR (2) : bit 1 is set if the application has a menu bar
 *           - \p APCI_HASDESK (4) : bit 2 is set if the application has a own desk
 *         - \p APC_MENU(15): The last used menu tree is returned. The parameter
 *           \p ap_cout is a pointer to an pointer of OBJECT. The AES fills in the
 *           address of the menu tree. If \p ap_cid is set to -1, the address of the
 *           menu tree of the active application is returned. If \p ap_cid is set to
 *           0 the address of the system menu (AES internally) is returned.
 *           If the wanted application has no menu bar or if the wanted
 *           application doesn't exist, a NULL-pointer is returned in \p *ap_cout.
 *           The return value always equals 1. \n
 *           Hint: the developer must know what he does! The changing of the tree can
 *           result in undefined system states. If MiNT memory protection is active, a read
 *           of the menu bar can result in an violation and terminate the application!
 *         - \p APC_WIDGETS(16): This mode inquires or sets the 'default' positions of the
 *           window widgets. \p ap_cout is a pointer to buffer of size of MINWINOB (=12)
 *           WORDs. For inquiring the OBJECT order this buffer must be filled completly with -1.
 *           The last WORD must equal 0! If an error is returned the buffer is not large
 *           enough for all objects and should be enlarged. In the buffer the objects are
 *           contained in the following order: first the title bar from the left to the right,
 *           the objects of the vertical slider from top to bottom, the objects of the
 *           horizontal sloder from the left to the right. The list is
 *           terminated with a 0 WORD. For setting the positions, the
 *           first objects must be of the type topwidgets (from the left
 *           to the right), the next objects of the type right widgets
 *           (from top to bottom) and the last objects of the type
 *           bottom widgets (from the left to the right). If objects are
 *           set doubly or wrong, an error is returned.
 *
 *  @param ap_cout is filled by the AES dependent on ap_cwhat.
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

/*
 *  $Id$
 */

#include "gem_aesP.h"

/** Can be used to control the activity of applications.
 *
 *  @param ap_cid the AES ID (apid) of the application you want to control.
 *  @param ap_cwhat the type of control (refer to the table below)
 *  @param ap_cout is filled by the AES dependent on \a ap_cwhat.
 *  @param global_aes global AES array
 *
 *  @return 0 if an error has occurred or a value>0 otherwise.
 *
 *  @since N.AES
 *
 *  @sa #SM_M_SPECIAL
 *
 *  The table hereafter summaries the action performed by mt_appl_control()
 *  depending on the value given in \a ap_cwhat.
 *
 *	<table>
 *	<tr><td> <b>Values of \a ap_cwhat</b> <td> \b Description
 *	<tr><td> 0..9	   <td> Reserved for N.AES
 *	<tr><td> #APC_HIDE <td> Hide (fade out) application.
 *	If \a ap_cid is -1, the active application will be hidden.
 *	<tr><td> #APC_SHOW <td> Show (fade in) application.
 *	  If \a ap_cid is -1, all hidden applications are shown.
 *	<tr><td> #APC_TOP  <td> Bring application to front (the application
 *	  becomes the active one).
 *	<tr><td> #APC_HIDENOT <td> Hide all applications except the one referred
 *	  to by \a ap_cid (which becomes the active application).
 *	  If ap_cid is -1, all applications except the active one will be
 *	  hidden.
 *	<tr><td> #APC_INFO <td> Get the application parameter of the application
 *	  \a ap_cid. If \a ap_cid is set to -1, the parameters of the active
 *	  application are returned. \a ap_cout must  point to a short variable.
 *	  This variable is a bitmap variable:
 *	  - \p #APCI_HIDDEN  is set if the application is hidden
 *	  - \p #APCI_HASMBAR  is set if the application has a menu bar
 *	  - \p #APCI_HASDESK  is set if the application has a own desk
 *	<tr><td> #APC_MENU <td> The last used menu tree is returned. The parameter
 *	  \a ap_cout is a pointer to an pointer of ::OBJECT. The AES fills in the
 *	  address of the menu tree. If \a ap_cid is set to -1, the address of the
 *	  menu tree of the active application is returned. If \a ap_cid is set to
 *	  0 the address of the system menu (AES internally) is returned.
 *	  If the wanted application has no menu bar or if the wanted
 *	  application doesn't exist, a NULL-pointer is returned in \a *ap_cout.
 *	  The return value always equals 1. \n
 *	  Hint: the developer must know what he does! The changing of the tree can
 *	  result in undefined system states. If MiNT memory protection is active, a read
 *	  of the menu bar can result in an violation and terminate the application!
 *	<tr><td> #APC_WIDGETS <td> This mode inquires or sets the 'default' positions of the
 *	  window widgets. \a ap_cout is a pointer to buffer of size of MINWINOB (=12)
 *	  short integers (16 bits). For inquiring the ::OBJECT order this buffer must be filled completly with -1.
 *	  The last \c short must equal 0! If an error is returned the buffer is not large
 *	  enough for all objects and should be enlarged. In the buffer the objects are
 *	  contained in the following order: first the title bar from the left to the right,
 *	  the objects of the vertical slider from top to bottom, the objects of the
 *	  horizontal sloder from the left to the right. The list is
 *	  terminated with a 0 \c short. For setting the positions, the
 *	  first objects must be of the type topwidgets (from the left
 *	  to the right), the next objects of the type right widgets
 *	  (from top to bottom) and the last objects of the type
 *	  bottom widgets (from the left to the right). If objects are
 *	  set doubly or wrong, an error is returned.
 *      <tr><td> #APC_APP_CONFIG <td> With this option you are able to inform to AES how you want your application should be considered.
 *	  \a ap_cout is a pointer to a string. At this time value supported are:
 *	  - \p "app_debug=true" or "app_debug" : put the application in debug mode
 *	  - \p "app_debug=false" : stop debug mode
 *	  - \p "app_topmost=true" or "app_topmost" : Application windows will be always on top (compare to other classical application) but without focus (can be usefull for tesk bar for exemple)
 *	  - \p "app_topmost=false" : remove previous option
 *	  - \p "app_system" : application is a system application (used in appl_search() for type APP_SYSTEM)
 *	  - \p "app_texticon=opaque" : background icon text is opaque
 *	  - \p "app_texticon=transparent" : background icon text is transparent
 *	  - \p "app_signal_mesag=true": Request receive Unix Signal when even message is waiting see APC_INFORM_MESAG as it do exactly the same
 *	  - \p "app_signal_mesag=false": Request stop receive Unix Signal when even message is waiting
 *	  appl_control return 1 if the request is recognize else 0
 *      <tr><td> #APC_INFORM_MESAG <td> Request to AES to inform the application when there 
 *	  is a AES message waiting with a Unix Signal. \a ap_cout : not used.
 *	  When the application receive a message the AES send the Signal SIGUSR2 (30) to the application, 
 *        to manage the message should use classical event_mesag() or event_multi() functions.
 *	  Calling one time this call request to AES to send Signal, calling a second time remove this order.
 *	  appl_control return 1 if take into account else 0 
 *	</table>
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

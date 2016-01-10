/*
 *  $Id$
 */

/* This file just contains some documentation for doxygen,
   nothing to be compiled here */

/** @defgroup AES AES  Function Reference
 *  @{
 */

/** @defgroup a_appl Application Services Library
 *
 *  @brief initialization and interprocess communication
 *
 *  The Application Services Library provides general use functions used in
 *  locating and working with other resident applications in addition to
 *  providing AES initialization and termination code.
 */


/** @defgroup a_evnt Event Library
 *
 *  @brief wait for user response
 *
 *  The Event Library consists of a group of system calls which are used to
 *  monitor system messages including mouse clicks, keyboard usage, menu bar
 *  interaction, timer calls, and mouse tracking.
 */

/** @defgroup a_form Form Library
 *
 *  @brief user interaction with dialogs & error messages
 *
 *  The Form Library contains utility functions for the use and control of
 *  dialog boxes, alert boxes, and user input.
 */

/** @defgroup a_fsel File Selector Library
 *
 *  @brief standard file selector
 *
 *  The File Selector Library contains two functions for displaying the
 *  system file selector (or currently installed alternate file selector) and
 *  prompting the user to select a file.
 */

/** @defgroup a_graf Graphics Library
 *
 *  @brief special mouse functions
 *
 *  The Graphics Library provides applications with a variety of utility
 *  functions which serve to provide common screen effects, mouse control, and
 *  the obtaining of basic screen attributes.
 */

/** @defgroup a_menu Menu Library
 *
 *  @brief create or modify drop-down menu
 *
 *  The Menu Library assists in the handling of system menu bars and popup
 *  menus. In addition, individual control of menu items can also be handled
 *  through these functions.
 */

/** @defgroup a_objc Object Library
 *
 *  @brief display or modify object trees
 *
 *  The Object Library is responsible for the drawing and manipulation of AES
 *  objects such as boxes, strings, icons, etc. See earlier in this chapter
 *  for a complete discussion of AES objects.
 */

/** @defgroup a_rsrc Resource Library
 *
 *  @brief resource files
 *
 *  The Resource Library is responsibe for the loading/unloading of resource
 *  files and the manipulation of resource objects in memory.
 */

/** @defgroup a_scrp Scrap Library
 *
 *  @brief interprocess cut & paste operations
 *
 *  The Scrap Library is used to maintain the location of the clipboard
 *  directory used for interprocess data exchange.
 */

/** @defgroup a_shel Shell Library
 *
 *  @brief AES shell functions
 *
 *  The Shell Library contains several miscellaneous functions most often
 *  used by the GEM Desktop and other 'Desktop-like' applications. Other
 *  applications may, however, need specific functions of the Shell Library
 *  for various tasks.
 */

/** @defgroup a_wind Window Library
 *
 *  @brief window frame interface
 *
 *  The Window Library is responsible for the displaying and maintenance of
 *  AES windows.
 */

/** @defgroup a_util Utility Library
 *
 *  @brief some usefull utilities function. This library doesn't contain
 *         any AES call.
 *
 */

/** @defgroup x_wdlg MagiC extension: Window Dialog
 *
 *  @brief AES extended dialog in window
 *
 *  TODO
 */

/** @defgroup x_edit MagiC extension: Edit Library
 *
 *  @brief AES extended edit functions
 *
 *  This Edit Library is available from MagiC 5.20 onwards. As it is 
 *  implemented as part of the shared library (SLB or SharedLib), 
 *  one only needs to open the library with:\n
 *  <pre>Slbopen("EDITOBJC.SLB", NULL, 0L, &slb, &slbexec);</pre>
 *  The library installs a new AES object-type G_EDIT (37)
 *  as well as the AES functions mt_edit_xx().
 */

/** @defgroup x_fnts MagiC/WDIALOG extension: Font selector Library
 *
 *  @brief font selector functions
 *
 *  This Font Selector library availability can be found calling
 *  mt_appl_getinfo(7). Bit 2 of \p ap_gout1, if equal to 1,
 *  says that mt_fnts_xx() functions are available.
 */

/** @defgroup x_fslx MagiC/WDIALOG extension: File selector Library
 *
 *  @brief file selector functions
 *
 *  This File Selector library availability can be found calling
 *  mt_appl_getinfo(7). Bit 3 of \p ap_gout1, if equal to 1,
 *  says that mt_flsx_xx() functions are available.
 */

/** @defgroup x_lbox MagiC/WDIALOG extension: List Box Library
 *
 *  @brief list box functions
 *
 *  This List Box library availability can be found calling
 *  mt_appl_getinfo(7). Bit 1 of \p ap_gout1, if equal to 1,
 *  says that mt_lbox_xx() functions are available.
 */

/** @defgroup x_pdlg MagiC/WDIALOG extension: Printer Dialog Library
 *
 *  @brief printer dialog functions
 *
 *  This Printer Dialog library availability can be found calling
 *  mt_appl_getinfo(7). Bit 4 of \p ap_gout1, if equal to 1,
 *  says that mt_pdlg_xx() functions are available.
 */

/**@}*/

/** @defgroup VDI VDI  Function Reference
 *  @{
 */

/** @defgroup v_attr VDI attribute functions
 *
 *  @brief attribute functions
 *
 *  todo: add description here
 */

/** @defgroup v_ctrl VDI control functions
 *
 *  @brief control functions
 *
 *  todo: add description here
 */

/** @defgroup v_escp VDI escape functions
 *
 *  @brief escapes functions
 *
 *  todo: add description here
 */

/** @defgroup v_inqr VDI inquiry functions
 *
 *  @brief inquiry functions
 *
 *  todo: add description here
 */

/** @defgroup v_inpt VDI input functions
 *
 *  @brief input functions
 *
 *  todo: add description here
 */

/** @defgroup v_outp VDI output functions
 *
 *  @brief output functions
 *
 *  todo: add description here
 */

/** @defgroup v_rstr VDI raster functions
 *
 *  @brief raster functions
 *
 *  todo: add description here
 */

/** @defgroup v_util VDI utility functions
 *
 *  @brief some usefull utilities function. This library doesn't contain
 *         any VDI call.
 */

/** @defgroup n_vdi VDI extended functions
 *
 */

/** @defgroup force_udef Specific UDEF functions
 *
 *  @brief This section contains all VDI functions that have a specific UDEF version.
 *
 *  Other UDEF functions are just an alias (define) to the standard VDI function.
 *
 *  When FORCE_GEMLIB_UDEF is defined by gemlib user, these functions will be used in place of their standard VDI version. 
 *  See \ref overviewUDEF for details.
 *
 *  \warning These functions are not multithread safe, and should be reserved for userdef usage, as suggested in \ref overviewUDEF. 
 */
/**@}*/


/** @mainpage
 *
 *  Welcome to GEMlib documentation main page.
 *
 *  @section Presentation Overview of gemlib usage
 *
 *  GEMlib is a C library that allow your software to access AES and VDI layers.
 *  If you don't know what AES and VDI are, then this library is probably not for you.
 *
 *  A good starting point of this documentation is the <a href="modules.html">Modules page</a>.
 *
 *  @subsection overviewAES1 Common usage of AES functions
 *
 *  Most of the time, gemlib is used to produce single thread application (only one thread for all AES stuff). In that case, the standard way to use GEMlib is to include gem.h.
 *  \code
 *  #include <gem.h>
 *  #include <gemx.h> // if extended gemlib functions are used
 *  
 *  int main() {
 *  // ...
 *  appl_init();
 *  //...
 *  appl_exit();
 *  // ...
 *  }
 *  \endcode
 *  
 *  In that case, AES functions invoked by the application will use the global AES data defined in GEMlib and initialised by appl_init().
 *
 *  @subsection overviewAES2 Mutlithread compatible usage of AES functions
 *
 *  For a multithread compliant applications, mt_gem.h shall be used. Then, the application shall define its own global AES data, and give a pointer to this
 *  global AES data as last parameter when invoking AES multithread compatible function, which are prefixed with "mt_".
 *  
 *  \code
 *  #include <mt_gem.h>
 *  #include <mt_gemx.h> // if extended gemlib functions are used
 *  
 *  int main() {
 *  // ...
 *  short aes_global[AES_GLOBMAX]; // global aes variable required by mt_ functions
 *  // ...
 *  mt_appl_init(aes_global);
 *  // ...
 *  mt_appl_exit(aes_global);
 *  // ...
 *  }
 *  \endcode
 *
 *  @subsection overviewVDI1 VDI is multithread compatible
 *
 *  Whatever the "mt" kind of header used (gem.h or mt_gem.h), VDI functions provided by GEMlib are thread safe.
 *
 *  To reach this goal, all the data used by VDI functions are allocated in the stack.
 *
 *  @subsection overviewUDEF UDEF version of VDI functions
 *  
 *  AES provides a mean for applications to draw its own objects in forms. This is "userdefined" object feature. The application defines a ub_code()
 *  callback function, and this callback function is called by the AES to redraw the object (by using VDI functions to draw stuff).
 *
 *  The issue is the following: some AES (TOS, maybe MagiC ?) have a small supervisor stack, and invoke the userdef callback function in supervisor mode.
 *  This may lead to a stack overflow if hungry stack consumption VDI calls are used.
 *
 *  Note: this is no issue with modern AES (XaAES or MyAES) which invokes the callback function in user mode.
 *
 *  In order to generate an application compatible with old fashion AES, the application shall have userdef callback function that are not memory stack hungry.
 *  For this purpose, userdef version of VDI functions have been introduced in gemlib.
 * 
 *  These functions are standard VDI function, prefixed with "udef_".
 *  A global VDIPB data is defined in gemlib, and this global data will be used by all udef_xxx functions. This way, the amount of memory allocated in the stack
 *  by udef_xxx functions will remain compatible with old fashion AES.
 *  For VDI functions that have light usage of the stack, their udef_xxx version is exactly the standard VDI function.
 *
 *  The use of udef_xxx functions should not be a problem on modern AES if there are only used in userdef functions : an AES callback function won't be interrupted
 *  by another AES callback function.
 *
 *  To use this feature, replace your VDI call by their udef version in your callback functions : just add "udef_" as prefix to the VDI function.
 *  \code
 *  void my_userdefined_callback_function(PARMBLK *pblk)
 *  {
 *    // ...
 *    udef_vswr_mode (vdih, MD_TRANS);   // instead of vswr_mode()
 *    udef_vsf_color (vdih, WHITE);
 *    udef_vsf_interior (vdih, FIS_PATTERN);
 *    udef_vsf_style (vdih, 4);
 *    udef_vr_recfl (vdih, tab);
 *    // ...
 *  }
 *  \endcode
 *
 *  If you don't want to change your callback function (too much work ?), and if you have a .c file that contains only your callback functions, then the option
 *  FORCE_GEMLIB_UDEF may be used. This option (to be defined before gem.h include) will replace all standard VDI call to their udef version.
 *  \code
 *  #define FORCE_GEMLIB_UDEF
 *  #include <gem.h>  // or mt_gem.h
 *  // ...
 *  void my_userdefined_callback_function(PARMBLK *pblk)
 *  {
 *    // ...
 *    vswr_mode (vdih, MD_TRANS);
 *    vsf_color (vdih, WHITE);
 *    vsf_interior (vdih, FIS_PATTERN);
 *    vsf_style (vdih, 4);
 *    vr_recfl (vdih, tab);
 *    // ...
 *  }
 *  \endcode
 *  
 *
 *  @section Reference
 * 
 *  If you want to get last news about GEMlib, please visit
 *  http://arnaud.bercegeay.free.fr/gemlib/
 *
 *  GEMlib is hosted on sparemint server. For developement access (CVS, bugtracker, mailing list...) please visit
 *  http://sparemint.org/sparemint/development.html
 *
 *  @section History
 *
 *  If you want to get details about last changes done in GEMlib, you can
 *  read the \link Changelog Changelog \endlink (from Dec 2002).
 *
 *  If you are interested in older changes that occured between GEMlib PL38 (last release before the
 *  MGEMlib branch of the library was created) and GEMlib 0.43.0 (merge back of MGEMlib and GEMlib),
 *  you can read
 *    - \link Changelog.MGL MGEMLIB branch (mgemlib 39 -> mgemlib 41) \endlink
 *    - \link Changelog.422 GEMLIB branch (gemlib 0.40.0 -> gemlib 0.42.2) \endlink
 *
 *  And last, the very first changelog, up to GEMlib PL38:  
 *  \link Changelog.old Changelog.old \endlink 
 */

/** @page Changelog.old
 * \verbinclude ChangeLog.old
 */

/** @page Changelog.MGL
 * \verbinclude ChangeLog.MGL
 */

/** @page Changelog.422
 * \verbinclude ChangeLog.422
 */

/** @page Changelog
 * \verbinclude ChangeLog
 */


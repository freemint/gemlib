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
 *  todo (any contribution is welcome)...
 */

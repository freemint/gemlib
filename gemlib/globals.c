/*
 *  $Id$
 */


# include "gem.h"

/* i don't know any way to stringify using sozobonx built-in preprocessor */
/* here is a very dirty hack just to get this file compilable with sozobonx */
#ifdef __SOZOBON__
#define str(x) "<str>"
#endif

#ifndef str
# define str(x)		_stringify (x)
# define _stringify(x)	#x
#endif

/*
 *  global data related to the lib
 */

/** release number of this lib in constant string */
#define GEMLIB_PATCHLEVEL	str(__GEMLIB_MAJOR__) "." str(__GEMLIB_MINOR__) "." \
				str(__GEMLIB_REVISION__) __GEMLIB_BETATAG__

/** global identify string for the lib */
char __Ident_gem[] = "$PatchLevel: GEM library: " GEMLIB_PATCHLEVEL " $";


/*
 *  global data related to AES stuff
 */
 
/** global aes variable: Application ID initialized by appl_init */
short gl_apid;

/** global aes variable: AES version initialized by appl_init */
short gl_ap_version;

/** global aes variable: aes global array, used by all 
    "old style" aes functions (function without "mt_")
 */
short aes_global  [AES_GLOBMAX];


/*
 * global vdi binding params 
 */

#if 0
short vdi_control[VDI_CNTRLMAX];
short vdi_intin[VDI_INTINMAX];
short vdi_ptsin[VDI_PTSINMAX];
short vdi_intout[VDI_INTOUTMAX];
short vdi_ptsout[VDI_PTSOUTMAX];

VDIPB vdi_params =
{
	&vdi_control[0],
	&vdi_intin[0],
	&vdi_ptsin[0],
	&vdi_intout[0],
	&vdi_ptsout[0]
};
#endif

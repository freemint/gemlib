
# include "gem.h"


#ifndef str
# define str(x)		_stringify (x)
# define _stringify(x)	#x
#endif

#define GEMLIB_PATCHLEVEL	str(__GEMLIB_MAJOR__) "." str(__GEMLIB_MINOR__) "." \
				str(__GEMLIB_REVISION__) __GEMLIB_BETATAG__

/*
 * global identify string for the lib
 */
char __Ident_gem[] = "$PatchLevel: GEM library: " GEMLIB_PATCHLEVEL " $";


/*
 * global aes variables, initialized by appl_init
 */
short gl_apid;
short gl_ap_version;


/*
 * global aes binding params 
 */
short	aes_control [AES_CTRLMAX];
short	aes_global  [AES_GLOBMAX];
short	aes_intin   [AES_INTINMAX];
short	aes_intout  [AES_INTOUTMAX];
long	aes_addrin  [AES_ADDRINMAX];
long	aes_addrout [AES_ADDROUTMAX];

AESPB aes_params =
{
	&aes_control[0],
	&aes_global[0],
	&aes_intin[0],
	&aes_intout[0],
	&aes_addrin[0],
	&aes_addrout[0]
};


/*
 * global vdi binding params 
 */
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

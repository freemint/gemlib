
# include "gemx.h"


/*
 * global aes variables, initialized by appl_init
 */
int gl_apid;
int gl_ap_version;


/*
 * global aes binding params 
 */
short aes_control[AES_CTRLMAX];
short aes_global[AES_GLOBMAX];
short aes_intin[AES_INTINMAX];
short aes_intout[AES_INTOUTMAX];
long aes_addrin[AES_ADDRINMAX];
long aes_addrout[AES_ADDROUTMAX];

AESPB aes_params = {
	&aes_control[0],
	&aes_global[0],
	&aes_intin[0],
	&aes_intout[0],
	&aes_addrin[0],
	&aes_addrout[0]
};

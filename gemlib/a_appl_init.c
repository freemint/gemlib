
#include <string.h>
#include "gem.h"


short
appl_init (void)
{
	/* clear all binding arrays
	 * other binding arrays are synonyms for the stuff
	 */
	bzero (&aes_control[0], AES_CTRLMAX * sizeof (short));
	bzero (&aes_intin[0], AES_INTINMAX * sizeof (short));
	bzero (&aes_intout[0], AES_INTOUTMAX * sizeof (short));
	bzero (&aes_addrin[0], AES_ADDRINMAX * sizeof (short));
	bzero (&aes_addrout[0], AES_ADDROUTMAX * sizeof (short));
	bzero (&aes_global[0], AES_GLOBMAX * sizeof (short));

	aes_control[0] = 10;
	aes_control[1] = 0;
	aes_control[2] = 1;
	aes_control[3] = 0;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	gl_ap_version = aes_global[0];
	gl_apid = aes_intout[0];
	
	return aes_intout[0];
}

#include <string.h>
#include "gem_aesP.h"


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

	AES_TRAP (aes_params, 10, 0,1,0,0);
	
	gl_ap_version = aes_global[0];
	gl_apid       = aes_intout[0];
	
	return aes_intout[0];
}

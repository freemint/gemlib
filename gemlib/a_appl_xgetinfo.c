#include "gem_aesP.h"


short
appl_xgetinfo (short type, short *out1, short *out2, short *out3, short *out4)
{
	static int has_agi = -1; /* do the check only once */
	
	if (has_agi < 0) {
		has_agi = gl_ap_version >= 0x400 || appl_find("?AGI") >= 0;
		          /* || (gl_ap_version == 0x399 && MagiC_version >= 0x0200) */
	}
	if (!has_agi) {
		return 0;
	}
	
	aes_intin[0] = type;
	
	AES_TRAP (aes_params, 130, 1,5,0,0);
	
	*out1 = aes_intout[1];
	*out2 = aes_intout[2];
	*out3 = aes_intout[3];
	*out4 = aes_intout[4];
	
	return aes_intout[0];
}

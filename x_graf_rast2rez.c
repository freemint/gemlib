#include "gem_aesP.h"
#include "mt_gemx.h"

/** 
 *
 *  @param src_data
 *  @param plane_len
 *  @param old_planes
 *  @param mfdb
 *  @param devspef
 *  @param global_aes global AES array
 *
 *  @return 0 if an error occured or non-zero otherwise.
 *
 *  @since Geneva
 *
 */

void
mt_x_graf_rast2rez(unsigned short *src_data, long plane_len,
     short old_planes, MFDB *mfdb, short devspef, short *global_aes)
{
	AES_PARAMS(0x7132,4,0,2,0);

	aes_intin_long(0) = plane_len;
	aes_intin[2] = old_planes;
	aes_intin[3] = devspef;
	aes_addrin[0] = (long)src_data;
	aes_addrin[1] = (long)mfdb;

	AES_TRAP(aes_params);
}

/*
 *  $Id$
 */

#include "gem_aesP.h"

/** tell PC-GEM which logical drives are connected to the system (for the file selector box).
 *
 *  @param bvdisk Bit vector with all connected disk drives. Bit 15 (the most
 *         significant bit) denotes drive A:
 *  @param bvhard Bit vector with all connected hard drives.
 *  @param global_aes global AES array
 *
 *  @return Unknown
 *
 *  @since only available on PC-GEM (as of version 2.0)
 *
 */

short
mt_appl_bvset(short bvdisk, short bvhard, short *global_aes)
{
	AES_PARAMS(16,2,1,0,0);

	aes_intin[0] = bvdisk;
	aes_intin[1] = bvhard;

	AES_TRAP(aes_params);

	return aes_intout[0];
}

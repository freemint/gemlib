
#include "gem.h"


short
graf_shrinkbox (short Fx, short Fy, short Fw, short Fh, short Sx, short Sy, short Sw,
		short Sh)
{
	aes_intin[0] = Fx;
	aes_intin[1] = Fy;
	aes_intin[2] = Fw;
	aes_intin[3] = Fh;
	aes_intin[4] = Sx;
	aes_intin[5] = Sy;
	aes_intin[6] = Sw;
	aes_intin[7] = Sh;
	
	aes_control[0] = 74;
	aes_control[1] = 8;
	aes_control[2] = 1;
	aes_control[3] = 0;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return aes_intout[0];
}

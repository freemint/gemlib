
#include "gemx.h"


short
form_xdial (short fo_diflag, short fo_dilittlx, short fo_dilittly, short fo_dilittlw,
	    short fo_dilittlh, short fo_dibigx, short fo_dibigy, short fo_dibigw,
	    short fo_dibigh, void **flydial)
{
	aes_intin[0] = fo_diflag;
	aes_intin[1] = fo_dilittlx;
	aes_intin[2] = fo_dilittly;
	aes_intin[3] = fo_dilittlw;
	aes_intin[4] = fo_dilittlh;
	aes_intin[5] = fo_dibigx;
	aes_intin[6] = fo_dibigy;
	aes_intin[7] = fo_dibigw;
	aes_intin[8] = fo_dibigh;
	aes_addrin[0] = (long) flydial;
	aes_control[0] = 51;
	aes_control[1] = 9;
	aes_control[2] = 1;
	aes_control[3] = 1;
	aes_control[4] = 0;
	aes (&aes_params);
	return aes_intout[0];
}

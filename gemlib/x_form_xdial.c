
#include "gemx.h"


int
form_xdial (int fo_diflag, int fo_dilittlx, int fo_dilittly, int fo_dilittlw,
	    int fo_dilittlh, int fo_dibigx, int fo_dibigy, int fo_dibigw,
	    int fo_dibigh, void **flydial)
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

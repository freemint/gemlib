
#include "gem.h"


int
evnt_dclick (int ToSet, int SetGet)
{
	aes_intin[0] = ToSet;
	aes_intin[1] = SetGet;
	aes_control[0] = 26;
	aes_control[1] = 2;
	aes_control[2] = 1;
	aes_control[3] = 0;
	aes_control[4] = 0;
	aes (&aes_params);
	return aes_intout[0];
}

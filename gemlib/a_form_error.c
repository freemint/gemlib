
#include "gem.h"


int
form_error (int ErrorCode)
{
	aes_intin[0] = ErrorCode;
	aes_control[0] = 53;
	aes_control[1] = 1;
	aes_control[2] = 1;
	aes_control[3] = 0;
	aes_control[4] = 0;
	aes (&aes_params);
	return aes_intout[0];
}

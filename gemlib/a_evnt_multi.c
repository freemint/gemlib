#include "gem_aesP.h"


short
evnt_multi (short Type, short Clicks, short WhichButton, short WhichState,
	    short EnterExit1, short In1X, short In1Y, short In1W, short In1H,
	    short EnterExit2, short In2X, short In2Y, short In2W, short In2H,
	    short MesagBuf[], unsigned long Interval,
	    short *OutX, short *OutY, short *ButtonState, short *KeyState, short *Key,
	    short *ReturnCount)
{
	unsigned short *i = (unsigned short *) &Interval;

	aes_intin[0]  = Type;
	aes_intin[1]  = Clicks;
	aes_intin[2]  = WhichButton;
	aes_intin[3]  = WhichState;
	aes_intin[4]  = EnterExit1;
	aes_intin[5]  = In1X;
	aes_intin[6]  = In1Y;
	aes_intin[7]  = In1W;
	aes_intin[8]  = In1H;
	aes_intin[9]  = EnterExit2;
	aes_intin[10] = In2X;
	aes_intin[11] = In2Y;
	aes_intin[12] = In2W;
	aes_intin[13] = In2H;
	aes_intin[14] = i[1];
	aes_intin[15] = i[0];
	aes_addrin[0] = (long)MesagBuf;

	AES_TRAP (aes_params, 25, 16,7,1,0);

	*OutX        = aes_intout[1];
	*OutY        = aes_intout[2];
	*ButtonState = aes_intout[3];
	*KeyState    = aes_intout[4];
	*Key         = aes_intout[5];
	*ReturnCount = aes_intout[6];

	return aes_intout[0];
}


#include "gem.h"


int
objc_draw (void *Tree, int Start, int Depth, int Cx, int Cy, int Cw, int Ch)
{
	aes_intin[0] = Start;
	aes_intin[1] = Depth;
	aes_intin[2] = Cx;
	aes_intin[3] = Cy;
	aes_intin[4] = Cw;
	aes_intin[5] = Ch;
	aes_addrin[0] = (long) Tree;
	aes_control[0] = 42;
	aes_control[1] = 6;
	aes_control[2] = 1;
	aes_control[3] = 1;
	aes_control[4] = 0;
	aes (&aes_params);
	return aes_intout[0];
}

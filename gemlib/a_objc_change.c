#include "gem.h"


short
objc_change (OBJECT *Tree, short Object, short Res,
             short Cx, short Cy, short Cw, short Ch,
             short NewState, short Redraw)
{
	aes_intin[0] = Object;
	aes_intin[1] = Res;
	aes_intin[2] = Cx;
	aes_intin[3] = Cy;
	aes_intin[4] = Cw;
	aes_intin[5] = Ch;
	aes_intin[6] = NewState;
	aes_intin[7] = Redraw;
	aes_addrin[0] = (long) Tree;
	aes_control[0] = 47;
	aes_control[1] = 8;
	aes_control[2] = 1;
	aes_control[3] = 1;
	aes_control[4] = 0;
	aes (&aes_params);
	return aes_intout[0];
}


#include "gem.h"


void
vqt_attributes (int handle, int atrib[])
{
#ifndef __MSHORT__
	short *wptr;
	int *end;
#else
	vdi_params.intout = (short *) &atrib[0];
	vdi_params.ptsout = (short *) &atrib[6];
#endif

	vdi_control[0] = 38;
	vdi_control[1] = 0;
	vdi_control[3] = 0;
	vdi_control[5] = 0;
	vdi_control[6] = handle;
	vdi (&vdi_params);

#ifndef __MSHORT__
	wptr = &vdi_intout[0];
	end = &atrib[6];
	do
	{
		*atrib++ = *wptr++;
	}
	while (atrib < end);
	wptr = &vdi_ptsout[0];
	end += 4;
	do
	{
		*atrib++ = *wptr++;
	}
	while (atrib < end);
#else
	vdi_params.intout = &vdi_intout[0];
	vdi_params.ptsout = &vdi_ptsout[0];
#endif
}

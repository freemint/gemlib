
#include "gemx.h"


void
vr_transfer_bits (int handle, GCBITMAP * src_bm, GCBITMAP * dst_bm,
		  int *src_rect, int *dst_rect, int mode)
{
	vdi_intin[0] = mode;
	vdi_intin[1] = 0;
	vdi_intin[2] = 0;
	vdi_intin[3] = 0;

	vdi_ptsin[0] = src_rect[0];
	vdi_ptsin[1] = src_rect[1];
	vdi_ptsin[2] = src_rect[2];
	vdi_ptsin[3] = src_rect[3];

	vdi_ptsin[4] = dst_rect[0];
	vdi_ptsin[5] = dst_rect[1];
	vdi_ptsin[6] = dst_rect[2];
	vdi_ptsin[7] = dst_rect[3];

	*(GCBITMAP **) & vdi_control[7] = src_bm;
	*(GCBITMAP **) & vdi_control[9] = dst_bm;
	*(GCBITMAP **) & vdi_control[11] = 0L;

	vdi_control[0] = 170;
	vdi_control[1] = 4;
	vdi_control[3] = 4;
	vdi_control[5] = 0;
	vdi_control[6] = handle;
	vdi (&vdi_params);
}

/*
 * * NOTE: requires NVDI version 5.x or higher
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/**
 *
 *  @param handle Device handle
 *  @param src_clip_rect clipping rectangle
 *  @param src_rect source rectangle
 *  @param dst_rect destination rectangle
 *  @param clipped_src_rect clipped source rectangle
 *  @param clipped_dst_rect clipped destination rectangle
 *
 *  @since NVDI 5.02 (check bit #2 of workout[30] of vq_extnd())
 *
 *
 *
 */

short vr_clip_rects_by_src(short handle, const RECT16 *src_clip_rect, const RECT16 *src_rect, const RECT16 *dst_rect, RECT16 *clipped_src_rect, RECT16 *clipped_dst_rect)
{
	short vdi_control[VDI_CNTRLMAX];
	short vdi_ptsin[12];
	short vdi_ptsout[8];
	short vdi_intout[1];
	RECT16 *pp;

	VDI_PARAMS(vdi_control, vdi_dummy, vdi_ptsin, vdi_intout, vdi_ptsout);

	pp = (RECT16 *)&vdi_ptsin[0];
	*pp++ = *src_clip_rect;
	*pp++ = *src_rect;
	*pp = *dst_rect;

	VDI_TRAP_ESC (vdi_params, handle, 171, 1, 6, 0);

#if CHECK_NULLPTR
	if (clipped_src_rect)
#endif
	{
		pp = (RECT16*)&vdi_ptsout[0];
		*clipped_src_rect = *pp;
	}
#if CHECK_NULLPTR
	if (clipped_dst_rect)
#endif
	{
		pp = (RECT16*)&vdi_ptsout[4];
		*clipped_dst_rect = *pp;
	}

	return vdi_intout[0];
}

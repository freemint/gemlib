/*
 *  $Id$
 */

#ifndef _GEM_VDI_P_
# define _GEM_VDI_P_

# ifndef _GEMLIB_H_
#  include "mt_gem.h"
# endif


#define vdi_control_ptr(n)   *((void**)(vdi_control +n))
#define vdi_intin_ptr(n)     *((void**)(vdi_intin   +n))
#define vdi_intout_long(n)   *((long*) (vdi_intout  +n))

#if defined(__GNUC__) && !defined(__NO_INLINE__)

static inline void
_vdi_trap_esc (VDIPB * vdipb,
               long cntrl_0_1, long cntrl_3, long cntrl_5, short handle)
{
	__asm__ volatile (
		"movea.l	%0,a0\n\t"	/* &vdipb */
		"move.l	a0,d1\n\t"
		"move.l	(a0),a0\n\t"	/* vdipb->control */
		"move.l	%1,(a0)+\n\t"	/* cntrl_0, cntrl_1 */
		"move.l	%2,(a0)+\n\t"	/* cntrl_2, cntrl_3 */
		"move.l	%3,(a0)+\n\t"	/* cntrl_4, cntrl_5 */
		"move.w	%4,(a0)\n\t"	/* handle */
		"move.w	#115,d0\n\t"	/* 0x0073 */
		"trap	#2"
		:
		: "g"(vdipb), "g"(cntrl_0_1), "g"(cntrl_3), "g"(cntrl_5), "g"(handle)
		: "d0", "d1", "d2", "a0", "a1", "a2", "memory"
	);
}
#define VDI_TRAP_ESC(vdipb, handle, opcode, subop, cntrl_1, cntrl_3) \
	_vdi_trap_esc (&vdipb, (opcode##uL<<16)|cntrl_1, cntrl_3, subop, handle)

static inline void
_vdi_trap_00 (VDIPB * vdipb, long cntrl_0_1, short handle)
{
	__asm__ volatile (
		"movea.l %0,a0\n\t"	/* &vdipb */
		"move.l  a0,d1\n\t"
		"move.l  (a0),a0\n\t"	/* vdipb->control */
		"move.l  %1,(a0)+\n\t"	/* cntrl_0, cntrl_1 */
		"moveq   #0,d0\n\t"
		"move.l  d0,(a0)+\n\t"	/* cntrl_2, cntrl_3 */
		"move.l  d0,(a0)+\n\t"	/* cntrl_4, cntrl_5 */
		"move.w  %2,(a0)\n\t"	/* handle */
		"move.w  #115,d0\n\t"	/* 0x0073 */
		"trap    #2"
		:
		: "g"(vdipb), "g"(cntrl_0_1), "g"(handle)
		: "d0", "d1", "d2", "a0", "a1", "a2", "memory"
	);
}
#define VDI_TRAP_00(vdipb, handle, opcode) \
	_vdi_trap_00 (&vdipb, (opcode##uL<<16), handle)


#else 

#if defined(__VBCC__)

__regsused("d0/d1/a0/a1") void _vdi_trap_esc(
        __reg("a0")VDIPB *,__reg("d0")long,__reg("d1")long,
        __reg("d2")long,__reg("d3")short) =
  "\tmove.l\td2,-(sp)\n"
  "\tmove.l\ta2,-(sp)\n"
  "\tmove.l\t(a0),a1\n"
  "\tmovem.l\td0-d2,(a1)\n"
  "\tmove.w\td3,12(a1)\n"
  "\tmove.l\ta0,d1\n"
  "\tmoveq\t#115,d0\n"
  "\ttrap\t#2\n"
  "\tmove.l\t(sp)+,a2\n"
  "\tmove.l\t(sp)+,d2";
  
#define VDI_TRAP_ESC(vdipb, handle, opcode, subop, cntrl_1, cntrl_3) \
        _vdi_trap_esc (&vdipb, (opcode##uL<<16)|cntrl_1, cntrl_3, subop, handle)

__regsused("d0/d1/a0/a1") void _vdi_trap_00(
        __reg("a0")VDIPB *,__reg("d0")long,__reg("d1")short) =
  "\tmove.l\td2,-(sp)\n"
  "\tmove.l\ta2,-(sp)\n"
  "\tmove.l\t(a0),a1\n"
  "\tmove.l\td0,(a1)+\n"
  "\tmoveq\t#0,d0\n"
  "\tmove.l\td0,(a1)+\n"
  "\tmove.l\td0,(a1)+\n"
  "\tmove.w\td1,(a1)\n"
  "\tmove.l\ta0,d1\n"
  "\tmoveq\t#115,d0\n"
  "\ttrap\t#2\n"
  "\tmove.l\t(sp)+,a2\n"
  "\tmove.l\t(sp)+,d2";  
  
#define VDI_TRAP_00(vdipb, handle, opcode) \
	_vdi_trap_00 (&vdipb, (opcode##uL<<16), handle)
 
#else /* no usage of inlines, go the old way */

#define VDI_TRAP_ESC(vdipb, handle, opcode, subop, cntrl_1, cntrl_3) \
	vdi_control[0] = opcode;  \
	vdi_control[1] = cntrl_1; \
	vdi_control[3] = cntrl_3; \
	vdi_control[5] = subop;   \
	vdi_control[6] = handle;  \
	vdi (&vdipb);

#define VDI_TRAP_00(vdipb, handle, opcode) \
	VDI_TRAP_ESC (vdipb, handle, opcode, 0, 0, 0)
#endif /* __VBCC__ */
#endif


#define VDI_TRAP(vdipb, handle, opcode, cntrl_1, cntrl_3) \
	VDI_TRAP_ESC(vdipb, handle, opcode, 0, cntrl_1, cntrl_3)

#define VDI_PARAMS(a,b,c,d,e) \
	VDIPB vdi_params;         \
	vdi_params.control = a;   \
	vdi_params.intin   = b;   \
	vdi_params.ptsin   = c;   \
	vdi_params.intout  = d;   \
	vdi_params.ptsout  = e;


/* special feature for VDI bindings: pointer in parameters (for return values)
 * could be NULL (nice idea by Martin Elsasser against dummy variables) 
 */
#define CHECK_NULLPTR 1

/* special feature for VDI bindings: set VDIPB::intout and VDIPB::ptsout to
 * vdi_dummy array intead of NULL against crashes if some crazy VDI drivers
 * tries to write something in ptsout/intout.
 */ 
#define USE_VDI_DUMMY 1

#if USE_VDI_DUMMY
	/* use dummy array vdi_dummy[] from vdi_dummy.c */
	extern short vdi_dummy[];
#else
	/* replace vdi_dummy in VDIPB by NULL pointer */
	#define vdi_dummy 0L
#endif

# endif /* _GEM_VDI_P_ */

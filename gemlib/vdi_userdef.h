/*
 *  $Id$
 */

#include "mt_gem.h"

/** private type used by all "udef" specific functions */
typedef struct
{
    short    vdi_control[VDI_CNTRLMAX];  /**< private global data used by all "udef" specific functions */
    short    vdi_intin[VDI_INTINMAX];    /**< private global data used by all "udef" specific functions */
    short    vdi_intout[VDI_INTOUTMAX];  /**< private global data used by all "udef" specific functions */
    short    vdi_ptsin[VDI_PTSINMAX];    /**< private global data used by all "udef" specific functions */
    short    vdi_ptsout[VDI_PTSOUTMAX];  /**< private global data used by all "udef" specific functions */
} VDIPARBLK;


extern VDIPARBLK _VDIParBlk;

#undef vdi_control_ptr
#undef vdi_intin_ptr
#undef vdi_intin_long
#undef vdi_intout_long
#undef vdi_intout_ptr
#undef vdi_ptsout_long
#undef vdi_ptsin_long

#ifdef __GNUC__

/* to avoid "dereferencing type-punned pointer" */
#define vdi_intin_long(n)  *__vdi_intin_long(n, _VDIParBlk.vdi_intin)
#define vdi_intout_long(n)  *__vdi_intout_long(n, _VDIParBlk.vdi_intout)
#define vdi_intout_ptr(n, t)  *((t *)__vdi_intout_ptr(n, _VDIParBlk.vdi_intout))
#define vdi_ptsout_long(n)  *__vdi_ptsout_long(n, _VDIParBlk.vdi_ptsout)
#define vdi_ptsin_long(n)  *__vdi_ptsin_long(n, _VDIParBlk.vdi_ptsin)
#define vdi_intin_ptr(n, t)  *((t *)__vdi_intin_ptr(n, _VDIParBlk.vdi_intin))
#define vdi_control_ptr(n, t)  *((t *)__vdi_control_ptr(n, _VDIParBlk.vdi_control))

#else

#define vdi_control_ptr(n, t)   *((t *)(_VDIParBlk.vdi_control + 7 + (n) * N_PTRINTS))
#define vdi_intin_ptr(n, t)     *((t *)(_VDIParBlk.vdi_intin + (n) * N_PTRINTS))
#define vdi_intin_long(n)       *((long *)(_VDIParBlk.vdi_intin + (n)))
#define vdi_intout_long(n)      *((long *)(_VDIParBlk.vdi_intout + (n)))
#define vdi_intout_ptr(n, t)    *((t *)(_VDIParBlk.vdi_intout + n * N_PTRINTS))
#define vdi_ptsout_long(n)      *((long *)(_VDIParBlk.vdi_ptsout + n))
#define vdi_ptsin_long(n)       *((long *)(_VDIParBlk.vdi_ptsin + n))

#endif

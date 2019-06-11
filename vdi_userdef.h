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

/* to avoid "dereferencing type-punned pointer" */
#define vdi_intin_long(n)  *__vdi_array_long(n, _VDIParBlk.vdi_intin)
#define vdi_intout_long(n)  *__vdi_array_long(n, _VDIParBlk.vdi_intout)
#define vdi_ptsin_long(n)  *__vdi_array_long(n, _VDIParBlk.vdi_ptsin)
#define vdi_ptsout_long(n)  *__vdi_array_long(n, _VDIParBlk.vdi_ptsout)
#define vdi_intout_ptr(n, t)  *((t *)__vdi_array_ptr(n, _VDIParBlk.vdi_intout))
#define vdi_intin_ptr(n, t)  *((t *)__vdi_array_ptr(n, _VDIParBlk.vdi_intin))
#define vdi_control_ptr(n, t)  *((t *)__vdi_array_ptr(7 + (n) * N_PTRINTS, _VDIParBlk.vdi_control))

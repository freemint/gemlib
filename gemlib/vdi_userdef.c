
#include "mt_gem.h"

typedef struct
{
    short    vdi_control[VDI_CNTRLMAX];
    short    vdi_intin[VDI_INTINMAX];
    short    vdi_intout[VDI_INTOUTMAX];
    short    vdi_ptsin[VDI_PTSINMAX];
    short    vdi_ptsout[VDI_PTSOUTMAX];
} VDIPARBLK;


VDIPARBLK _VDIParBlk;

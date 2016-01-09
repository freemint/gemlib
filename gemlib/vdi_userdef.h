/*
 *  $Id$
 */

#include "mt_gem.h"

/** TODO */
typedef struct
{
    short    vdi_control[VDI_CNTRLMAX];  /**< TODO */
    short    vdi_intin[VDI_INTINMAX];    /**< TODO */
    short    vdi_intout[VDI_INTOUTMAX];  /**< TODO */
    short    vdi_ptsin[VDI_PTSINMAX];    /**< TODO */
    short    vdi_ptsout[VDI_PTSOUTMAX];  /**< TODO */
} VDIPARBLK;


extern VDIPARBLK _VDIParBlk;


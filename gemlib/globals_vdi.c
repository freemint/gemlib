
# include "gem.h"


/*
 * global vdi binding params 
 */
short vdi_control[VDI_CNTRLMAX];
short vdi_intin[VDI_INTINMAX];
short vdi_ptsin[VDI_PTSINMAX];
short vdi_intout[VDI_INTOUTMAX];
short vdi_ptsout[VDI_PTSOUTMAX];

VDIPB vdi_params = {
	&vdi_control[0],
	&vdi_intin[0],
	&vdi_ptsin[0],
	&vdi_intout[0],
	&vdi_ptsout[0]
};

/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** copies the header of a speedo font file into \p buffer and 
 *  returns a pointer to the TDF file. The buffer should have a size of 1 Kb, 
 *  because the header size depends on the font and extensions of the font format.
 *
 *  @param handle Device handle
 *  @param buffer font header
 *  @param pathname name of the TDF
 *
 *  @since NVDI 3.00
 *
 *  If the selected (vector) font is not a Speedo font (TrueType, ...) the VDI 
 *  tries to create a virtual header with the important information.
 *  
 *  You should consider that each vqt_fontheader()-call can lead to several disk 
 *  accesses (depending on the font format) - if a user has installed 300 or more 
 *  fonts (which can happen very easily if you use high quality fonts with a lot 
 *  of font styles), this will take a few seconds. If necessary, save font 
 *  information and load (and update) it when your program is started.
 *
 *  Note:
 *  
 *  Usually the following elements of the font header are the most interesting 
 *  ones for programmers:
 *  
\verbatim
Name      Offset  Length  Description
FH_FNTNM    24     70     font name (siehe auch vqt_name()),
                          e.g. "Century 725 Italic BT"
FH_NKTKS   258      2     number of kerning tracks
FH_NKPRS   260      2     number of kerining pairs, (see vst_kern())
FH_CLFGS   263      1     classification (Italic and Monospace)
FH_SFNTN   266     32     name of the corresponding Postscript font,
                          e.g. "Century725BT-Italic"
FH_SFACN   298     16     short name of the family, e.g. "Century725 BT"
FH_FNTFM   314     14     style, e.g. "Italic"
FH_ITANG   328      2     skew in 1/256 of degrees (if it is an italic font),
                          e.g 4480 (17,5 degree)
FH_ORUPM   330      2     number of ORUs per em, e.g. 2048
\endverbatim
 *
 */

void
vqt_fontheader (short handle, char *buffer, char *pathname)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[VDI_INTOUTMAX]; 
	VDI_PARAMS(vdi_control, (short*)&buffer, 0L, vdi_intout, vdi_dummy);
#else
	vdi_intin_ptr(0) = buffer;
#endif
		
	VDI_TRAP (vdi_params, handle, 232, 0,2);
	
	vdi_array2str (vdi_intout, pathname, vdi_control[4]);
}

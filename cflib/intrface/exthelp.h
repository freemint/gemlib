/*
 * resource set indices for exthelp
 *
 * created by ORCS 2.15
 */

/*
 * Number of Strings:        17
 * Number of Bitblks:        0
 * Number of Iconblks:       0
 * Number of Color Iconblks: 0
 * Number of Color Icons:    0
 * Number of Tedinfos:       0
 * Number of Free Strings:   1
 * Number of Free Images:    0
 * Number of Objects:        18
 * Number of Trees:          1
 * Number of Userblks:       0
 * Number of Images:         0
 * Total file size:          1174
 */

#undef RSC_NAME
#ifndef __ALCYON__
#define RSC_NAME "exthelp"
#endif
#undef RSC_ID
#ifdef exthelp
#define RSC_ID exthelp
#else
#define RSC_ID 0
#endif

#ifndef RSC_STATIC_FILE
# define RSC_STATIC_FILE 0
#endif
#if !RSC_STATIC_FILE
#define NUM_STRINGS 17
#define NUM_FRSTR 1
#define NUM_UD 0
#define NUM_IMAGES 0
#define NUM_BB 0
#define NUM_FRIMG 0
#define NUM_IB 0
#define NUM_CIB 0
#define NUM_TI 0
#define NUM_OBS 18
#define NUM_TREE 1
#endif



#define HELP_EXTEND        0 /* form/dialog */

#define EXITALERT          0 /* Alert string */
/* [2][Exitbutton:|%d = '%s'][Weiter|Abbruch] */




#ifdef __STDC__
#ifndef _WORD
#  ifdef WORD
#    define _WORD WORD
#  else
#    define _WORD short
#  endif
#endif
extern _WORD exthelp_rsc_load(void);
extern _WORD exthelp_rsc_gaddr(_WORD type, _WORD idx, void *gaddr);
extern _WORD exthelp_rsc_free(void);
#endif

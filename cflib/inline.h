/*
 * resource set indices for inline
 *
 * created by ORCS 2.15
 */

/*
 * Number of Strings:        23
 * Number of Bitblks:        4
 * Number of Iconblks:       0
 * Number of Color Iconblks: 4
 * Number of Color Icons:    8
 * Number of Tedinfos:       2
 * Number of Free Strings:   0
 * Number of Free Images:    0
 * Number of Objects:        27
 * Number of Trees:          3
 * Number of Userblks:       0
 * Number of Images:         4
 * Total file size:          5636
 */

#undef RSC_NAME
#ifndef __ALCYON__
#define RSC_NAME "inline"
#endif
#undef RSC_ID
#ifdef inline
#define RSC_ID inline
#else
#define RSC_ID 0
#endif

#ifndef RSC_STATIC_FILE
# define RSC_STATIC_FILE 0
#endif
#if !RSC_STATIC_FILE
#define NUM_STRINGS 23
#define NUM_FRSTR 0
#define NUM_UD 0
#define NUM_IMAGES 4
#define NUM_BB 4
#define NUM_FRIMG 0
#define NUM_IB 0
#define NUM_CIB 4
#define NUM_TI 2
#define NUM_OBS 27
#define NUM_TREE 3
#endif



#define ALERTBOX           0 /* form/dialog */
#define AL_TITLE           1 /* STRING in tree ALERTBOX */
#define AL_INFO            2 /* IMAGE in tree ALERTBOX */
#define AL_ACHT            3 /* IMAGE in tree ALERTBOX */
#define AL_QST             4 /* IMAGE in tree ALERTBOX */
#define AL_STOP            5 /* IMAGE in tree ALERTBOX */
#define AL_STR1            6 /* STRING in tree ALERTBOX */
#define AL_STR2            7 /* STRING in tree ALERTBOX */
#define AL_STR3            8 /* STRING in tree ALERTBOX */
#define AL_STR4            9 /* STRING in tree ALERTBOX */
#define AL_STR5           10 /* STRING in tree ALERTBOX */
#define AL_BUT1           11 /* BUTTON in tree ALERTBOX */
#define AL_BUT2           12 /* BUTTON in tree ALERTBOX */
#define AL_BUT3           13 /* BUTTON in tree ALERTBOX */

#define ASCIITAB           1 /* form/dialog */
#define AT_TITLE           1 /* STRING in tree ASCIITAB */
#define AT_BOX             2 /* IBOX in tree ASCIITAB */
#define AT_DEZ             4 /* TEXT in tree ASCIITAB */ /* max len 3 */
#define AT_HEX             6 /* TEXT in tree ASCIITAB */ /* max len 4 */
#define AT_ABBRUCH         7 /* BUTTON in tree ASCIITAB */

#define BUTTONS            2 /* form/dialog */
#define BT_RADIO           1 /* CICON in tree BUTTONS */ /* max len 1 */
#define BT_CHECK           2 /* CICON in tree BUTTONS */ /* max len 1 */
#define BT_RLOW            3 /* CICON in tree BUTTONS */ /* max len 1 */
#define BT_CLOW            4 /* CICON in tree BUTTONS */ /* max len 1 */




#ifdef __STDC__
#ifndef _WORD
#  ifdef WORD
#    define _WORD WORD
#  else
#    define _WORD short
#  endif
#endif
extern _WORD inline_rsc_load(void);
extern _WORD inline_rsc_gaddr(_WORD type, _WORD idx, void *gaddr);
extern _WORD inline_rsc_free(void);
#endif

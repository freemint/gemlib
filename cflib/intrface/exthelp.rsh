/* GEM Resource C Source */

#include "exthelp.h"

#if !defined(WHITEBAK)
#define WHITEBAK    0x0040
#endif
#if !defined(DRAW3D)
#define DRAW3D      0x0080
#endif

#define FLAGS9  0x0200
#define FLAGS10 0x0400
#define FLAGS11 0x0800
#define FLAGS12 0x1000
#define FLAGS13 0x2000
#define FLAGS14 0x4000
#define FLAGS15 0x8000
#define STATE8  0x0100
#define STATE9  0x0200
#define STATE10 0x0400
#define STATE11 0x0800
#define STATE12 0x1000
#define STATE13 0x2000
#define STATE14 0x4000
#define STATE15 0x8000

static char *rs_frstr[] =
{ "[2][Exitbutton:|%d = \047%s\047][Weiter|Abbruch]"
};

static OBJECT rs_object[] =
{ 
  /******** Tree 0 HELP_EXTEND ****************************************************/
        -1,        1,       17, G_BOX             ,   /* Object 0  */
  NONE, OUTLINED|DRAW3D, (long)0x00021100L,
  0x0000, 0x0000, 0x003C, 0x0816,
         2,       -1,       -1, G_IBOX            |0x1100,   /* Object 1  */
  TOUCHEXIT, CROSSED|OUTLINED|DRAW3D, (long)0x00FF1101L,
  0x003A, 0x0000, 0x0002, 0x0001,
         3,       -1,       -1, G_BUTTON          |0x1300,   /* Object 2  */
  NONE, DRAW3D, (long)"Hilfe \201ber erweiterte MagiC-Objekttypen",
  0x0002, 0x0001, 0x0027, 0x0001,
         4,       -1,       -1, G_STRING          ,   /* Object 3  */
  NONE, DRAW3D, (long)"Grunds\204tzlich mu\236 bei allen MagiC-Objekten WHITEBAK",
  0x0003, 0x0003, 0x0033, 0x0001,
         5,       -1,       -1, G_STRING          ,   /* Object 4  */
  NONE, DRAW3D, (long)"gesetzt sein (bis auf Edit-Feld und Popup).",
  0x0003, 0x0004, 0x002B, 0x0001,
         6,       -1,       -1, G_STRING          ,   /* Object 5  */
  NONE, DRAW3D, (long)"\232berschrift  : STRING, State-Bit 8..15, CHECKED: klein",
  0x0003, 0x0006, 0x0036, 0x0001,
         7,       -1,       -1, G_STRING          ,   /* Object 6  */
  NONE, DRAW3D, (long)"Gruppenrahmen: BUTTON, State-Bit 9..15, CHECKED: klein",
  0x0003, 0x0007, 0x0036, 0x0001,
         8,       -1,       -1, G_STRING          ,   /* Object 7  */
  NONE, DRAW3D, (long)"Editfeld     : FTEXT, 3D Background, Rahmen au\236en 2",
  0x0003, 0x0008, 0x0033, 0x0001,
         9,       -1,       -1, G_STRING          ,   /* Object 8  */
  NONE, DRAW3D, (long)"Popup        : BOXTEXT, SHADOWED, TOUCHEXIT",
  0x0003, 0x0009, 0x002B, 0x0001,
        10,       -1,       -1, G_BUTTON          |0x1300,   /* Object 9  */
  NONE, DRAW3D, (long)"Tastaturbedienbare Objekte",
  0x0002, 0x000B, 0x001A, 0x0001,
        11,       -1,       -1, G_STRING          ,   /* Object 10  */
  NONE, DRAW3D, (long)"Shortcut-Position: 4bit-Zahl (State-Bit 8..11)",
  0x0003, 0x080C, 0x002E, 0x0001,
        12,       -1,       -1, G_STRING          ,   /* Object 11  */
  NONE, DRAW3D, (long)"Radiobutton  : BUTTON, RADIO, Bit 15, 3D Background",
  0x0003, 0x080E, 0x0033, 0x0001,
        13,       -1,       -1, G_STRING          ,   /* Object 12  */
  NONE, DRAW3D, (long)"Checkbox     : BUTTON, !RADIO, Bit 15, 3D Background",
  0x0003, 0x080F, 0x0034, 0x0001,
        14,       -1,       -1, G_STRING          ,   /* Object 13  */
  NONE, DRAW3D, (long)"Exitbutton   : BUTTON, EXIT, 3D Activator",
  0x0003, 0x0810, 0x0029, 0x0001,
        15,       -1,       -1, G_STRING          ,   /* Object 14  */
  NONE, DRAW3D, (long)"String       : STRING, TOUCHEXIT",
  0x0003, 0x0811, 0x0020, 0x0001,
        16,       -1,       -1, G_STRING          ,   /* Object 15  */
  NONE, DRAW3D, (long)"Undobutton   : Flag-Bit 11",
  0x0003, 0x0013, 0x001A, 0x0001,
        17,       -1,       -1, G_STRING          ,   /* Object 16  */
  NONE, NORMAL, (long)"Helpbutton   : Flag-Bit 12",
  0x0003, 0x0014, 0x001A, 0x0001,
         0,       -1,       -1, G_BUTTON          |0x1200,   /* Object 17  */
  SELECTABLE|DEFAULT|EXIT|LASTOB, DRAW3D, (long)"[OK",
  0x042A, 0x0814, 0x0009, 0x0001
};

static OBJECT *rs_trindex[] =
{ &rs_object[0]    /* Tree  0 HELP_EXTEND      */
};

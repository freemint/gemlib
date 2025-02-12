/*
 * gemx.h - main header file for new gem-lib extensions
 *
 * This lib contains all GEM extensions of MagiC/Geneva and NVDI/FSM/Speedo
 *
 */

/**@file
 * GEMlib header for extended functions
 */

#ifndef _MT_GEMLIB_X_H_
#define _MT_GEMLIB_X_H_

#ifndef _MT_GEMLIB_H_
#include <mt_gem.h>
#endif

__BEGIN_DECLS


/*******************************************************************************
 * The AES extensions of MagiC
 */

/** an opaque structure. One should not access the
    structure directly. The mt_wdlg_xx functions should be used! */
typedef struct _dialog DIALOG;

/** EVNT structure */
#ifndef __EVNT
#define __EVNT
/** Event structure */
typedef struct
{
	short		mwhich;		/**< Type of events */
	short		mx;			/**< X-coordinate of the mouse cursor */
	short		my;			/**< Y-coordinate of the mouse cursor */
	short		mbutton; 	/**< Pressed mouse button */
	short		kstate;		/**< Status of the 'special' keys (kbshift) */
	short		key;		/**< Scancode of the pressed key */
	short		mclicks; 	/**< Number of mouse clicks */
	short		reserved[9];/**< Reserved */
	short		msg[16]; 	/**< Message-buffer */
} EVNT;
#endif


/** @addtogroup a_evnt
 *  @{
 */
void mt_EVNT_multi(short evtypes, short nclicks, short bmask, short bstate,
                    const MOBLK *m1, const MOBLK *m2, unsigned long ms, EVNT *event, short *global_aes );

/**@}*/

/*
 * Extensions to the form library (MagiC only)
 */

/** @addtogroup a_form
 *  @{
 */

/** SCANX structure */
#ifndef _SCANX
#define _SCANX
/** SCANX assignment, perform mouse click on an object when a key is pressed */
typedef struct
{
	char		scancode;	/**< scancode of the key */
	char		nclicks;	/**< mouse click to perform */
	short		objnr;		/**< object index number */
} SCANX;
#endif

/** XDO_INF strcture */
#ifndef _XDO_INF
#define _XDO_INF
/** XDO_INF contains pointers to tables that assign to a scancode an object index of the dialog box */
typedef struct
{
	SCANX		*unsh;		/**< table for unshifted keys */
	SCANX		*shift;		/**< table for shifted keys */
	SCANX		*ctrl;		/**< table for ctrl-key */
	SCANX		*alt; 		/**< table for alt-key */
	void		*resvd;		/**< reserved */
} XDO_INF;
#endif

/** parameters for the init callback function (7th parameter of mt_xfrm_popup() )
 */
struct POPUP_INIT_args
{
	OBJECT *tree;		/**< address of the object tree */
	short scrollpos;	/**< scroll position */
	short nlines;		/**< number of lines */
	void *param;		/**< user-defined parameter */
};

short	mt_form_popup 	(OBJECT *tree, short x, short y, short * global);
short	mt_form_wbutton	(OBJECT *fo_btree, short fo_bobject, short fo_bclicks, short *fo_bnxtobj, short whandle, short * global);
short	mt_form_wkeybd	(OBJECT *fo_ktree, short fo_kobject, short fo_kobnext, short fo_kchar, short *fo_knxtobject, short *fo_knxtchar, short whandle, short * global);
short	mt_form_xdial 	(short fo_diflag, short fo_dilittlx, short fo_dilittly, short fo_dilittlw, short fo_dilittlh, short fo_dibigx, short fo_dibigy, short fo_dibigw, short fo_dibigh, void **flydial, short * global);
short	mt_form_xdial_grect (short fo_diflag, const GRECT *fo_dilittl, const GRECT *fo_dibig, void **flydial, short * global);
short	mt_form_xdo		(OBJECT *tree, short startob, short *lastcrsr, XDO_INF *tabs, void *flydial, short * global);
short	mt_form_xerr	(long errcode, const char *errfile, short * global);
short	mt_xfrm_popup 	(OBJECT *tree, short x, short y, short firstscrlob, short lastscrlob, short nlines,
						 void __CDECL (*init)(struct POPUP_INIT_args),
						 void *param, short *lastscrlpos, short * global);
/**@}*/

/*
 * Extensions to the object library (MagiC only)
 */

/** @addtogroup a_objc
 *  @{
 */
void	mt_objc_wchange	(OBJECT *tree, short obj, short new_state, GRECT *clip, short whandle, short * global);
void	mt_objc_wdraw	(OBJECT *tree, short start, short depth, GRECT *clip, short whandle, short * global);
short	mt_objc_wedit	(OBJECT *tree, short obj, short key, short *idx, short kind, short whandle, short * global);
short	mt_objc_xedit	(OBJECT *tree, short obj, short key, short *xpos, short subfn, GRECT *r, short * global);
/**@}*/


/*
 * fnts_* font selection (MagiC/WDIALOG only)
 */

/** @addtogroup x_fnts
 *  @{
 */

/** opaque structure (internal management structure) */
typedef struct _fnt_dialog FNT_DIALOG;

/** parameters for UTXT_FN callback functions
 */
struct UTXT_FN_args
{
	short x;			/**< X-coordinate of the window's top left corner, or -1 (centered) */
	short y;			/**< Y-coordinate of the window's top left corner, or -1 (centered) */
	short *clip_rect;	/**< Clipping rectangle */
	long id;			/**< Font ID */
	long pt;			/**< Height in 1/65536 point */
	long ratio;			/**< Width/height ratio in 1/65536 */
	char *string;		/**< String */
};

/** void __CDECL (*UTXT_FN)(struct UTXT_FN_args) */
typedef void __CDECL (*UTXT_FN)(struct UTXT_FN_args);

/** FNTS_ITEM */
typedef struct _fnts_item FNTS_ITEM;

/** FNTS_ITEM data structure */
struct _fnts_item
{
	FNTS_ITEM	*next;		  /**< Pointer to the next font or 0L (end of the list) */
	UTXT_FN		display;	  /**< Pointer to the display function for the user fonts */
	long		id; 		  /**< Font ID, >= 65536 for user fonts */
	short 		index;		  /**< Must be 0, as not a VDI font */
	char		mono;		  /**< Flag for mono-spaced font */
	char		outline;	  /**< Flag for vector font */
	short 		npts;		  /**< Number of predefined point sizes */
	char		*full_name;   /**< Pointer to the complete name */
	char		*family_name; /**< Pointer to the family name */
	char		*style_name;  /**< Pointer to the style name */
	char		*pts; 		  /**< Pointer to field with point sizes */
	long		reserved[4];  /**< Reserved, must be 0 */
};

/* Definition of <font_flags> in mt_fnts_create() */
#define FNTS_BTMP 		1		    /**< Display bitmap fonts */
#define FNTS_OUTL 		2		    /**< Display vector fonts */
#define FNTS_MONO 		4		    /**< Display mono-spaced fonts */
#define FNTS_PROP 		8		    /**< Display proportional fonts */

/* Definition  of <dialog_flags> in mt_fnts_create() */
#define FNTS_3D			1			/**< Display selector in 3D-look */
#define FNTS_DISPLAY	2			/**< Display available display types (XaAES) */

/* Definition of <button_flags> in mt_fnts_open() */
#define FNTS_SNAME		0x01		/**< Select checkbox for names */
#define FNTS_SSTYLE		0x02		/**< Select checkbox for style */
#define FNTS_SSIZE		0x04		/**< Select checkbox for height  */
#define FNTS_SRATIO		0x08		/**< Select checkbox for width/height ratio */

#define FNTS_CHNAME		0x0100		/**< Display checkbox for names */
#define FNTS_CHSTYLE 	0x0200		/**< Display checkbox for style */
#define FNTS_CHSIZE		0x0400		/**< Display checkbox for height */
#define FNTS_CHRATIO 	0x0800		/**< Display checkbox for width/height ratio */
#define FNTS_RATIO		0x1000		/**< Width/height ratio adjustable */
#define FNTS_BSET 		0x2000		/**< Button "Set" selectable */
#define FNTS_BMARK		0x4000		/**< Button "Mark" selectable */

/* Definition of <button> in mt_fnts_evnt() */
#define FNTS_CANCEL		1			/**< Cancel button */
#define FNTS_OK			2			/**< OK button */
#define FNTS_SET		3			/**< Set button */
#define FNTS_MARK 		4			/**< Mark button */
#define FNTS_OPT		5			/**< Options button */
#define FNTS_OPTION		FNTS_OPT	/**< see FNTS_OPT */

short		mt_fnts_add			(FNT_DIALOG *fnt_dialog, FNTS_ITEM *user_fonts, short *global);
short		mt_fnts_close		(FNT_DIALOG *fnt_dialog, short *x, short *y, short *global);
FNT_DIALOG *mt_fnts_create		(short vdi_handle, short no_fonts, short font_flags, short dialog_flags, const char *sample, const char *opt_button, short *global);
short		mt_fnts_delete		(FNT_DIALOG *fnt_dialog, short vdi_handle, short *global);
short		mt_fnts_do			(FNT_DIALOG *fnt_dialog, short button_flags, long id_in, long pt_in, long ratio_in, short *check_boxes, long *id, long *pt, long *ratio, short *global);
short		mt_fnts_evnt		(FNT_DIALOG *fnt_dialog, EVNT *events, short *button, short *check_boxes, long *id, long *pt, long *ratio, short *global);
short		mt_fnts_get_info	(FNT_DIALOG *fnt_dialog, long id, short *mono, short *outline, short *global);
short		mt_fnts_get_name	(FNT_DIALOG *fnt_dialog, long id, char *full_name, char *family_name, char *style_name, short *global);
short		mt_fnts_get_no_styles (FNT_DIALOG *fnt_dialog, long id, short *global);
long		mt_fnts_get_style	(FNT_DIALOG *fnt_dialog, long id, short __index, short *global);
short		mt_fnts_open		(FNT_DIALOG *fnt_dialog, short button_flags, short x, short y, long id, long pt, long ratio, short *global);
void		mt_fnts_remove		(FNT_DIALOG *fnt_dialog, short *global);
short		mt_fnts_update		(FNT_DIALOG *fnt_dialog, short button_flags, long id, long pt, long ratio, short *global);
/**@}*/

/*
 * fslx_* file selection (MagiC only)
 */

#ifndef GEMLIB_XATTR
/* purec pctoslib defined __TOS in the file that defines the structure XATTR */
/* sozobonx xdlibs defined _file_h_ or _filesys_h_ in both files where the structure XATTR is defined */
/* in other case (XATTR not defined at this point), we go the old way and use "void" instead */
#  if defined(__TOS) || defined(_file_h_) || defined(_filesys_h_)
/** XATTR type used in XFSL_FILTER */
#    define GEMLIB_XATTR XATTR
#  else /* struct XATTR defined */
/** XATTR type used in XFSL_FILTER */
#    define GEMLIB_XATTR void
#  endif /* struct XATTR defined */
#endif /* GEMLIB_XATTR */

/** @addtogroup x_fslx
 *  @{
 */

/** short __CDECL (*XFSL_FILTER)(char *path, char *name, GEMLIB_XATTR *xattr) */
typedef short __CDECL (*XFSL_FILTER)(char *path, char *name, GEMLIB_XATTR *xattr);

/* sort modes */
#define SORTBYNAME		0			/**< Sort by name */
#define SORTBYDATE		1			/**< Sort by date */
#define SORTBYSIZE		2			/**< Sort by size */
#define SORTBYTYPE		3			/**< Sort by type */
#define SORTBYNONE		4			/**< Unsorted (physical order) */
#define SORTDEFAULT		(-1)		/**< Default mode saved in system (from MagiC 6.10 onwards) */

/* flags for file selection */
#define DOSMODE			1			/**< Compatibility mode that returns filenames in the 8.3 format */
#define NFOLLOWSLKS		2			/**< Symbolic links will not be followed */
#define GETMULTI		8			/**< If set, one can select and pass several files at the same time */

/* fslx_set_flags */
#define SHOW8P3			1			/**< Show TOS files as 8+3 (on DOS drives only) */

/** XFSL_DIALOG */
typedef struct _fslx_dialog XFSL_DIALOG;

short	mt_fslx_close		(XFSL_DIALOG *fsd, short *global);
XFSL_DIALOG *mt_fslx_do		(const char *title, char *path, short pathlen, char *fname, short fnamelen, const char *patterns, XFSL_FILTER filter, char *paths, short *sort_mode, short flags, short *button, short *nfiles, char **pattern, short *global);
short	mt_fslx_evnt		(XFSL_DIALOG *fsd, EVNT *events, char *path, char *fname, short *button, short *nfiles, short *sort_mode, char **pattern, short *global);
short	mt_fslx_getnxtfile	(XFSL_DIALOG *fsd, char *fname, short *global);
XFSL_DIALOG *mt_fslx_open	(const char *title, short x, short y, short *handle, char *path, short pathlen, char *fname, short fnamelen, const char *patterns, XFSL_FILTER filter, char *paths, short sort_mode, short flags, short *global);
short	mt_fslx_set_flags 	(short flags, short *oldval, short *global);
/**@}*/

/*
 * pdlg_* printer configuration dialogs (WDIALOG only)
 */

/** @addtogroup x_pdlg
 *  @{
 */

/** PRN_DIALOG */
typedef struct _prn_dialog PRN_DIALOG;

typedef struct _prn_tray		PRN_TRAY;			/**< PRN_TRAY */
typedef struct _media_size		MEDIA_SIZE;			/**< MEDIA_SIZE */
typedef struct _media_type		MEDIA_TYPE;			/**< MEDIA_TYPE */
typedef struct _prn_mode		PRN_MODE;			/**< PRN_MODE */
typedef struct _prn_entry		PRN_ENTRY;			/**< PRN_ENTRY */
typedef struct _dither_mode 	DITHER_MODE;		/**< DITHER_MODE */
typedef struct _drv_entry		DRV_ENTRY;			/**< DRV_ENTRY */
typedef struct _pdlg_sub		PDLG_SUB;			/**< PDLG_SUB */
typedef struct _prn_settings	PRN_SETTINGS;		/**< PRN_SETTINGS */

/** Description of a feed/output tray */
struct _prn_tray
{
	PRN_TRAY	*next;		/**< Pointer to next output tray description */
	long		tray_id; 	/**< Number of the feed or output tray */
	char		name[32];	/**< Name of the tray */
};

/** Description of a paper format */
struct _media_size
{
	MEDIA_SIZE	*next;		/**< Pointer to next paper format description */
	long		size_id; 	/**< Paper format size ID */
	char		name[32];	/**< Name of the paper format */
};

/** Description of a paper type/print medium */
struct _media_type
{
	MEDIA_TYPE	*next;		/**< Pointer to next print medium description */
	long		type_id; 	/**< Paper format type ID */
	char		name[32];	/**< Name of the paper format */
};

/** Description of a print mode */
struct _prn_mode
{
	PRN_MODE	*next; 				/**< Pointer to the next print mode */
	long		mode_id; 			/**< Mode ID (index within the file) */
	short 		hdpi; 				/**< Horizontal resolution in dpi */
	short 		vdpi; 				/**< Vertical resolution in dpi */
	long		mode_capabilities;	/**< Mode capabilities */
	long		color_capabilities;	/**< Color capabilities */
	long		dither_flags;		/**< Flags specifying whether the
	                                     corresponding color mode is accessible
										 with or without dithering */
	MEDIA_TYPE	*paper_types;		/**< Suitable paper types */
	long		reserved;			/**< Reserved */
	char		name[32];			/**< Mode name  */
};

/* sub_flags */
#define	PRN_STD_SUBS	0x0001			/**< standard sub-dialogs for NVDI printer */
#define	PRN_FSM_SUBS	0x0002			/**< standard sub-dialogs for FSM printer */
#define	PRN_QD_SUBS 	0x0004			/**< standard sub-dialogs for QuickDraw printer */

/** old_printer can also be 0L */
typedef long __CDECL (*PRN_SWITCH)(DRV_ENTRY *drivers, PRN_SETTINGS *settings, PRN_ENTRY *old_printer, PRN_ENTRY *new_printer);

/** Device description */
struct _prn_entry
{
	PRN_ENTRY	*next;					/**< Pointer to next device description */
	long		length; 				/**< Structure length */
	long		format; 				/**< Data format */
	long		reserved;				/**< Reserved */
	short 		driver_id;				/**< Driver ID */
	short 		driver_type;			/**< Driver type */
	long		printer_id; 			/**< Printer ID */
	long		printer_capabilities;	/**< Printer capabilities */
	long		reserved1;      /**< reserved */
	long		sub_flags;		/**< Various flags */
	PDLG_SUB	*sub_dialogs;	/**< Pointer to the list of sub-dialogs for this printer */
	PRN_SWITCH	setup_panel;	/**< Initialise sub-dialog at printer change  */
	PRN_SWITCH	close_panel;	/**< Close sub-dialog at printer change */
	PRN_MODE 	*modes;			/**< List of available resolutions */
	MEDIA_SIZE	*papers; 		/**< List of available paper formats */
	PRN_TRAY 	*input_trays;	/**< List of feed trays */
	PRN_TRAY 	*output_trays; 	/**< List of output trays */
	char		name[32];		/**< Name of the printer */
};

/** TODO */
struct _dither_mode
{
	DITHER_MODE	*next;			/**< Pointer to successor */
	long		length;			/**< Structure length */
	long		format;			/**< Data format */
	long		reserved;		/**< Reserved */
	long		dither_id;		/**< Dither ID */
	long		color_modes;	/**< Color depths supported */
	long		reserved1;		/**< Reserved */
	long		reserved2;		/**< Reserved */
	char		name[32];		/**< Name of the dither process */
};

/** Driver information structure */
typedef struct
{
	long		magic;			/**< 'pdnf' */
	long		length;			/**< Structure length */
	long		format;			/**< Data format */
	long		reserved;		/**< Reserved */
	short 		driver_id;		/**< Driver number for the VDI */
	short 		driver_type;	/**< Driver type */
	long		reserved1;		/**< Reserved */
	long		reserved2;		/**< Reserved */
	long		reserved3;		/**< Reserved */
	PRN_ENTRY	*printers;		/**< List of printers belonging to the driver */
	DITHER_MODE	*dither_modes; 	/**< List of dither processes supported by the driver */
	long		reserved4;		/**< Reserved */
	long		reserved5;		/**< Reserved */
	long		reserved6;		/**< Reserved */
	long		reserved7;		/**< Reserved */
	long		reserved8;		/**< Reserved */
	long		reserved9;		/**< Reserved */
	char		device[128];	/**< Printer driver output file */
} DRV_INFO;

/** Driver entry structure */
struct _drv_entry
{
	 DRV_ENTRY	*next; /**< Pointer to successor */
};

#define	PDLG_CHG_SUB	0x80000000L 	/**< Change sub-dialog */
#define	PDLG_IS_BUTTON	0x40000000L 	/**< Is button */

#define	PDLG_PREBUTTON	0x20000000L 	/**< TODO */
#define	PDLG_PB_OK		1 				/**< OK button */
#define	PDLG_PB_CANCEL	2 				/**< Cancel button */
#define	PDLG_PB_DEVICE	3 				/**< Device button */

#define	PDLG_BUT_OK 	(PDLG_PREBUTTON + PDLG_PB_OK) 		/**< OK button */
#define	PDLG_BUT_CNCL	(PDLG_PREBUTTON + PDLG_PB_CANCEL) 	/**< Cancel button */
#define	PDLG_BUT_DEV	(PDLG_PREBUTTON + PDLG_PB_DEVICE) 	/**< Change device */

/** Initialization function */
typedef long __CDECL (*PDLG_INIT)(PRN_SETTINGS *settings, PDLG_SUB *sub);

/** parameters for PDLG_HNDL callback functions
 */
struct PDLG_HNDL_args
{
	PRN_SETTINGS *settings;	/**< Settings */
	PDLG_SUB *sub;			/**< Sub-dialog */
	short exit_obj; 		/**< Exit object */
};

/** Handling function */
typedef long __CDECL (*PDLG_HNDL)(struct PDLG_HNDL_args);

/** Reset function */
typedef long __CDECL (*PDLG_RESET)(PRN_SETTINGS *settings, PDLG_SUB *sub);

/** Sub-dialog for setting device */
struct _pdlg_sub
{
	PDLG_SUB	*next; 			/**< Pointer to the successor in the list */
	long		length;			/**< Structure length */
	long		format;			/**< Data format */
	long		reserved;		/**< Reserved */
	void		*drivers;		/**< Only for internal dialogs */
	short 		option_flags;	/**< Flags, inc. PDLG_PRINTING, PDLG_PREFS */
	short 		sub_id;			/**< Sub-dialog ID, entered for global
                                     sub-dialogs of mt_pdlg_add() */
	void		*dialog; 		/**< Pointer to the structure of the window
                                     dialog or 0L */
	OBJECT		*tree;			/**< Pointer to the assembled object tree */
	short 		index_offset;	/**< Index offset of the sub-dialog */
	short 		reserved1;		/**< Reserved */
	long		reserved2;		/**< Reserved */
	long		reserved3;		/**< Reserved */
	long		reserved4;		/**< Reserved */
	PDLG_INIT	init_dlg;		/**< Initialisation function */
	PDLG_HNDL	do_dlg;			/**< Handling function */
	PDLG_RESET	reset_dlg;		/**< Reset function */
	long		reserved5;		/**< Reserved */
	OBJECT		*sub_icon;		/**< Pointer to the icon for the list box */
	OBJECT		*sub_tree;		/**< Pointer to the object tree of the
                                     sub-dialog */
	long		reserved6;		/**< Reserved */
	long		reserved7;		/**< Reserved */
	long		private1;		/**< Dialog's private information */
	long		private2;		/**< Dialog's private information */
	long		private3;		/**< Dialog's private information */
	long		private4;		/**< Dialog's private information */
};


/*----------------------------------------------------------------------------------------*/
/* einstellbare Farbmodi eines Druckermodus																*/
/*----------------------------------------------------------------------------------------*/
#define	CC_MONO			0x0001		/**< 2 Graut馬e */
#define	CC_4_GREY		0x0002		/**< 4 Graut馬e */
#define	CC_8_GREY		0x0004		/**< 8 Graut馬e */
#define	CC_16_GREY		0x0008		/**< 16 Graut馬e */
#define	CC_256_GREY 	0x0010		/**< 256 Graut馬e */
#define	CC_32K_GREY 	0x0020		/**< 32768 Farben in Graut馬e wandeln */
#define	CC_65K_GREY 	0x0040		/**< 65536 Farben in Graut馬e wandeln */
#define	CC_16M_GREY 	0x0080		/**< 16777216 Farben in Graut馬e wandeln */

#define	CC_2_COLOR		0x0100		/**< 2 Farben */
#define	CC_4_COLOR		0x0200		/**< 4 Farben */
#define	CC_8_COLOR		0x0400		/**< 8 Farben */
#define	CC_16_COLOR 	0x0800		/**< 16 Farben */
#define	CC_256_COLOR	0x1000		/**< 256 Farben */
#define	CC_32K_COLOR	0x2000		/**< 32768 Farben */
#define	CC_65K_COLOR	0x4000		/**< 65536 Farben */
#define	CC_16M_COLOR	0x8000		/**< 16777216 Farben */

#define	NO_CC_BITS		16			/**< TODO */

/*----------------------------------------------------------------------------------------*/
/* settable dither modes                                                                  */
/*----------------------------------------------------------------------------------------*/
#define	DC_NONE			0			/**< keine Rasterverfahren */
#define	DC_FLOYD 		1			/**< einfacher Floyd-Steinberg */
#define	NO_DC_BITS		1			/**< TODO */

/*----------------------------------------------------------------------------------------*/
/* printer characteristics                                                                */
/*----------------------------------------------------------------------------------------*/
#define PDLG_OUTFILES		5		/**< TODO */

#define	PC_FILE			0x0001		/**< printer can be accessed with GEMDOS calls */
#define	PC_SERIAL		0x0002		/**< printer can be attached to serial interface */
#define	PC_PARALLEL 	0x0004		/**< printer can be attached to parallel interface */
#define	PC_ACSI			0x0008		/**< printer can be attached to ACSI interface */
#define	PC_SCSI			0x0010		/**< printer can be attached to SCSI interface */

#define	PC_BACKGROUND	0x0080		/**< driver can do background jobs */

#define	PC_SCALING		0x0100		/**< driver can scale pages */
#define	PC_COPIES		0x0200		/**< driver can copy pages */

/*----------------------------------------------------------------------------------------*/
/* mode characteristics                                                                   */
/*----------------------------------------------------------------------------------------*/
#define	MC_PORTRAIT 	0x0001		/**< Seite kann im Hochformat ausgegeben werden */
#define	MC_LANDSCAPE	0x0002		/**< Seite kann im Querformat ausgegeben werden */
#define	MC_REV_PTRT 	0x0004		/**< Seite kann um 180 Grad gedreht im Hochformat ausgegeben werden */
#define	MC_REV_LNDSCP	0x0008		/**< Seite kann um 180 Grad gedreht im Querformat ausgegeben werden */
#define	MC_ORIENTATION	0x000f		/**< Orientation mask */

#define	MC_SLCT_CMYK	0x0400		/**< Treiber kann bestimmte Farbebenen ausgeben */
#define	MC_CTRST_BRGHT	0x0800		/**< Treiber kann Kontrast und Helligkeit ver�ndern */

/*----------------------------------------------------------------------------------------*/
/* plane_flags 																									*/
/*----------------------------------------------------------------------------------------*/
#define	PLANE_BLACK 	0x0001		/**< Black plane */
#define	PLANE_YELLOW	0x0002		/**< Yellow plane */
#define	PLANE_MAGENTA	0x0004		/**< Magenta plane */
#define	PLANE_CYAN		0x0008		/**< Cyan plane */
#define PLANE_MASK	(PLANE_BLACK|PLANE_YELLOW|PLANE_MAGENTA|PLANE_CYAN)		/**< Plane mask */


/* <driver_mode> */
#define	DM_BG_PRINTING	0x0001		/**< Flag for background printing */

/*----------------------------------------------------------------------------------------*/

/* <page_flags> */
#define  PG_EVEN_PAGES  0x0001  	/**< Only output pages with even page numbers */
#define  PG_ODD_PAGES   0x0002  	/**< Only output pages with odd page numbers */

/* <first_page/last_page> */
#define	PG_MIN_PAGE 	1			/**< First page to output */
#define	PG_MAX_PAGE 	9999		/**< Last page to output */

/* <orientation> */
#define  PG_UNKNOWN     0x0000  	/**< Orientation unknown and not adjustable */
#define  PG_PORTRAIT    0x0001  	/**< Output page in portrait format */
#define  PG_LANDSCAPE   0x0002  	/**< Output page in landscape format */

/** printer settings
 *
 *  The following structure items can be read by the application:
 *  - length
 *  - page_flags
 *  - first_page
 *  - last_page
 *  - no_copies
 *  - orientation
 *  - scale
 *  - driver_id
 *  .
 *  All other entries should not be accessed. Data such as the printer
 *  resolution or color planes, for instance, should not be taken from the
 *  settings structure but requested from the printer at the start of printing
 *  (it is possible, for instance, that the printer driver is forced by a
 *  shortage of memory to reduce the print resolution below the value entered
 *  in PRN_SETTINGS).
 */
struct _prn_settings
{
	long		magic;			/**< 'pset' */
	long		length;			/**< Structure length */
	long		format;			/**< Structure type */
	long		reserved;		/**< Reserved */

	long		page_flags; 	/**< Flags, inc. even pages, odd pages */
	short		first_page; 	/**< First page to be printed */
	short		last_page;		/**< Last page to be printed */
	short		no_copies;		/**< Number of copies */
	short		orientation;	/**< Orientation */
	long		scale;			/**< Scaling: 0x10000L corresponds to 100%  */

	short		driver_id;		/**< VDI device number */
	short		driver_type;	/**< Type of driver set */
	long		driver_mode;	/**< Flags, inc. for background printing */
	long		reserved1;		/**< Reserved */
	long		reserved2;		/**< Reserved */

	long		printer_id; 	/**< Printer number */
	long		mode_id; 		/**< Mode number */
	short		mode_hdpi;		/**< Horizontal resolution in dpi */
	short		mode_vdpi;		/**< Vertical resolution in dpi */
	long		quality_id; 	/**< Print mode (hardware-dependent quality,
                                     e.g. Microweave or Econofast) */

	long		color_mode; 	/**< Color mode */
	long		plane_flags;	/**< Flags for color planes to be output
                                     (e.g. cyan only) */
	long		dither_mode;	/**< Dither process */
	long		dither_value;	/**< Parameter for the dither process */

	long		size_id; 		/**< Paper format */
	long		type_id; 		/**< Paper type (normal, glossy) */
	long		input_id;		/**< Paper feed channel */
	long		output_id;		/**< Paper output channel */

	long		contrast;		/**< Contrast: 0x10000L corresponds to the
                                     normal setting */
	long		brightness; 	/**< Brightness: 0x1000L corresponds to the
                                     normal setting */
	long		reserved3;		/**< Reserved */
	long		reserved4;		/**< Reserved */

	long		reserved5;		/**< Reserved */
	long		reserved6;		/**< Reserved */
	long		reserved7;		/**< Reserved */
	long		reserved8;		/**< Reserved */

	char		device[128];	/**< File name to be printed  */

	struct	             		/**< Settings of the Mac printer driver */
	{
		char	inside[120];	/**< Content of settings of the Mac printer driver */
	} mac_settings;             /**< Settings of the Mac printer driver */
};


/* <dialog_flags> for mt_pdlg_create() */
#define PDLG_3D			0x0001      /**< Use 3D-look */

/* <option_flags> for mt_pdlg_open/do() */
#define PDLG_PREFS          0x0000  /**< Display settings dialog */
#define PDLG_PRINT          0x0001  /**< Display print dialog */

#define PDLG_ALWAYS_COPIES  0x0010  /**< Always offer No. of copies */
#define PDLG_ALWAYS_ORIENT  0x0020  /**< Always offer landscape format */
#define PDLG_ALWAYS_SCALE   0x0040  /**< Always offer scaling */

#define PDLG_EVENODD        0x0100  /**< Offer option for even and odd pages */

/* <button> for mt_pdlg_evnt()/mt_pdlg_do() */
#define	PDLG_CANCEL 1				/**< "Abbruch" wurde angew�hlt */
#define	PDLG_OK		2				/**< "OK" wurde gedr…kt */

short		   mt_pdlg_add_printers 		(PRN_DIALOG *prn_dialog, DRV_INFO *drv_info, short *global);
short		   mt_pdlg_add_sub_dialogs		(PRN_DIALOG *prn_dialog, PDLG_SUB *sub_dialogs, short *global);
short		   mt_pdlg_close	    		(PRN_DIALOG *prn_dialog, short *x, short *y, short *global);
PRN_DIALOG *   mt_pdlg_create				(short dialog_flags, short *global);
short		   mt_pdlg_delete		    	(PRN_DIALOG *prn_dialog, short *global);
short		   mt_pdlg_dflt_settings    	(PRN_DIALOG *prn_dialog, PRN_SETTINGS *settings, short *global);
short		   mt_pdlg_do			    	(PRN_DIALOG *prn_dialog, PRN_SETTINGS *settings, const char *document_name, short option_flags, short *global);
short		   mt_pdlg_evnt 		    	(PRN_DIALOG *prn_dialog, PRN_SETTINGS *settings, EVNT *events, short *button, short *global);
short		   mt_pdlg_free_settings    	(PRN_SETTINGS *settings, short *global);
long		   mt_pdlg_get_setsize      	(short *global);
PRN_SETTINGS * mt_pdlg_new_settings			(PRN_DIALOG *prn_dialog, short *global);
short		   mt_pdlg_open 			    (PRN_DIALOG *prn_dialog, PRN_SETTINGS *settings, const char *document_name, short option_flags, short x, short y, short *global);
short		   mt_pdlg_remove_printers      (PRN_DIALOG *prn_dialog, short *global);
short		   mt_pdlg_remove_sub_dialogs   (PRN_DIALOG *prn_dialog, short *global);
short		   mt_pdlg_save_default_settings(PRN_DIALOG *prn_dialog, PRN_SETTINGS *settings, short *global);
short		   mt_pdlg_update			    (PRN_DIALOG *prn_dialog, const char *document_name, short *global);
short		   mt_pdlg_use_settings 	    (PRN_DIALOG *prn_dialog, PRN_SETTINGS *settings, short *global);
short		   mt_pdlg_validate_settings    (PRN_DIALOG *prn_dialog, PRN_SETTINGS *settings, short *global);
/**@}*/


/******************************************************************************
 * Listbox definitions
 */

/** @addtogroup x_lbox
 *  @{
 */

 /** opaque structure */
typedef struct _list_box LIST_BOX;

typedef struct lbox_item LBOX_ITEM;		/**< List box item */

/** List box item structure */
struct lbox_item
{
	LBOX_ITEM	*next;		/**< Pointer to the next entry in the list */
	short		selected;	/**< Specifies if the object is selected */

	short		data1;		/**< Data for the program... */
	void		*data2; 	/**< Data for the program... */
	void		*data3; 	/**< Data for the program... */

};

/** parameters for SLCT_ITEM callback function */
struct SLCT_ITEM_args
{
	LIST_BOX *box;			/**< Points to the list box structure */
	OBJECT *tree;			/**< Points to the object tree of the dialog */
	struct lbox_item *item;	/**< Points to the LBOX_ITEM-structure of the selected entry */
	void *user_data;		/**< Is the pointer passed by lbox_create() */
	short obj_index;		/**< Is the number of the selected object */
	short last_state;		/**< Is the previous status of the object */
};

/** parameters for SET_ITEM callback function */
struct SET_ITEM_args
{
	LIST_BOX *box;			/**< Points to the list box structure */
	OBJECT *tree;			/**< Points to the object tree of the dialog */
	struct lbox_item *item;	/**< Points to the LBOX_ITEM structure of the entry to be set */
	short obj_index;		/**< Is the number of the object to be set */
	void *user_data;		/**< Is the pointer passed by lbox_create() */
	GRECT *rect;			/**< Is the pointer to the GRECT for the object redraw or 0L */
	short first;			/**< Contains the number of the first visible item for Slider B */
};

typedef void  __CDECL (*SLCT_ITEM)(struct SLCT_ITEM_args);		/**< Selection routine */
typedef short __CDECL (*SET_ITEM)(struct SET_ITEM_args);		/**< Set routine */

#define	LBOX_VERT		1	/**< Listbox with vertical slider */
#define	LBOX_AUTO		2	/**< Auto-scrolling */
#define	LBOX_AUTOSLCT		4	/**< Automatic display during auto-scrolling */
#define	LBOX_REAL		8	/**< Real-time slider */
#define	LBOX_SNGL		16	/**< Only a selectable entry */
#define	LBOX_SHFT		32	/**< Multi-selection with Shift */
#define	LBOX_TOGGLE		64	/**< Toggle status of an entry at selection */
#define	LBOX_2SLDRS		128	/**< Listbox has a horiz. and a vertical slider */

LIST_BOX *	mt_lbox_create (OBJECT *tree, SLCT_ITEM slct, SET_ITEM set,
		    LBOX_ITEM *items, short visible_a, short first_a,
		    const short *ctrl_objs, const short *objs, short flags,
		    short pause_a, void *user_data, DIALOG *dialog,
		    short visible_b, short first_b, short entries_b,
		    short pause_b, short *global);
void		mt_lbox_update (LIST_BOX *box, GRECT *rect, short *global);
short		mt_lbox_do (LIST_BOX *box, short obj, short *global);
short		mt_lbox_delete (LIST_BOX *box, short *global);
short		mt_lbox_cnt_items (LIST_BOX *box, short *global);
OBJECT *	mt_lbox_get_tree (LIST_BOX *box, short *global);
short		mt_lbox_get_visible (LIST_BOX *box, short *global);
void *		mt_lbox_get_udata (LIST_BOX *box, short *global);
short		mt_lbox_get_afirst (LIST_BOX *box, short *global);
short		mt_lbox_get_slct_idx (LIST_BOX *box, short *global);
LBOX_ITEM *	mt_lbox_get_items (LIST_BOX *box, short *global);
LBOX_ITEM *	mt_lbox_get_item (LIST_BOX *box, short n, short *global);
LBOX_ITEM *	mt_lbox_get_slct_item (LIST_BOX *box, short *global);
short		mt_lbox_get_idx (LBOX_ITEM *items, LBOX_ITEM *search, short *global);
short		mt_lbox_get_bvis (LIST_BOX *box, short *global);
short		mt_lbox_get_bentries (LIST_BOX *box, short *global);
short		mt_lbox_get_bfirst (LIST_BOX *box, short *global);
void		mt_lbox_set_asldr (LIST_BOX *box, short first, GRECT *rect, short *global);
void		mt_lbox_set_items (LIST_BOX *box, LBOX_ITEM *items, short *global);
void		mt_lbox_free_items (LIST_BOX *box, short *global);
void		mt_lbox_free_list (LBOX_ITEM *items, short *global);
void		mt_lbox_ascroll_to (LIST_BOX *box, short first, GRECT *box_rect,
		    GRECT *slider_rect, short *global);
void		mt_lbox_set_bsldr (LIST_BOX *box, short first, GRECT *rect, short *global);
void		mt_lbox_set_bentries (LIST_BOX *box, short entries, short *global);
void		mt_lbox_bscroll_to (LIST_BOX *box, short first, GRECT *box_rect,
   		    GRECT *slider_rect, short *global);

/* #defines for listboxes with only one slider */
#define	mt_lbox_get_avis			mt_lbox_get_visible	/**< another name for mt_lbox_get_avis */
#define	mt_lbox_get_first			mt_lbox_get_afirst	/**< another name for mt_lbox_get_first */
#define	mt_lbox_set_slider			mt_lbox_set_asldr	/**< another name for mt_lbox_set_slider */
#define	mt_lbox_scroll_to			mt_lbox_ascroll_to	/**< another name for mt_lbox_scroll_to */
/**@}*/

/******************************************************************************
 * Wdialog definitions
 */

/** @addtogroup x_wdlg
 *  @{
 */

/** parameters of HNDL_OBJ callback functions */
struct HNDL_OBJ_args 
{
	DIALOG *dialog;	/**< Pointer to a dialog structure. One should not access the structure directly; the wdlg_xx functions should be used! */
	EVNT *events;	/**< If obj is an object number (>=0), then events points to the EVNT structure that was passed by wdlg_evnt; otherwise events is basically 0L and can not be used for addressing */
	short obj;		/**< Object number (>=0) or function number (<0) */
	short clicks;	/**< Number of mouse clicks (if obj is an object number) */
	void *data;		/**< If the parameter obj is a positive object number, then the variable user_data from wdlg_create() function will be passed here; otherwise the value depends on the corresponding function number */
};

/** service routine that is called, among others, by mt_wdlg_evnt().
 *
 *  This function may be called if an exit or touchexit
 *  object was clicked on (in that case \p obj is a positive object number)
 *  or when an event has occurred that affects the dialog (in that case
 *  \p obj is negative and contains a corresponding function number such as
 *  HNDL_CLSD, for instance).
 *
 *  If \p obj is an object number (>= 0), then \p events points to
 *  the EVNT structure that was passed by mt_wdlg_evnt().
 *  Otherwise \p events is basically 0L and can  not be used for addressing.
 *
 *  \p clicks contains then number of mouse clicks (if \p obj is an object number)
 *
 *  Here is a list of event (value given in the \p obj parameter):
 *  - HNDL_INIT (-1) : \n
 *	  \p data is the variable passed by wdlg_create.
 *	  If handle_exit() returns 0, mt_wdlg_create() does not
 *	  create a dialog structure (error).
 *	  The variable \p code is passed in \p clicks.
 *  - HNDL_OPEN (-5) : \n
 *    \p data is the variable passed by wdlg_open.
 *    The variable \p code is passed in \p clicks.
 *  - HNDL_CLSD (-3) : \n
 *    \p data is \p user_data. If handle_exit() returns 0,
 *    the dialog will be closed -- mt_wdlg_evnt() returns 0
 *    \p events points to the EVNT structure passed by
 *    mt_wdlg_evnt().
 *  - HNDL_MOVE (-9) : \n
 *    \p data is \p user_data. If handle_exit() returns 0,
 *    the dialog will be closed -- mt_wdlg_evnt() returns 0.
 *    \p events points to the EVNT structure passed by
 *    mt_wdlg_evnt().
 *  - HNDL_TOPW (-10) : \n
 *    \p data is \p user_data. If handle_exit() returns 0,
 *    the dialog will be closed -- mt_wdlg_evnt() returns 0.
 *    \p events points to the EVNT structure passed by
 *    mt_wdlg_evnt().
 *  - HNDL_UNTP (-11) : \n
 *    \p data is \p user_data. If handle_exit() returns 0,
 *    the dialog will be closed -- mt_wdlg_evnt() returns 0.
 *    \p events points to the EVNT structure passed by
 *    mt_wdlg_evnt().
 *  - HNDL_EDIT (-6) : \n
 *    \p data points to a word with the key code.
 *    If handle_exit() returns 1, the key press will be
 *    evaluated, if 0 ignored.
 *    \p events points to the EVNT structure passed by
 *    mt_wdlg_evnt().
 *  - HNDL_EDDN (-7) : \n
 *    \p data points to a word with the key code.
 *    \p events points to the EVNT structure passed by
 *    mt_wdlg_evnt().
 *  - HNDL_EDCH (-8) : \n
 *    \p data points to a word with the object number of
 *    the new editable field.
 *  - HNDL_MESG (-2) : \n
 *    \p data is \p user_data. If handle_exit() returns 0,
 *    the dialog will be closed -- mt_wdlg_evnt() returns 0.
 *    \p events points to the EVNT structure passed by
 *    mt_wdlg_evnt().	\n
 *    HNDL_MESG is only passed if a message code between
 *    20 and 39 was received that is not handled by other
 *    opcodes.
 *    Is required for iconification, for instance.\n
 *    Warning: This opcode is only present from MagiC 4.5
 *    of 18.4.96
 *  .
 *  Of these function numbers one only has to react to HNDL_CLSD. All other
 *  events need only be paid attention to when needed.\n
 *  If handle_exit is called with an unknown function number in \p obj, or
 *  one of the above function numbers is to be ignored, then 1 has to be
 *  returned.
 *
 *  The parameters are passed via the stack and the routine may alter
 *  registers d0-d2/a0-a2.
 */
typedef short __CDECL (*HNDL_OBJ)(struct HNDL_OBJ_args);

DIALOG * mt_wdlg_create			(HNDL_OBJ handle_exit, OBJECT *tree, void *user_data, short code, void *data, short flags, short *global);
short	 mt_wdlg_open			(DIALOG *dialog, const char *title, short kind, short x, short y, short code, void *data, short *global);
short	 mt_wdlg_close			(DIALOG *dialog, short *x, short *y, short *global);
short	 mt_wdlg_delete			(DIALOG *dialog, short *global);
short	 mt_wdlg_get_tree		(DIALOG *dialog, OBJECT **tree, GRECT *r, short *global);
short	 mt_wdlg_get_edit		(DIALOG *dialog, short *cursor, short *global);
void *	 mt_wdlg_get_udata		(DIALOG *dialog, short *global);
short	 mt_wdlg_get_handle		(DIALOG *dialog, short *global);
short	 mt_wdlg_set_edit		(DIALOG *dialog, short obj, short *global);
short	 mt_wdlg_set_tree		(DIALOG *dialog, OBJECT *tree, short *global);
short	 mt_wdlg_set_size		(DIALOG *dialog, GRECT *size, short *global);
short	 mt_wdlg_set_iconify	(DIALOG *dialog, GRECT *g, const char *title, OBJECT *tree, short obj, short *global);
short	 mt_wdlg_set_uniconify	(DIALOG *dialog, GRECT *g, const char *title, OBJECT *tree, short *global);
short	 mt_wdlg_evnt			(DIALOG *dialog, EVNT *events, short *global );
void	 mt_wdlg_redraw			(DIALOG *dialog, GRECT *rect, short obj, short depth, short *global);

/* Definitions for <flags> */
#define  WDLG_BKGD   1           /**< Permit background operation */

/* Function numbers for <obj> with handle_exit(...) */
#define  HNDL_INIT   (-1)          /**< Initialise dialog */
#define  HNDL_MESG   (-2)          /**< Handle message */
#define  HNDL_CLSD   (-3)          /**< Dialog window was closed */
#define  HNDL_OPEN   (-5)          /**< End of dialog initialisation (second  call at end of wdlg_init) */
#define  HNDL_EDIT   (-6)          /**< Test characters for an edit-field */
#define  HNDL_EDDN   (-7)          /**< Character was entered in edit-field */
#define  HNDL_EDCH   (-8)          /**< Edit-field was changed */
#define  HNDL_MOVE   (-9)          /**< Dialog was moved */
#define  HNDL_TOPW   (-10)         /**< Dialog-window has been topped */
#define  HNDL_UNTP   (-11)         /**< Dialog-window is not active */
/**@}*/


/*
 *    Editor extensions for Magic
 */

/** @addtogroup x_edit
 *  @{
 */
typedef void XEDITINFO; /**< opaque data structure use by mt_edit_create() and mt_edit_delete() */
XEDITINFO *	mt_edit_create 	(short *global);
void	mt_edit_delete 		(XEDITINFO *xi, short *global);
short	mt_edit_open		(OBJECT *tree, short obj, short *global);
void	mt_edit_close		(OBJECT *tree, short obj, short *global);
short	mt_edit_cursor 		(OBJECT *tree, short obj, short whdl, short show, short *global);
short	mt_edit_evnt		(OBJECT *tree, short obj, short whdl,	EVNT *ev, long *errc, short *global);
short	mt_edit_get_buf		(OBJECT *tree, short obj, char **buf, long *buflen, long *txtlen, short *global);
short	mt_edit_get_format	(OBJECT *tree, short obj, short *tabwidth, short *autowrap, short *global);
short	mt_edit_get_colour	(OBJECT *tree, short obj, short *tcolor, short *bcolor, short *global);
/** another name, with "color" instead of "colour" to be consistent with AES/VDI function naming rules */
#define mt_edit_get_color	mt_edit_get_colour
short	mt_edit_get_cursor	(OBJECT *tree, short obj, char **cursorpos, short *global);
short	mt_edit_get_font	(OBJECT *tree, short obj, short *fontID, short *fontH, short *fontPix, short *mono, short *global);
void	mt_edit_set_buf		(OBJECT *tree, short obj, char *buf, long buflen, short *global);
void	mt_edit_set_format	(OBJECT *tree, short obj, short tabwidth, short autowrap, short *global);
void	mt_edit_set_font	(OBJECT *tree, short obj, short fontID, short fontH, short fontPix, short mono, short *global);
void	mt_edit_set_colour	(OBJECT *tree, short obj, short tcolor, short bcolor, short *global);
/** another name, with "color" instead of "colour" to be consistent with AES/VDI function naming rules */
#define mt_edit_set_color	mt_edit_set_colour
void	mt_edit_set_cursor	(OBJECT *tree, short obj, char *cursorpos, short *global);
short	mt_edit_resized		(OBJECT *tree, short obj, short *oldrh, short *newrh, short *globalo);
short	mt_edit_get_dirty	(OBJECT *tree, short obj, short *global);
void	mt_edit_set_dirty	(OBJECT *tree, short obj, short dirty, short *global);
void	mt_edit_get_sel		(OBJECT *tree, short obj, char **bsel, char **esel, short *global);
void	mt_edit_get_pos		(OBJECT *tree, short obj, short *xscroll, long *yscroll, char **cyscroll, char **cursorpos, short *cx, short *cy, short *global);
void	mt_edit_set_pos		(OBJECT *tree, short obj, short xscroll, long yscroll, char *cyscroll, char *cursorpos, short cx, short cy, short *global);
short	mt_edit_scroll		(OBJECT *tree, short obj, short whdl, long yscroll, short xscroll, short *global);
void	mt_edit_get_scrollinfo (OBJECT *tree, short obj, long *nlines, long *yscroll, short *yvis, short *yval, short *ncols, short *xscroll, short *xvis, short *global);
/**@}*/

/*
 * Geneva extensions
 */

/** @addtogroup geneva
 *  @{
 */

/** Geneva cookie */
#ifndef GENEVA_COOKIE
#define GENEVA_COOKIE   0x476E7661L     /**< "Gnva" */
#define GENEVA_VER      0x0106          /**< current Geneva version */
/** Geneva cookie structure */
typedef struct
{
	short ver;			/**< Geneva version */
	char *process_name;		/**< Points to the name of the process currently using Geneva */
	short apid;			/**< Application ID of the process */
	short (**aes_funcs)(void);	/**< Internal table of AES functions */
	short (**xaes_funcs)(void);	/**< Internal table of extended functions */
	struct G_vectors *vectors;	/**< rel 004 */
} G_COOKIE;

typedef struct G_vectors		/**< Vectors used by Geneva, rel 004 */
{
	short used;			/**< Bitmap of which vectors in the rest of the structure are used. Currently this is 7 */
	short (*keypress)(long *key);	/**< Called whenever Geneva receives a key from the keyboard */
	short (*app_switch)(const char *process_name, short apid);	/**< Called whenever the user performs some action that causes the topmost application to change */
	short (*gen_event)(void);	/**< Called continually by Geneva to poll a certain condition and generate an event if something occurs */
} G_VECTORS;
#endif

/********************** form_do/objc_edit **********************/
/* Value for long edits into TEDINFO->te_tmplen */
#define X_LONGEDIT      -71     /**< rel 004 */

/** Animated mouse shape */
typedef struct
{
	short frames;		/**< Number of frames in shape */
	short delay;		/**< 60Hz ticks to pause between frames */
	MFORM form[32];		/**< List of mouse forms */
} ANI_MOUSE;
#define X_SET_SHAPE     1100    /**< Add to mouse shape index to change shape */

/************************** objc_draw **************************/
#define X_MAGMASK       0xF000 /**< ob_state: Mask for X_MAGIC                  */
#define X_MAGIC         0x9000 /**<           Must be set this way              */
#define X_PREFER        0x0040 /**<           User-defined fill                 */
#define X_DRAW3D        0x0080 /**<           3D                                */
#define X_ROUNDED       0x0100 /**<           Rounded                           */
#define X_KBD_EQUIV     0x0200 /**<           Scan for ['s; Root: no auto equivs*/
#define X_SMALLTEXT     0x0400 /**<           Small font                        */
#define X_SHADOWTEXT    0x0800 /**<           Shadowed text (rel 004)           */
#define X_BOLD          0x4000 /**< ob_flags: With X_MAGIC, bold text           */
#define X_ITALICS       0x8000 /**<           With X_MAGIC, italic text         */
/* Extended ob_types */
#define X_MOVER         17     /**< Dialog mover box                            */
#define X_RADCHKUND     18     /**< Radio/check/Undo                            */
#define X_UNDERLINE     19     /**< Title (G_STRING)                            */
#define X_GROUP         20     /**< Group (G_BUTTON)                            */
#define X_HELP          21     /**< Activated with Help key                     */
#define X_UNDO          31     /**< Activated with Undo key                     */
#define X_USRDEFPRE     90     /**< With X_MAGIC, call USERBLK before drawing   */
#define X_USRDEFPOST    91     /**< With X_MAGIC, call USERBLK after drawing    */
#define X_GRAYMENU      92     /**< root object: draw DISABLED G_STRING children in gray (rel 004) */

/************************** x_settings *************************/
#define SET_VER         0x0106   /**< the last time SETTINGS changed */

/** Keypress description structure */
typedef struct
{
	unsigned char shift;	/**< State of special keys */
	unsigned char scan;	/**< Scancode or zero */
	unsigned char ascii;	/**< ASCII value or zero */
} KEYCODE;

/** Extended object description */
typedef union
{
	struct
	{
		unsigned outlined   :1;	/**< Object is OUTLINED */
		unsigned shadowed   :1;	/**< Object is SHADOWED */
		unsigned draw_3D    :1;	/**< Object is drawn in 3D */
		unsigned rounded    :1;	/**< Object has rounded corners */
		unsigned atari_3D   :1;   /**< TODO rel 004 */
		unsigned shadow_text:1;   /**< TODO rel 004 */
		unsigned bold_shadow:1;   /**< TODO rel 004 */
		unsigned reserved   :9;	/**< Reserved for future use */
		unsigned framecol   :4;	/**< Color of frame */
		unsigned textcol    :4;	/**< Color of text */
		unsigned textmode   :1;	/**< 0: transparent, 1:replace */
		unsigned fillpattern:3;	/**< Fill pattern index */
		unsigned interiorcol:4;	/**< Color of interior */
	} s; /**< Bitmapped flags */
	unsigned long l;		/**< Longword for accessing all flags */
} OB_PREFER;

/** parameters for x_settings() */
typedef struct Settings
{
	short version;		/**< Version SETTINGS is for, in BCD */
	short struct_len;	/**< Total # of bytes in SETTINGS */
	short boot_rez;		/**< ST/TT resolution at startup */
	short falcon_rez;	/**< Falcon video mode at startup */
	union
	{
		struct
		{
			unsigned pulldown          :1;	/**< 1: use pulldown menus */
			unsigned insert_mode       :1;	/**< 1: insert in dialog edits */
			unsigned long_titles       :1;	/**< long underlines X_UNDERLINE */
			unsigned alerts_under_mouse:1;	/**< alerts appear under mouse */
			unsigned fsel_1col         :1;	/**< 1 column in item selector */
			unsigned grow_shrink       :1;	/**< 1: FMD_GROW/SHRINK on */
			unsigned tear_aways_topped :1;	/**< 1: tear aways always usable */
			unsigned auto_update_shell :1;  /**< TODO */
			unsigned alert_mode_change :1;  /**< TODO */
			unsigned ignore_video_mode :1;  /**< TODO */
			unsigned no_alt_modal_equiv:1;	/**< rel 004 */
			unsigned no_alt_modeless_eq:1;	/**< rel 004 */
			unsigned preserve_palette  :1;	/**< rel 004 */
			unsigned mouse_on_off      :1;	/**< rel 004 */
			unsigned top_all_at_once   :1;	/**< rel 005 */
			unsigned child_pexec_single:1;	/**< rel 006: undocumented */
		} s;					/**< Bitmapped flags */
		unsigned short i;			/**< Word for accessing all flags */
	} flags;					/**< Preferences */
	short gadget_pause;						/**< 50 Hz timer tics */
	KEYCODE menu_start;			/**< Key to start menus */
	KEYCODE app_switch;			/**< Key to toggle between apps */
	KEYCODE app_sleep;                      /**< TODO */
	KEYCODE ascii_table;			/**< Key to open ASCII table */
	KEYCODE redraw_all;			/**< Key to redraw whole screen */
	KEYCODE wind_keys[13];			/**< Keys for window events */
	OB_PREFER color_3D[4];			/**< Colors for 3D objects */
	OB_PREFER color_root[4];		/**< Colors for root objects */
	OB_PREFER color_exit[4];		/**< Colors for EXIT objects */
	OB_PREFER color_other[4];		/**< Colors for other objects */
	char sort_type;				/**< fsel sort type, 0(name) - 4(None) */
	char find_file[26];			/**< fsel Search string */
	char fsel_path[10][35];			/**< Item Selector paths */
	char fsel_ext[10][6];			/**< Item Selector extension strings */
	KEYCODE cycle_in_app;		            /**< TODO rel 004 */
	KEYCODE iconify;                        /**< TODO rel 004 */
	KEYCODE alliconify;                     /**< TODO rel 004 */
	KEYCODE procman;                        /**< TODO rel 006 */
	KEYCODE unused[4];                      /**< unused */
	char graymenu;	                        /**< TODO rel 004 */
	char reserved;                          /**< reserved */
	union
	{
		struct
		{
			unsigned procman_details  :1;
			unsigned reserved         :15;
			unsigned reserved2        :16;
		} s;
		unsigned long l;
	} flags2;				                /**< rel 006 */
} SETTINGS;

#define XS_UPPAGE WA_UPPAGE	/**< Index for up page key */
#define XS_DNPAGE WA_DNPAGE	/**< Index for down page key */
#define XS_UPLINE WA_UPLINE	/**< Index for up line key */
#define XS_DNLINE WA_DNLINE	/**< Index for down line key */
#define XS_LFPAGE WA_LFPAGE	/**< Index for page left key */
#define XS_RTPAGE WA_RTPAGE	/**< Index for page right key */
#define XS_LFLINE WA_LFLINE	/**< Index for line left key */
#define XS_RTLINE WA_RTLINE	/**< Index for line right key */
#define XS_CLOSE		8	/**< Index for close box key */
#define XS_CYCLE		9	/**< Index for cycle window key */
#define XS_FULL			10	/**< Index for full window key */
#define XS_LFINFO		11	/**< Index for info left key */
#define XS_RTINFO		12	/**< Index for info right key */

short mt_x_settings(short getset, short length, SETTINGS *user, short *global);

/************************ x_shel_get/put ************************/
#define X_SHLOADSAVE    -1      /**< Load/save SETTINGS */
#define X_SHOPEN        0       /**< Start read/write   */
#define X_SHACCESS      1       /**< Read/write         */
#define X_SHCLOSE       2       /**< Close              */


short mt_x_shel_get(short mode, short length, char *buf, short *global);
short mt_x_shel_put(short mode, const char *buf, short *global);

/***************** x_wind_create, x_wind_calc *******************/
#define X_MENU		0x0001	/**< Extended window type to attach a menu bar to a window */
#define X_HSPLIT	0x0002	/**< Extended window type to add a horizontal split bar to a window */
#define X_VSPLIT	0x0004	/**< Extended window type to add a vertical split bar to a window */

short mt_x_wind_create(short kind, short xkind, short wx, short wy, short ww, short wh, short *global);
short mt_x_wind_calc(short type, short kind, short xkind, short inx, short iny,  short inw, short inh,
	short *outx, short *outy, short *outw, short *outh, short *global);

/************************** x_wind_tree *************************/
/** Window tree structure for x_wind_tree() */
typedef struct WindTree
{
	short handle;	/**< Handle of window */
	short count;	/**< Number of objects in window */
	short flag;	/**< Location to copy to/from */
	OBJECT *tree;	/**< Pointer to object tree */
} WIND_TREE;

#define X_WT_GETCNT     0       /**< Get count and flag */
#define X_WT_READ       1       /**< Copy window tree   */
#define X_WT_SET        2       /**< Set new tree       */

#define X_WTFL_RESIZE   1       /**< Flags bit 0: Auto resize                  */
#define X_WTFL_CLICKS   2       /**<           1: Process clicks               */
#define X_WTFL_SLIDERS  4       /**<           2: Resize sliders, info         */

/* window gadgets */
#define WGCLOSE   1   /**< BOXCHAR */
#define WGMOVE    2   /**< BOXTEXT */
#define WGICONIZ  3   /**< BOXCHAR */
#define WGBACK    4   /**< BOXCHAR */
#define WGFULL    5   /**< BOXCHAR */
#define WGILEFT   6   /**< BOXCHAR */
#define WGINFO    7   /**< BOXTEXT */
#define WGIRT     8   /**< BOXCHAR */
#define WGTOOLBOX 9   /**< IBOX */
#define WGMNLEFT  10  /**< BOXCHAR */
#define WGMENU    11  /**< BOX */
#define WGMNRT    12  /**< BOXCHAR */
#define WGUP      13  /**< BOXCHAR */
#define WGVBIGSL  14  /**< BOX */
#define WGVSMLSL  15  /**< BOX */
#define WGDOWN    16  /**< BOXCHAR */
#define WGVSPLIT  17  /**< BOX */
#define WGUP2     18  /**< BOXCHAR */
#define WGVBIGSL2 19  /**< BOX */
#define WGVSMLSL2 20  /**< BOX */
#define WGDOWN2   21  /**< BOXCHAR */
#define WGLEFT    22  /**< BOXCHAR */
#define WGHBIGSL  23  /**< BOX */
#define WGHSMLSL  24  /**< BOX */
#define WGRT      25  /**< BOXCHAR */
#define WGHSPLIT  26  /**< BOX */
#define WGLEFT2   27  /**< BOXCHAR */
#define WGHBIGSL2 28  /**< BOX */
#define WGHSMLSL2 29  /**< BOX */
#define WGRT2     30  /**< BOXCHAR */
#define WGSIZE    31  /**< BOXCHAR */

short mt_x_wind_tree(short mode, WIND_TREE *wt, short *global);

/************************* x_appl_flags *************************/
/** Application bit flags */
typedef union
{
	struct
	{
		unsigned multitask    :1;	/**< 1: Multitasking */
		unsigned special_types:1;	/**< 1: Use extended objects types */
		unsigned round_buttons:1;	/**< 1: Use rounded EXIT buttons */
		unsigned kbd_equivs   :1;	/**< 1: Use auto keyboard equivs */
		unsigned undo_equivs  :1;	/**< 1: Undraw when form_do exits */
		unsigned off_left     :1;	/**< 1: Allow windows off left edge */
		unsigned exit_redraw  :1;	/**< 1: Redraw everything at quit */
		unsigned AES40_msgs   :1;	/**< 1: New messages for AES 4.0 OK */
		unsigned limit_handles:1;	/**< 1: Limit window handles to 1-7 */
		unsigned limit_memory :1;	/**< 1: Limit Malloc's */
		unsigned keep_deskmenu:1;	/**< 1: Keep desktop/menu nar */
		unsigned clear_memory :1;	/**< 1: Clear Malloc'd memory */
		unsigned maximize_wind:1;	/**< 1: Omit unnecessary gadgets */
		unsigned optim_redraws:1;	/**< 1: Optimize redraws, rel 004 */
		unsigned unused       :2;   /* Reserved for future use */
		unsigned mem_limit    :16;  /* Kb to limit memory allocation */
	} s; /**< Bitmapped flags */
	unsigned long l; /**< Longword for accessing all flags */
} APFLG;

/** Application flags */
typedef struct
{
	char name[13];		/**< Filename pattern to use these flags */
	char desc[17];		/**< User-defined description flags */
	APFLG flags;		/**< Execution flags */
	KEYCODE open_key;	/**< Open application when this key is pressed */
	KEYCODE reserve_key[3];	/**< Application uses these keys, so don't let Geneva process them */
} APPFLAGS;

#define X_APF_GET_INDEX	0	/**< Get the Nth block of global application flags */
#define X_APF_SET_INDEX	1	/**< Set the Nth block of global application flags */
#define X_APF_DEL_INDEX	2	/**< Delete the Nth block of global application flags */
#define X_APF_GET_ID	3	/**< Get the application flags for a particular process */
#define X_APF_SET_ID	4	/**< Set the application flags for a particular process */
#define X_APF_SEARCH	5	/**< TODO rel 004 */

short mt_x_appl_flags(short getset, short index, APPFLAGS *flags, short *global);

/*********************** x_appl_font ****************************/
/** Font being used and window gadget borders */
typedef struct
{
	short font_id;		/**< VDI font ID */
	short point_size;	/**< Point size of the font */
	short gadget_wid;	/**< Width of border around a char in a window gadget */
	short gadget_ht;	/**< Height of border around a char in a window gadget */
} XFONTINFO;

short mt_x_appl_font(short getset, short zero, XFONTINFO *info, short *global);

short mt_x_appl_term(short apid, short retrn, short set_me, short *global);
short mt_x_appl_trecord(void *mem, short count, KEYCODE *cancel, short mode, short *global);
short mt_x_appl_tplay(void *mem, short num, short scale, short mode, short *global);
short mt_x_appl_sleep(short id, short _sleep, short *global);
short mt_x_form_center(OBJECT *tree, short *cx, short *cy, short *cw, short *ch, short *global);
short mt_x_form_error(const char *fmt, short num, short *global);
short mt_x_form_filename(OBJECT *tree, short obj, short to_from, char *string, short *global);
short mt_x_form_mouse(OBJECT *tree, short mouse_x, short mouse_y, short clicks,
     short *edit_obj, short *next_obj, short *edit_idx, short *global);
short mt_x_fsel_input(char *inpath, short pathlen, char *insel, short sels,
     short *exbutton, const char *label, short *global);
short mt_x_graf_blit(GRECT *r1, GRECT *r2, short *global);
short mt_x_graf_rubberbox(GRECT *area, GRECT *outer, short minwidth,
     short minheight, short maxwidth, short maxheight, short snap, short lag, short *global);
void mt_x_graf_rast2rez(unsigned short *src_data, long plane_len,
     short old_planes, MFDB *mfdb, short devspef, short *global);         /* rel 004 */
short mt_x_help(const char *topic, const char *helpfile, short sensitive, short *global);
void mt_x_malloc(void **addr, long size, short *global);                /* rel 004 */
short mt_x_mfree(void *addr, short *global);                             /* rel 004 */
short mt_x_mshrink(void *addr, long newsize, short *global);                 /* rel 004 */
short mt_x_realloc(void **addr, long size, short *global);               /* rel 004 */
short mt_x_objc_edit(OBJECT *tree, short edit_obj, short key_press,
     short shift_state, short *edit_idx, short mode, short *global);
short mt_x_scrp_get(char *out, short deleteit, short *global);               /* rel 004 */
short mt_x_wdial_draw(short handle, short start, short depth, short *global);
short mt_x_wdial_change(short handle, short object, short newstate, short *global);

/* these two are only available with -mshort, because otherwise size of int does not match */
#ifdef __MSHORT__
void mt_x_sprintf(char *buf, const char *fmt, ...);
void mt_x_sscanf(const char *buf, const char *fmt, ...);
#endif


/**@}*/

/*******************************************************************************
 * The VDI extensions of NVDI/FSM/Speedo
 */

/*
 * The following functions requires EdDI version 1.x or higher
 */

/** @addtogroup n_vdi
 *  @{
 */
void	v_clsbm		(short handle);
void	v_opnbm		(short *work_in, MFDB *bitmap, short *handle, short *work_out);
void	vq_scrninfo	(short handle, short *work_out);
/**@}*/

/** UDEF version of v_clsbm(). See \ref overviewUDEF for details about UDEF feature */
#define udef_v_clsbm v_clsbm
/** UDEF version of v_opnbm(). See \ref overviewUDEF for details about UDEF feature */
#define udef_v_opnbm v_opnbm
/** UDEF version of vq_scrninfo(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vq_scrninfo vq_scrninfo


/*
 * The following functions requires NVDI version 2.x or higher
 */

/** @addtogroup n_vdi
 *  @{
 */
short	v_bez_on	(short handle);
void	v_bez_off	(short handle);
void	v_bez		(short handle, short count, short *xyarr, char *bezarr, short *extent, short *totpts, short *totmoves);
void	v_bez_fill	(short handle, short count, short *xyarr, char *bezarr, short *extent, short *totpts, short *totmoves);
short 	v_bez_qual	(short handle, short percent, short *actual);
/**@}*/

/** UDEF version of (). See \ref overviewUDEF for details about UDEF feature */
#define udef_v_bez_on v_bez_on
/** UDEF version of (). See \ref overviewUDEF for details about UDEF feature */
#define udef_v_bez_off v_bez_off
/** @ingroup force_udef */
void	udef_v_bez		(short handle, short count, short *xyarr, char *bezarr, short *extent, short *totpts, short *totmoves);
/** @ingroup force_udef */
void	udef_v_bez_fill	(short handle, short count, short *xyarr, char *bezarr, short *extent, short *totpts, short *totmoves);
/** UDEF version of (). See \ref overviewUDEF for details about UDEF feature */
#define udef_v_bez_qual v_bez_qual

#ifdef FORCE_GEMLIB_UDEF
#define v_bez udef_v_bez
#define v_bez_fill udef_v_bez_fill
#endif


/*
 * The following functions requires NVDI version 3.x or higher
 */

/** structure to store information about a font */
typedef struct
{
	long		size;				/**< length of the structure, initialize this entry before
	                                     calling vqt_xfntinfo() */
	short		format;				/**< font format, e.g. 4 for TrueType */
	short		id;					/**< font ID, e.g. 6059 */
	short		index;				/**< index */
	char		font_name[50];		/**< font name, e.g. "Century 725 Italic BT" */
	char		family_name[50];	/**< name of the font family, e.g. "Century725 BT" */
	char		style_name[50];		/**< name of the font style, e.g. "Italic" */
	char		file_name1[200];	/**< name of the first font file,
	                                     e.g. "C:\\FONTS\\TT1059M_.TTF" */
	char		file_name2[200];	/**< name of the 2nd font file */
	char		file_name3[200];	/**< name of the 3rd font file */
	short		pt_cnt;				/**< number of available point sizes (vst_point()),
	                                     e.g. 10 */
	short		pt_sizes[64];		/**< available point sizes,
                                         e.g. { 8, 9, 10, 11, 12, 14, 18, 24, 36, 48 } */
} XFNT_INFO;

typedef unsigned short WCHAR; /**< 16bit string, eg. for unicode */

#ifdef __GEMLIB_VDI  /* defined in mt_gem.h */

/** @addtogroup n_vdi
 *  @{
 */

void	v_ftext         (VdiHdl, short x, short y, const char  *str);
void	v_ftextn        (VdiHdl, short x, short y, const char  *str, short num);
void	v_ftext16       (VdiHdl, short x, short y, const WCHAR *wstr);
void	v_ftext16n      (VdiHdl, PXY pos, const WCHAR *wstr, short num);
void	v_ftext_offset  (VdiHdl, short x, short y,
                               const char  *str,  const short *offset);
void	v_ftext_offset16(VdiHdl, short x, short y,
                               const WCHAR *wstr, const short *offset);
void	v_ftext_offset16n(VdiHdl, short x, short y,
                               const WCHAR *wstr, short num, const short *offset);
void	v_getbitmap_info(VdiHdl, short ch, long *advancex, long *advancey,
                               long *xoffset, long *yoffset, short *width,
                               short *height, short **bitmap);
void	v_getoutline    (VdiHdl, short ch, short *xyarray, char *bezarray,
                               short maxverts, short *numverts);

short	vq_devinfo     (VdiHdl, short device, short *dev_exists,
                              char *file_name, char *device_name);
void	vqt_devinfo    (VdiHdl, short device, short *dev_busy,
                              char *file_name, char *device_name);
short	vq_ext_devinfo (VdiHdl, short device, short *dev_exists,
                              char *file_path, char *file_name, char *name);

void	vqt_advance     (VdiHdl, short ch, short *advx, short *advy,
                               short *xrem, short *yrem);
void	vqt_advance32   (VdiHdl, short ch, long *advx, long *advy);
short	vqt_ext_name    (VdiHdl, short __index,
                               char *name, short *font_format, short *flags);

void	vqt_f_extent    (VdiHdl, const char  *str, short extent[]);
void	vqt_f_extentn   (VdiHdl, const char  *str, short num, short extent[]);
void	vqt_f_extent16  (VdiHdl, const WCHAR *str, short extent[]);
void	vqt_f_extent16n (VdiHdl, const WCHAR *str, short num, short extent[]);

void	vqt_fontheader  (VdiHdl, char *buffer, char *pathname);

short	vqt_name_and_id (VdiHdl, short font_format,
                               char *font_name, char *ret_name);
void	vqt_pairkern    (VdiHdl, short ch1, short ch2, long *x, long *y);

void	vqt_real_extent (VdiHdl, short x, short y, const char *string, short extent[]);
void	vqt_real_extentn (VdiHdl, short x, short y, const char *string, short num, short extent[]);
void	vqt_real_extent16n (VdiHdl, short x, short y, const WCHAR *wstring, short num, short extent[]);
void	vqt_trackkern   (VdiHdl, long *x, long *y);
short	vqt_xfntinfo    (VdiHdl, short flags, short id,
                               short __index, XFNT_INFO *info);

short vst_arbpt 	(VdiHdl, short point, short *wchar, short *hchar, short *wcell, short *hcell);
long  vst_arbpt32 	(VdiHdl, long point, short *wchar, short *hchar, short *wcell, short *hcell);
void  vst_charmap 	(VdiHdl, short mode);
void  vst_kern	(VdiHdl, short tmode, short pmode, short *tracks, short *pairs);

short vst_name 	(VdiHdl, short font_format, char *font_name, char *ret_name);
short vst_setsize 	(VdiHdl, short point, short *wchar, short *hchar, short *wcell, short *hcell);
long  vst_setsize32 	(VdiHdl, long point, short *wchar, short *hchar, short *wcell, short *hcell);
short vst_skew 	(VdiHdl, short skew);
void  vst_track_offset(VdiHdl, long offset, short pairmode, short *tracks, short *pairs);
/** another name for vst_track_offset */
#define vst_kern_info vst_track_offset
void  vst_width	(VdiHdl, short width, short *char_width, short *char_height, short *cell_width, short *cell_height);
/**@}*/



/** @ingroup force_udef */
void	udef_v_ftext         (VdiHdl, short x, short y, const char  *str);
void	udef_v_ftextn         (VdiHdl, short x, short y, const char  *str, short num);
/** UDEF version of v_ftext16(). See \ref overviewUDEF for details about UDEF feature */
#define udef_v_ftext16 v_ftext16
/** UDEF version of v_ftext16n(). See \ref overviewUDEF for details about UDEF feature */
#define udef_v_ftext16n v_ftext16n
/** @ingroup force_udef */
void	udef_v_ftext_offset  (VdiHdl, short x, short y,
                               const char  *str,  const short *offset);
/** @ingroup force_udef */
void	udef_v_ftext_offset16(VdiHdl, short x, short y,
                               const WCHAR *wstr, const short *offset);
/** @ingroup force_udef */
void	udef_v_ftext_offset16n(VdiHdl, short x, short y,
                               const WCHAR *wstr, short num, const short *offset);
/** UDEF version of v_getbitmap_info(). See \ref overviewUDEF for details about UDEF feature */
#define udef_v_getbitmap_info v_getbitmap_info
/** UDEF version of v_getoutline(). See \ref overviewUDEF for details about UDEF feature */
#define udef_v_getoutline v_getoutline
/** @ingroup force_udef */
short	udef_vq_devinfo     (VdiHdl, short device, short *dev_exists,
                              char *file_name, char *device_name);
/** UDEF version of vqt_devinfo(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vqt_devinfo vqt_devinfo
/** UDEF version of vq_ext_devinfo(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vq_ext_devinfo vq_ext_devinfo

/** UDEF version of vqt_advance(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vqt_advance vqt_advance
/** UDEF version of vqt_advance32(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vqt_advance32 vqt_advance32
/** UDEF version of vqt_ext_name(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vqt_ext_name vqt_ext_name
/** @ingroup force_udef */
void	udef_vqt_f_extent    (VdiHdl, const char  *str, short extent[]);
void	udef_vqt_f_extentn    (VdiHdl, const char  *str, short num, short extent[]);
/** UDEF version of vqt_f_extent16(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vqt_f_extent16 vqt_f_extent16
/** UDEF version of vqt_f_extent16n(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vqt_f_extent16n vqt_f_extent16n
/** @ingroup force_udef */
void	udef_vqt_fontheader  (VdiHdl, char *buffer, char *pathname);
/** @ingroup force_udef */
short	udef_vqt_name_and_id (VdiHdl, short font_format,
                               char *font_name, char *ret_name);
/** UDEF version of vqt_pairkern(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vqt_pairkern vqt_pairkern
/** @ingroup force_udef */
void	udef_vqt_real_extent (VdiHdl, short x, short y, const char *string, short extent[]);
void	udef_vqt_real_extentn (VdiHdl, short x, short y, const char *string, short num, short extent[]);
/** UDEF version of vqt_real_extent16n(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vqt_real_extent16n vqt_real_extent16n
/** UDEF version of vqt_trackkern(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vqt_trackkern vqt_trackkern
/** UDEF version of vqt_xfntinfo(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vqt_xfntinfo vqt_xfntinfo

/** UDEF version of vst_arbpt(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vst_arbpt vst_arbpt
/** UDEF version of vst_arbpt32(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vst_arbpt32 vst_arbpt32
/** UDEF version of vst_charmap(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vst_charmap vst_charmap
/** UDEF version of vst_kern(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vst_kern vst_kern
/** @ingroup force_udef */
short udef_vst_name 	(VdiHdl, short font_format, char *font_name, char *ret_name);

/** UDEF version of vst_setsize(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vst_setsize vst_setsize
/** UDEF version of vst_setsize32(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vst_setsize32 vst_setsize32
/** UDEF version of vst_skew(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vst_skew vst_skew
/** UDEF version of vst_track_offset(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vst_track_offset vst_track_offset

/** UDEF version of vst_kern_info(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vst_kern_info vst_track_offset

/** UDEF version of vst_width(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vst_width vst_width


#ifdef FORCE_GEMLIB_UDEF
#define v_ftext udef_v_ftext
#define v_ftextn udef_v_ftextn
#define v_ftext_offset udef_v_ftext_offset
#define v_ftext_offset16 udef_v_ftext_offset16
#define v_ftext_offset16n udef_v_ftext_offset16n
#define vq_devinfo udef_vq_devinfo
#define vqt_f_extent udef_vqt_f_extent
#define vqt_f_extentn udef_vqt_f_extentn
#define vqt_fontheader udef_vqt_fontheader
#define vqt_name_and_id udef_vqt_name_and_id
#define vqt_real_extent udef_vqt_real_extent
#define vst_name udef_vst_name
#endif


#endif


/*
 * The following functions requires NVDI version 4.x or higher
 */

/** @addtogroup n_vdi
 *  @{
 */
short vqt_char_index (short handle, short scr_index, short scr_mode, short dst_mode);
short vst_map_mode   (short handle, short mode);
/**@}*/

/** UDEF version of vqt_char_index(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vqt_char_index vqt_char_index
/** UDEF version of vst_map_mode(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vst_map_mode vst_map_mode

/** vqt_is_char_available() */
#define vqt_is_char_available(handle,unicode) \
	(vqt_char_index(handle,unicode,CHARIDX_UNICODE,CHARIDX_DIRECT)!=0xFFFF)

/*
 * The following functions requires NVDI version 5.x or higher
 */
 
/*----------------------------------------------------------------------------------------*/
/* Functions which use the printer dialog from WDialog									  */
/*----------------------------------------------------------------------------------------*/

/** @addtogroup n_vdi
 *  @{
 */
DRV_INFO *v_create_driver_info(short handle, short driver_id );
short v_delete_driver_info(short handle, DRV_INFO *drv_info );
short v_read_default_settings(short handle, PRN_SETTINGS *settings );
short v_write_default_settings(short handle, PRN_SETTINGS *settings );
/**@}*/

/** UDEF version of v_create_driver_info(). See \ref overviewUDEF for details about UDEF feature */
#define udef_v_create_driver_info v_create_driver_info
/** UDEF version of v_delete_driver_info(). See \ref overviewUDEF for details about UDEF feature */
#define udef_v_delete_driver_info v_delete_driver_info
/** UDEF version of v_read_default_settings(). See \ref overviewUDEF for details about UDEF feature */
#define udef_v_read_default_settings v_read_default_settings
/** UDEF version of v_write_default_settings(). See \ref overviewUDEF for details about UDEF feature */
#define udef_v_write_default_settings v_write_default_settings


/*----------------------------------------------------------------------------------------*/
/* Constants for pixel formats								*/
/*----------------------------------------------------------------------------------------*/
#define	PX_1COMP		0x01000000L										/**< Pixel consists of one used component: Color index */
#define	PX_3COMP		0x03000000L										/**< Pixel consists of three used components, e.g. RGB */
#define	PX_4COMP		0x04000000L										/**< Pixel consists of four used component, e.g. CMYK */

#define	PX_REVERSED	0x00800000L										/**< Pixel will be output in reverse byte order */
#define	PX_xFIRST	0x00400000L										/**< Unused bits lie before the used ones (viewed in Motorola format) */
#define	PX_kFIRST	0x00200000L										/**< K lies before CMY (viewed in Motorola format) */
#define	PX_aFIRST	0x00100000L										/**< Alpha channel lies before the color bits (viewed in Motorola format) */

#define	PX_PACKED	0x00020000L										/**< Bits are stored sequentially */
#define	PX_PLANES	0x00010000L										/**< Bits are distributed over several planes (order: 0, 1, ..., n) */
#define	PX_IPLANES	0x00000000L										/**< Bits are distributed over several words (order: 0, 1, ..., n) */

#define	PX_USES1		0x00000100L										/**< 1 bit of the pixel is used */
#define	PX_USES2		0x00000200L										/**< 2 bits of the pixel are used */
#define	PX_USES3		0x00000300L										/**< 3 bits of the pixel are used */
#define	PX_USES4		0x00000400L										/**< 4 bits of the pixel are used */
#define	PX_USES8		0x00000800L										/**< 8 bits of the pixel are used */
#define	PX_USES15	0x00000f00L										/**< 15 bits of the pixel are used */
#define	PX_USES16	0x00001000L										/**< 16 bits of the pixel are used */
#define	PX_USES24	0x00001800L										/**< 24 bits of the pixel are used */
#define	PX_USES32	0x00002000L										/**< 32 bits of the pixel are used */
#define	PX_USES48	0x00003000L										/**< 48 bits of the pixel are used */

#define	PX_1BIT		0x00000001L										/**< Pixel consists of 1 bit */
#define	PX_2BIT		0x00000002L										/**< Pixel consists of 2 bits */
#define	PX_3BIT		0x00000003L										/**< Pixel consists of 3 bits */
#define	PX_4BIT		0x00000004L										/**< Pixel consists of 4 bits */
#define	PX_8BIT		0x00000008L										/**< Pixel consists of 8 bits */
#define	PX_16BIT		0x00000010L										/**< Pixel consists of 16 bits */
#define	PX_24BIT		0x00000018L										/**< Pixel consists of 24 bits */
#define	PX_32BIT		0x00000020L										/**< Pixel consists of 32 bits */
#define	PX_48BIT		0x00000030L										/**< Pixel consists of 48 bits */

#define	PX_CMPNTS	0x0f000000L										/**< Mask for number of pixel components */
#define	PX_FLAGS		0x00f00000L										/**< Mask for various flags */
#define	PX_PACKING	0x00030000L										/**< Mask for pixel format */
#define	PX_USED		0x00003f00L										/**< Mask for number of used bits */
#define	PX_BITS		0x0000003fL										/**< Mask for number of bits per pixel */

/*----------------------------------------------------------------------------------------*/
/* Pixel formats for ATARI graphics							*/
/*----------------------------------------------------------------------------------------*/
/** Atari graphics, 1 plane */
#define	PX_ATARI1	( PX_PACKED + PX_1COMP + PX_USES1 + PX_1BIT )
/** Atari graphics, 2 planes */
#define	PX_ATARI2	( PX_IPLANES + PX_1COMP + PX_USES2 + PX_2BIT )
/** Atari graphics, 4 planes */
#define	PX_ATARI4	( PX_IPLANES + PX_1COMP + PX_USES4 + PX_4BIT )
/** Atari graphics, 8 planes */
#define	PX_ATARI8	( PX_IPLANES + PX_1COMP + PX_USES8 + PX_8BIT )
/** Atari graphics, 15bit Falcon mode */
#define	PX_FALCON15	( PX_PACKED + PX_3COMP + PX_USES16 + PX_16BIT )

/*----------------------------------------------------------------------------------------*/
/* Pixel formats for Macintosh								*/
/*----------------------------------------------------------------------------------------*/
/** Macintosh, 1 plane */
#define	PX_MAC1		( PX_PACKED + PX_1COMP + PX_USES1 + PX_1BIT )
/** Macintosh, 4 planes */
#define	PX_MAC4		( PX_PACKED + PX_1COMP + PX_USES4 + PX_4BIT )
/** Macintosh, 256 colors */
#define	PX_MAC8		( PX_PACKED + PX_1COMP + PX_USES8 + PX_8BIT )
/** Macintosh, 15bit mode*/
#define	PX_MAC15		( PX_xFIRST + PX_PACKED + PX_3COMP + PX_USES15 + PX_16BIT )
/** Macintosh, 32bit mode */
#define	PX_MAC32		( PX_xFIRST + PX_PACKED + PX_3COMP + PX_USES24 + PX_32BIT )

/*----------------------------------------------------------------------------------------*/
/* Pixel formats for graphic cards							*/
/*----------------------------------------------------------------------------------------*/
/** VGA, 1 plane */
#define	PX_VGA1		( PX_PACKED + PX_1COMP + PX_USES1 + PX_1BIT )
/** VGA, 4 planes */
#define	PX_VGA4		( PX_PLANES + PX_1COMP + PX_USES4 + PX_4BIT )
/** VGA, 256 colors */
#define	PX_VGA8		( PX_PACKED + PX_1COMP + PX_USES8 + PX_8BIT )
/** VGA, 15bit */
#define	PX_VGA15		( PX_REVERSED + PX_xFIRST + PX_PACKED + PX_3COMP + PX_USES15 + PX_16BIT )
/** VGA, 16bit */
#define	PX_VGA16		( PX_REVERSED + PX_PACKED + PX_3COMP + PX_USES16 + PX_16BIT )
/** VGA, 24bit */
#define	PX_VGA24		( PX_REVERSED + PX_PACKED + PX_3COMP + PX_USES24 + PX_24BIT )
/** VGA, 32bit */
#define	PX_VGA32		( PX_REVERSED + PX_xFIRST + PX_PACKED + PX_3COMP + PX_USES24 + PX_32BIT )

/** Matrix graphic card, 16bit */
#define	PX_MATRIX16	( PX_PACKED + PX_3COMP + PX_USES16 + PX_16BIT )

/** Nova graphic card, 32bit */
#define	PX_NOVA32	( PX_PACKED + PX_3COMP + PX_USES24 + PX_32BIT )

/*----------------------------------------------------------------------------------------*/
/* Pixel formats for printers								*/
/*----------------------------------------------------------------------------------------*/
/** Pixel format for printer, B&W */
#define	PX_PRN1		( PX_PACKED + PX_1COMP + PX_USES1 + PX_1BIT )
/** Pixel format for printer, color */
#define	PX_PRN8		( PX_PACKED + PX_1COMP + PX_USES8 + PX_8BIT )
/** Pixel format for printer, 3 components */
#define	PX_PRN32		( PX_xFIRST + PX_PACKED + PX_3COMP + PX_USES24 + PX_32BIT )

/*----------------------------------------------------------------------------------------*/
/* Preferred (fast) pixel formats for bitmaps						*/
/*----------------------------------------------------------------------------------------*/

/** Monochrome */
#define	PX_PREF1		( PX_PACKED + PX_1COMP + PX_USES1 + PX_1BIT )
/** 4 colors */
#define	PX_PREF2		( PX_PACKED + PX_1COMP + PX_USES2 + PX_2BIT )
/** 16 colors */
#define	PX_PREF4		( PX_PACKED + PX_1COMP + PX_USES4 + PX_4BIT )
/** 256 colors */
#define	PX_PREF8		( PX_PACKED + PX_1COMP + PX_USES8 + PX_8BIT )
/** 15bit */
#define	PX_PREF15	( PX_xFIRST + PX_PACKED + PX_3COMP + PX_USES15 + PX_16BIT )
/** 32bit */
#define	PX_PREF32	( PX_xFIRST + PX_PACKED + PX_3COMP + PX_USES24 + PX_32BIT )

/*----------------------------------------------------------------------------------------*/
/* Color palettes									*/
/*----------------------------------------------------------------------------------------*/

/** Color space */
enum
{
	CSPACE_RGB		=	0x0001,			/**< RGB color space */
	CSPACE_ARGB		=	0x0002,			/**< ARGB color space */
	CSPACE_CMYK		=	0x0004			/**< CMYK color space */
};

/** Components */
enum
{
	CSPACE_1COMPONENT	=	0x0001,		/**< 1 component */
	CSPACE_2COMPONENTS	=	0x0002,		/**< 2 components */
	CSPACE_3COMPONENTS	= 	0x0003,		/**< 3 components */
	CSPACE_4COMPONENTS	=	0x0004		/**< 4 components */
};

/** RGB color structure */
typedef struct
{
	unsigned short	reserved;			/**< Reserved */
	unsigned short	red;				/**< Red */
	unsigned short	green;				/**< Green */
	unsigned short	blue;				/**< Blue */
} COLOR_RGB;

/** CMYK color structure */
typedef struct
{
	unsigned short	cyan;				/**< Cyan */
	unsigned short	magenta;			/**< Magenta */
	unsigned short	yellow;				/**< Yellow */
	unsigned short	black;				/**< Black */
} COLOR_CMYK;

/** Color entry */
typedef union
{
	COLOR_RGB	rgb;			/**< RGB color */
	COLOR_CMYK	cmyk;			/**< CMYK color */
} COLOR_ENTRY;

/** Magic value for color table */
#define	COLOR_TAB_MAGIC	0x63746162L /* 'ctab' */

/** Color table */
typedef struct
{
	long		magic;				/**< 'ctab' */
	long		length;				/**< Structure length */
	long		format;				/**< Format */
	long		reserved;			/**< Reserved, set to 0 */

	long		map_id;				/**< Color table ID */
	long		color_space;		/**< Color space (at present only CSPACE_RGB) */
	long		flags;				/**< VDI-internal flags, set to 0 */
	long		no_colors;			/**< Number of color entries */

	long		reserved1;			/**< Reserved, must be 0 */
	long		reserved2;			/**< Reserved, must be 0 */
	long		reserved3;			/**< Reserved, must be 0 */
	long		reserved4;			/**< Reserved, must be 0 */

#if defined(__GNUC__) || defined (__LATTICE__) || defined(__VBCC__)
	COLOR_ENTRY	colors[0];			/**< Color entries */
#else
	COLOR_ENTRY	colors[];			/**< Color entries */
#endif

} COLOR_TAB;

/** Color table with 256 colors */
typedef struct
{
	long	magic;			/**< set to 'ctab' */
	long	length;			/**< Structure length */
	long	format;			/**< Format */
	long	reserved;			/**< Reserved, set to 0 */
	
	long	map_id;			/**< Color table ID */
	long	color_space;			/**< Color space (at present only CSPACE_RGB) */
	long	flags;			/**< VDI-internal flags, set to 0 */
	long	no_colors;			/**< Number of color entries (256) */

	long	reserved1;			/**< Reserved, must be 0 */
	long	reserved2;			/**< Reserved, must be 0 */
	long	reserved3;			/**< Reserved, must be 0 */
	long	reserved4;			/**< Reserved, must be 0 */

	COLOR_ENTRY	colors[256];	/**< Color entries (256) */
} COLOR_TAB256;

typedef COLOR_TAB *CTAB_PTR;	/**< Pointer to color table */
typedef COLOR_TAB *CTAB_REF;	/**< Reference to color table */


typedef void INVERSE_CTAB;		/**< Inverse color table */
typedef INVERSE_CTAB *ITAB_REF;	/**< Reference to inverse color table */

/** Magic value for color bitmap */
#define	CBITMAP_MAGIC	0x6362746dL /* 'cbtm' */

typedef struct _gcbitmap GCBITMAP;/**< GCBITMAP */
/** GCBITMAP structure */
struct _gcbitmap
{
	long		magic;			/**< Structure identifier 'cbtm' */
	long		length;			/**< Structure length */
	long		format;			/**< Structure format (0) */
	long		reserved;		/**< Reserved (0) */

	unsigned char	*addr;		/**< Address of bitmap */
	long		width;			/**< Width of a line in bytes */
	long		bits;			/**< Bit-depth */
	unsigned long	px_format;	/**< Pixel format */

	long		xmin;			/**< Minimum discrete X-coordinate of bitmap */
	long		ymin;			/**< Minimum discrete Y-coordinate of bitmap */
	long		xmax;			/**< Maximum discrete X-coordinate of bitmap + 1 */
	long		ymax;			/**< Maximum discrete Y-coordinate of bitmap + 1 */

	CTAB_REF	ctab;			/**< Reference to color table, or 0L */
	ITAB_REF 	itab;			/**< Reference to inverse color table, or 0L */
	long		color_space;	/**< Color space */
	long		reserved1;		/**< Reserved, must be 0 */
};

/*----------------------------------------------------------------------------------------*/
/* Transfer modes for bitmaps								*/
/*----------------------------------------------------------------------------------------*/

/* Constants for modes */
#define	T_NOT				4	/**< Constant to reverse logical transfer mode */
#define	T_COLORIZE			16	/**< Colorize source */

#define	T_LOGIC_MODE		0	/**< Constant for logical transfer mode */
#define	T_DRAW_MODE			32	/**< Constant for drawing mode */
#define	T_ARITH_MODE		64	/**< Constant for arithmetic transfer mode */
#define	T_DITHER_MODE		128	/**< Dither source data */

/* Logical transfer modes */
#define	T_LOGIC_COPY		(T_LOGIC_MODE+0)	/**< dst = src */
#define	T_LOGIC_OR			(T_LOGIC_MODE+1)	/**< dst = src OR dst */
#define	T_LOGIC_XOR			(T_LOGIC_MODE+2)	/**< dst = src XOR dst*/
#define	T_LOGIC_AND			(T_LOGIC_MODE+3)	/**< dst = src AND dst */
#define	T_LOGIC_NOT_COPY	(T_LOGIC_MODE+4)	/**< dst = ( NOT src ) */
#define	T_LOGIC_NOT_OR		(T_LOGIC_MODE+5)	/**< dst = ( NOT src ) OR dst */
#define	T_LOGIC_NOT_XOR		(T_LOGIC_MODE+6)	/**< dst = ( NOT src ) XOR dst */
#define	T_LOGIC_NOT_AND		(T_LOGIC_MODE+7)	/**< dst = ( NOT src ) AND dst */

/* Writing modes */
#define	T_REPLACE				(T_DRAW_MODE+0)	/**< dst = src */
#define	T_TRANSPARENT			(T_DRAW_MODE+1)	/**< if ( src != bg_col ) dst = src */
#define	T_HILITE				(T_DRAW_MODE+2)	/**< if ( src != bg_col ) { if ( dst == bg_col ) dst = hilite_col; else if ( dst == hilite_col ) dst = bg_col } */
#define	T_REVERS_TRANSPARENT	(T_DRAW_MODE+3)	/**< if ( src == bg_col ) dst = src */

/* Arithmetic transfer modes */
#define	T_BLEND					(T_ARITH_MODE+0)	/**< Mix source and destination color */
#define	T_ADD					(T_ARITH_MODE+1)	/**< Add source and destination color */
#define	T_ADD_OVER				(T_ARITH_MODE+2)	/**< Add source and destination color, do not catch overflows */
#define	T_SUB					(T_ARITH_MODE+3)	/**< Substract source from destination color */
#define	T_MAX					(T_ARITH_MODE+5)	/**< Maximum RGB components */
#define	T_SUB_OVER				(T_ARITH_MODE+6)	/**< Substract source from destination color, do not catch overflows */
#define	T_MIN					(T_ARITH_MODE+7)	/**< Minimum RGB components */

/** 16b rectangle */
typedef struct			/* Rectangle with 16-Bit-coordinates */
{
	short	x1;			/**< X coordinate of the top left corner */
	short	y1;			/**< Y coordinate of the top left corner */
	short	x2;			/**< X coordinate of the bottom right corner + 1 */
	short	y2;			/**< Y coordinate of the bottom right corner + 1 */
} RECT16;

/** 32b rectangle */
typedef struct			/* Rectangle with 32-Bit-coordinates */
{
	long	x1;			/**< X coordinate of the top left corner */
	long	y1;			/**< Y coordinate of the top left corner */
	long	x2;			/**< X coordinate of the bottom right corner + 1 */
	long	y2;			/**< Y coordinate of the bottom right corner + 1 */
} RECT32;

/** @addtogroup n_vdi
 *  @{
 */
long		v_color2nearest		(short handle, long color_space, COLOR_ENTRY *color, COLOR_ENTRY *nearest_color);
unsigned long	v_color2value		(short handle, long color_space, COLOR_ENTRY *color);
COLOR_TAB *	v_create_ctab		(short handle, long color_space, unsigned long px_format);
ITAB_REF	v_create_itab		(short handle, COLOR_TAB *ctab, short bits );
unsigned long	v_ctab_idx2value	(short handle, short __index );
short		v_ctab_idx2vdi		(short handle, short __index);
short		v_ctab_vdi2idx		(short handle, short vdi_index);
short		v_delete_ctab		(short handle, COLOR_TAB *ctab);
short		v_delete_itab		(short handle, ITAB_REF itab);
long		v_get_ctab_id		(short handle);
short		v_get_outline		(short handle, short __index, short x_offset, short y_offset, short *pts, char *flags, short max_pts);
short		v_opnprn		(short aes_handle, PRN_SETTINGS *settings, short work_out[]);
short		v_open_bm		(short base_handle, GCBITMAP *bitmap, short color_flags, short unit_flags, short pixel_width, short pixel_height);
short		v_resize_bm		(short handle, short width, short height, long b_width, unsigned char *addr);
void		v_setrgb		(short handle, short type, short r, short g, short b);
long		v_value2color		(short handle, unsigned long value, COLOR_ENTRY *color);
short		vq_ctab			(short handle, long ctab_length, COLOR_TAB *ctab);
long		vq_ctab_entry		(short handle, short __index, COLOR_ENTRY *color);
long		vq_ctab_id		(short handle);
short		vq_dflt_ctab		(short handle, long ctab_length, COLOR_TAB *ctab);
long		vq_hilite_color		(short handle, COLOR_ENTRY *hilite_color);
short		vq_margins		(short handle, short *top_margin, short *bottom_margin, short *left_margin, short *right_margin, short *hdpi, short *vdpi);
long		vq_max_color		(short handle, COLOR_ENTRY *hilite_color);
long		vq_min_color		(short handle, COLOR_ENTRY *hilite_color);
long		vq_prn_scaling		(short handle);
long		vq_px_format		(short handle, unsigned long *px_format);
long		vq_weight_color		(short handle, COLOR_ENTRY *hilite_color);
long		vqf_bg_color		(short handle, COLOR_ENTRY *fg_color);
long		vqf_fg_color		(short handle, COLOR_ENTRY *fg_color);
long		vql_bg_color		(short handle, COLOR_ENTRY *fg_color);
long		vql_fg_color		(short handle, COLOR_ENTRY *fg_color);
long		vqm_bg_color		(short handle, COLOR_ENTRY *fg_color);
long		vqm_fg_color		(short handle, COLOR_ENTRY *fg_color);
long		vqr_bg_color		(short handle, COLOR_ENTRY *fg_color);
long		vqr_fg_color		(short handle, COLOR_ENTRY *fg_color);
long		vqt_bg_color		(short handle, COLOR_ENTRY *fg_color);
long		vqt_fg_color		(short handle, COLOR_ENTRY *fg_color);
void		vr_transfer_bits	(short handle, GCBITMAP *src_bm, GCBITMAP *dst_bm, short *src_rect, short *dst_rect, short mode);
short		vs_ctab			(short handle, COLOR_TAB *ctab);
short		vs_ctab_entry		(short handle, short __index, long color_space, COLOR_ENTRY *color);
short		vs_dflt_ctab		(short handle);
short		vs_document_info	(short vdi_handle, short type, char *s, short wchar);
short		vs_hilite_color		(short handle, long color_space, COLOR_ENTRY *hilite_color);
short		vs_max_color		(short handle, long color_space, COLOR_ENTRY *min_color);
short		vs_min_color		(short handle, long color_space, COLOR_ENTRY *min_color);
short		vs_weight_color		(short handle, long color_space, COLOR_ENTRY *weight_color);
short		vsf_bg_color		(short handle, long color_space, COLOR_ENTRY *bg_color);
short		vsf_fg_color		(short handle, long color_space, COLOR_ENTRY *fg_color);
short		vsl_bg_color		(short handle, long color_space, COLOR_ENTRY *bg_color);
short		vsl_fg_color		(short handle, long color_space, COLOR_ENTRY *fg_color);
short		vsm_bg_color		(short handle, long color_space, COLOR_ENTRY *bg_color);
short		vsm_fg_color		(short handle, long color_space, COLOR_ENTRY *fg_color);
short		vsr_bg_color		(short handle, long color_space, COLOR_ENTRY *bg_color);
short		vsr_fg_color		(short handle, long color_space, COLOR_ENTRY *fg_color);
short		vst_bg_color		(short handle, long color_space, COLOR_ENTRY *bg_color);
short		vst_fg_color		(short handle, long color_space, COLOR_ENTRY *fg_color);
/**@}*/

/** UDEF version of v_color2nearest(). See \ref overviewUDEF for details about UDEF feature */
#define udef_v_color2nearest v_color2nearest
/** UDEF version of v_color2value(). See \ref overviewUDEF for details about UDEF feature */
#define udef_v_color2value v_color2value
/** UDEF version of v_create_ctab(). See \ref overviewUDEF for details about UDEF feature */
#define udef_v_create_ctab v_create_ctab
/** UDEF version of v_create_itab(). See \ref overviewUDEF for details about UDEF feature */
#define udef_v_create_itab v_create_itab
/** UDEF version of v_ctab_idx2value(). See \ref overviewUDEF for details about UDEF feature */
#define udef_v_ctab_idx2value v_ctab_idx2value
/** UDEF version of v_ctab_idx2vdi(). See \ref overviewUDEF for details about UDEF feature */
#define udef_v_ctab_idx2vdi v_ctab_idx2vdi
/** UDEF version of v_ctab_vdi2idx(). See \ref overviewUDEF for details about UDEF feature */
#define udef_v_ctab_vdi2idx v_ctab_vdi2idx
/** UDEF version of v_delete_ctab(). See \ref overviewUDEF for details about UDEF feature */
#define udef_v_delete_ctab v_delete_ctab
/** UDEF version of v_delete_itab(). See \ref overviewUDEF for details about UDEF feature */
#define udef_v_delete_itab v_delete_itab
/** UDEF version of v_get_ctab_id(). See \ref overviewUDEF for details about UDEF feature */
#define udef_v_get_ctab_id v_get_ctab_id
/** UDEF version of v_get_outline(). See \ref overviewUDEF for details about UDEF feature */
#define udef_v_get_outline v_get_outline
/** UDEF version of v_opnprn(). See \ref overviewUDEF for details about UDEF feature */
#define udef_v_opnprn v_opnprn
/** UDEF version of v_open_bm(). See \ref overviewUDEF for details about UDEF feature */
#define udef_v_open_bm v_open_bm
/** UDEF version of v_resize_bm(). See \ref overviewUDEF for details about UDEF feature */
#define udef_v_resize_bm v_resize_bm
/** UDEF version of v_setrgb(). See \ref overviewUDEF for details about UDEF feature */
#define udef_v_setrgb v_setrgb
/** UDEF version of v_value2color(). See \ref overviewUDEF for details about UDEF feature */
#define udef_v_value2color v_value2color
/** UDEF version of vq_ctab(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vq_ctab vq_ctab
/** UDEF version of vq_ctab_entry(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vq_ctab_entry vq_ctab_entry
/** UDEF version of vq_ctab_id(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vq_ctab_id vq_ctab_id
/** UDEF version of vq_dflt_ctab(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vq_dflt_ctab vq_dflt_ctab
/** @ingroup force_udef */
long		udef_vq_hilite_color	(short handle, COLOR_ENTRY *hilite_color);
/** UDEF version of vq_margins(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vq_margins vq_margins
/** UDEF version of vq_max_color(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vq_max_color vq_max_color
/** UDEF version of vq_min_color(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vq_min_color vq_min_color
/** UDEF version of vq_prn_scaling(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vq_prn_scaling vq_prn_scaling
/** UDEF version of vq_px_format(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vq_px_format vq_px_format
/** UDEF version of vq_weight_color(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vq_weight_color vq_weight_color
/** UDEF version of vqf_bg_color(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vqf_bg_color vqf_bg_color
/** UDEF version of vqf_fg_color(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vqf_fg_color vqf_fg_color
/** UDEF version of vql_bg_color(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vql_bg_color vql_bg_color
/** UDEF version of vql_fg_color(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vql_fg_color vql_fg_color
/** UDEF version of vqm_bg_color(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vqm_bg_color vqm_bg_color
/** UDEF version of vqm_fg_color(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vqm_fg_color vqm_fg_color
/** UDEF version of vqr_bg_color(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vqr_bg_color vqr_bg_color
/** UDEF version of vqr_fg_color(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vqr_fg_color vqr_fg_color
/** UDEF version of vqt_bg_color(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vqt_bg_color vqt_bg_color
/** UDEF version of vqt_fg_color(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vqt_fg_color vqt_fg_color
/** UDEF version of vr_transfer_bits(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vr_transfer_bits vr_transfer_bits
/** UDEF version of vs_ctab(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vs_ctab vs_ctab
/** UDEF version of vs_ctab_entry(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vs_ctab_entry vs_ctab_entry
/** UDEF version of vs_dflt_ctab(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vs_dflt_ctab vs_dflt_ctab
/** @ingroup force_udef */
short		udef_vs_document_info	(short vdi_handle, short type, char *s, short wchar);
/** UDEF version of vs_hilite_color(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vs_hilite_color vs_hilite_color
/** UDEF version of vs_max_color(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vs_max_color vs_max_color
/** UDEF version of vs_min_color(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vs_min_color vs_min_color
/** UDEF version of vs_weight_color(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vs_weight_color vs_weight_color
/** UDEF version of vsf_bg_color(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vsf_bg_color vsf_bg_color
/** UDEF version of vsf_fg_color(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vsf_fg_color vsf_fg_color
/** UDEF version of vsl_bg_color(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vsl_bg_color vsl_bg_color
/** UDEF version of vsl_fg_color(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vsl_fg_color vsl_fg_color
/** UDEF version of vsm_bg_color(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vsm_bg_color vsm_bg_color
/** UDEF version of vsm_fg_color(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vsm_fg_color vsm_fg_color
/** UDEF version of vsr_bg_color(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vsr_bg_color vsr_bg_color
/** UDEF version of vsr_fg_color(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vsr_fg_color vsr_fg_color
/** UDEF version of vst_bg_color(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vst_bg_color vst_bg_color
/** UDEF version of vst_fg_color(). See \ref overviewUDEF for details about UDEF feature */
#define udef_vst_fg_color vst_fg_color

#ifdef FORCE_GEMLIB_UDEF
#define vq_hilite_color udef_vq_hilite_color
#define vs_document_info udef_vs_document_info
#endif


/*
 * speedo functions
 */

/** @addtogroup v_speedo
 *  @{
 */

/** Bit image structure */
typedef struct
{
	short nbplanes;     /**< Number of planes */
	short width;        /**< Width in pixels */
	short height;       /**< Height in pixels */
} BIT_IMAGE;

short vq_margins(short handle, short *top, short *bot, short *lft, short *rgt, short *xdpi, short *ydpi);
short vq_driver_info(short handle, short *lib, short *drv, short *plane, short *attr, char name[27]);
short vq_bit_image(short handle, short *ver, short *maximg, short *form);
short vs_page_info(short handle, short type, const char txt[60]);
short vs_crop(short handle, short ltx1, short lty1, short ltx2, short lty2, short ltlen, short ltoffset);
short vq_image_type(short handle, const char *file, BIT_IMAGE *img);
short vs_save_disp_list(short handle, const char *name);
short vs_load_disp_list(short handle, const char *name);

/**@}*/


__END_DECLS

#endif /* _MT_GEMLIB_X_H_ */

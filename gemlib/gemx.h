/*
 *  $Id$
 *
 * gemx.h - main header file for new gem-lib extensions
 *
 * This lib contains all GEM extensions of MagiC and NVDI/FSM/Speedo
 *
 */

#ifndef _GEMLIB_X_H_
#define _GEMLIB_X_H_

#include <gem.h>

__BEGIN_DECLS


/*******************************************************************************
 * The AES extentsions of MagiC
 */

typedef struct
{
	short		mwhich;		/* Art der Ereignisse */
	short		mx;		/* x-Koordinate des Mauszeigers */
	short		my;		/* y-Koordinate des Mauszeigers */
	short		mbutton; 	/* gedrÅckte Maustaste */
	short		kstate;		/* Status der Sondertasten (kbshift) */
	short		key;		/* Scancode der gedrÅckten Taste */
	short		mclicks; 	/* Anzahl der Mausklicks */
	short		reserved[9];	/* reserviert */
	short		msg[16]; 	/* Message-Buffer */
} EVNT;

/*
 * Extensions to the form library (MagiC only)
 */

/** @addtogroup a_form
 *  @{
 */

/** */
typedef struct
{
	char		scancode;  /**< */
	char		nclicks;   /**< */
	short		objnr;     /**< */
} SCANX;

/** */
typedef struct
{
	SCANX		*unsh;		/**< Tabellen fÅr UnShift-Kombinationen */
	SCANX		*shift;		/**< Tabellen fÅr Shift-Kombinationen */
	SCANX		*ctrl;		/**< Tabellen fÅr Control-Kombinationen */
	SCANX		*alt; 		/**< Tabellen fÅr Alternate-Kombinationen */
	void		*resvd;		/**< reserviert */
} XDO_INF;

short	mt_form_popup 	(OBJECT *tree, short x, short y, short * global);
short	mt_form_wbutton	(OBJECT *fo_btree, short fo_bobject, short fo_bclicks, short *fo_bnxtobj, short whandle, short * global);
short	mt_form_wkeybd	(OBJECT *fo_ktree, short fo_kobject, short fo_kobnext, short fo_kchar, short *fo_knxtobject, short *fo_knxtchar, short whandle, short * global);
short	mt_form_xdial 	(short fo_diflag, short fo_dilittlx, short fo_dilittly, short fo_dilittlw, short fo_dilittlh, short fo_dibigx, short fo_dibigy, short fo_dibigw, short fo_dibigh, void **flydial, short * global);
short	mt_form_xdo		(OBJECT *tree, short startob, short *lastcrsr, XDO_INF *tabs, void *flydial, short * global); 
short	mt_form_xerr	(long errcode, char *errfile, short * global);
#define form_popup(a,b,c)				mt_form_popup(a,b,c,aes_global)
#define form_wbutton(a,b,c,d,e)			mt_form_wbutton(a,b,c,d,e,aes_global)
#define form_wkeybd(a,b,c,d,e,f,g)		mt_form_wkeybd(a,b,c,d,e,f,g,aes_global)
#define form_xdial(a,b,c,d,e,f,g,h,i,j)	mt_form_xdial(a,b,c,d,e,f,g,h,i,j,aes_global)
#define form_xdo(a,b,c,d,e)				mt_form_xdo(a,b,c,d,e,aes_global)
#define form_xerr(a,b)					mt_form_xerr(a,b,aes_global)
/**@}*/

/*
 * Extensions to the object library (MagiC only)
 */

/** @addtogroup a_form
 *  @{
 */
void	mt_objc_wchange	(OBJECT *tree, short obj, short new_state, GRECT *clip, short whandle, short * global);
void	mt_objc_wdraw	(OBJECT *tree, short start, short depth, GRECT *clip, short whandle, short * global);
short	mt_objc_wedit	(OBJECT *tree, short obj, short key, short *idx, short kind, short whandle, short * global);
short	mt_objc_xedit	(OBJECT *tree, short obj, short key, short *xpos, short subfn, GRECT *r, short * global);
#define objc_wchange(a,b,c,d,e)	mt_objc_wchange(a,b,c,d,e,aes_global)
#define objc_wdraw(a,b,c,d,e)	mt_objc_wdraw(a,b,c,d,e,aes_global)
#define objc_wedit(a,b,c,d,e,f)	mt_objc_wedit(a,b,c,d,e,f,aes_global)
#define objc_xedit(a,b,c,d,e,f)	mt_objc_xedit(a,b,c,d,e,f,aes_global)
/**@}*/


/*
 * fnts_* font selection (MagiC/WDIALOG only)
 */

/** @addtogroup x_fnts
 *  @{
 */

/** opaque structure (internal management structure) */ 
typedef void *FNT_DIALOG;

/** */
typedef void __CDECL (*UTXT_FN)(short x, short y, short *clip_rect, long id, long pt, long ratio, char *string);

/** */
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
#define FNTS_CANCEL		1		
#define FNTS_OK			2		
#define FNTS_SET		3		
#define FNTS_MARK 		4		
#define FNTS_OPT		5		

short		mt_fnts_add			(FNT_DIALOG *fnt_dialog, FNTS_ITEM *user_fonts, short *global);
short		mt_fnts_close		(FNT_DIALOG *fnt_dialog, short *x, short *y, short *global);
FNT_DIALOG *mt_fnts_create		(short vdi_handle, short no_fonts, short font_flags, short dialog_flags, char *sample, char *opt_button, short *global);
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
#define fnts_add(a,b)				mt_fnts_add(a,b,aes_global)
#define fnts_close(a,b,c)			mt_fnts_close(a,b,c,aes_global)
#define fnts_create(a,b,c,d,e,f)	mt_fnts_create(a,b,c,d,e,f,aes_global)
#define fnts_delete(a,b)			mt_fnts_delete(a,b,aes_global)
#define fnts_do(a,b,c,d,e,f,g,h,i)	mt_fnts_do(a,b,c,d,e,f,g,h,i,aes_global)
#define fnts_evnt(a,b,c,d,e,f,g)	mt_fnts_evnt(a,b,c,d,e,f,g,aes_global)
#define fnts_get_info(a,b,c,d)		mt_fnts_get_info(a,b,c,d,aes_global)
#define fnts_get_name(a,b,c,d,e)	mt_fnts_get_name(a,b,c,d,e,aes_global)
#define fnts_get_no_styles(a,b)		mt_fnts_get_no_styles(a,b,aes_global)
#define fnts_get_style(a,b,c)		mt_fnts_get_style(a,b,c,aes_global)
#define fnts_open(a,b,c,d,e,f,g)	mt_fnts_open(a,b,c,d,e,f,g,aes_global)
#define fnts_remove(a)				mt_fnts_remove(a,aes_global)
#define fnts_update(a,b,c,d,e)		mt_fnts_update(a,b,c,d,e,aes_global)
/**@}*/

/*
 * fslx_* file selection (MagiC only)
 */

/** @addtogroup x_fslx
 *  @{
 */

/** */
typedef short __CDECL (*XFSL_FILTER)(char *path, char *name, void *xattr);

/* Sortiermodi */
#define SORTBYNAME		0
#define SORTBYDATE		1
#define SORTBYSIZE		2
#define SORTBYTYPE		3
#define SORTBYNONE		4

/* Flags fÅr Dateiauswahl */
#define DOSMODE			1
#define NFOLLOWSLKS		2
#define GETMULTI		8

/* fslx_set_flags */
#define SHOW8P3			1

short	fslx_close		(void *fsd, short *global);
void *	fslx_do			(char *title, char *path, short pathlen, char *fname, short fnamelen, char *patterns, XFSL_FILTER filter, char *paths, short *sort_mode, short flags, short *button, short *nfiles, char **pattern, short *global);
short	fslx_evnt		(void *fsd, EVNT *events, char *path, char *fname, short *button, short *nfiles, short *sort_mode, char **pattern, short *global); 
short	fslx_getnxtfile	(void *fsd, char *fname, short *global);
void *	fslx_open		(char *title, short x, short y, short *handle, char *path, short pathlen, char *fname, short fnamelen, char *patterns, XFSL_FILTER filter, char *paths, short sort_mode, short flags, short *global);
short	fslx_set_flags 	(short flags, short *oldval, short *global);
#define fslx_close(a)							mt_fslx_close(a,aes_global)
#define fslx_do(a,b,c,d,e,f,g,h,i,j,k,l,m)		mt_fslx_do(a,b,c,d,e,f,g,h,i,j,k,l,m,aes_global)
#define fslx_evnt(a,b,c,d,e,f,g,h)				mt_fslx_evnt(a,b,c,d,e,f,g,h,aes_global)
#define fslx_getnxtfile(a,b)					mt_fslx_getnxtfile(a,b,aes_global)
#define fslx_open(a,b,c,d,e,f,g,h,i,j,k,l,m)	mt_fslx_open(a,b,c,d,e,f,g,h,i,j,k,l,m,m,aes_global)
#define fslx_set_flags(a,b)						mt_fslx_set_flags(a,b,aes_global)
/**@}*/

/*
 * pdlg_* printer configuration dialogs (WDIALOG only)
 */

typedef void *PRN_DIALOG;

typedef struct _prn_tray	PRN_TRAY;
typedef struct _media_size	MEDIA_SIZE;
typedef struct _media_type	MEDIA_TYPE;
typedef struct _prn_mode	PRN_MODE;
typedef struct _prn_entry	PRN_ENTRY;
typedef struct _dither_mode	DITHER_MODE;
typedef struct _drv_entry	DRV_ENTRY;
typedef struct _pdlg_sub	PDLG_SUB;
typedef struct _prn_settings	PRN_SETTINGS;

struct _prn_tray				/* Beschreibung eines Einzugs/Auswurfs */
{
	PRN_TRAY	*next;
	
	long		tray_id; 		/* Nummer des Einzugs oder Auswurfs */
	char		name[32];		/* Name des Schachts */
};

struct _media_size 				/* Beschreibung eines Papierformats */
{
	MEDIA_SIZE	*next;

	long		size_id; 		/* Kennung des Papierformats */
	char		name[32];		/* Name des Papierformats */
};

struct _media_type 				/* Beschreibung eines Papiertyps/Druckmediums */
{
	MEDIA_TYPE	*next;

	long		type_id; 		/* Kennung des Papierformats */
	char		name[32];		/* Name des Papierformats */
};

struct _prn_mode				/* Beschreibung eines Druckermodus */
{
	PRN_MODE	*next; 			/* Zeiger auf den nÑchsten Druckermodus */

	long		mode_id; 		/* Moduskennung (Index innerhalb der Datei) */
	short 		hdpi; 			/* horizontale Auflîsung in dpi */
	short 		vdpi; 			/* vertikale Auflîsung in dpi */
	long		mode_capabilities;	/* Moduseigenschaften */

	long		color_capabilities;	/* einstellbare Farbmodi */
	long		dither_flags;		/* Flags, die angeben, ob der korrespondierende Farbmodus mit oder ohne Dithern ansprechbar ist */
	MEDIA_TYPE	*paper_types;		/* geeignete Papiertypen */
	long		reserved;

	char		name[32];		/* Modusname */
};

/* sub_flags */
#define	PRN_STD_SUBS	0x0001			/* Standard-Unterdialoge fÅr NVDI-Drucker */
#define	PRN_FSM_SUBS	0x0002			/* Standard-Unterdialoge fÅr FSM-Drucker */
#define	PRN_QD_SUBS 	0x0004			/* Standard-Unterdialoge fÅr QuickDraw-Drucker */

/* old_printer kann auch 0L sein */
typedef long __CDECL (*PRN_SWITCH)(DRV_ENTRY *drivers, PRN_SETTINGS *settings, PRN_ENTRY *old_printer, PRN_ENTRY *new_printer);

struct _prn_entry				/* GerÑtebeschreibung */
{
	PRN_ENTRY	*next;			/* Zeiger auf die die nÑchste GerÑtebeschreibung */
	long		length;			/* StrukturlÑnge */
	long		format;			/* Datenformat */
	long		reserved;		/* reserviert */
	
	short 		driver_id;		/* Treiberkennung */
	short 		driver_type;		/* Treibertyp */
	long		printer_id; 		/* Druckerkennung */
	long		printer_capabilities;	/* Druckereigenschaften */
	long		reserved1;

	long		sub_flags;		/* Flags fÅr die Unterdialoge */
	PDLG_SUB	*sub_dialogs;		/* Zeiger auf die Liste der Unterdialoge fÅr diesen Drucker */
	PRN_SWITCH	setup_panel;		/* Unterdialog bei Druckerwechsel initialisieren */
	PRN_SWITCH	close_panel;		/* Unterdialog bei Druckerwechsel schlieûen */

	PRN_MODE 	*modes;			/* Liste der vorhandenen Auflîsungen */
	MEDIA_SIZE	*papers; 		/* Liste der vorhandenen Papierformate */
	PRN_TRAY 	*input_trays;		/* Liste der EinzÅge */
	PRN_TRAY 	*output_trays; 		/* Liste der AuswÅrfe */

	char		name[32];		/* Name des Druckers */
};

struct _dither_mode
{
	DITHER_MODE	*next;
	long		length;			/* StrukturlÑnge */
	long		format;			/* Datenformat */
	long		reserved;		/* reserviert */

	long		dither_id;		/* Kennung */
	long		color_modes;		/* unterstÅtzte Farbtiefen */
	long		reserved1;
	long		reserved2;
	
	char		name[32];		/* Name des Rasterverfahrens */
};


typedef struct
{
	long		magic;			/* 'pdnf' */
	long		length;			/* StrukturlÑnge */
	long		format;			/* Datenformat */
	long		reserved;		/* reserviert */

	short 		driver_id;		/* Treibernummer fÅrs VDI */
	short 		driver_type;		/* Treibertyp */
	long		reserved1;
	long		reserved2;
	long		reserved3;

	PRN_ENTRY	*printers;		/* Liste der zum Treiber gehîrenden Drucker */
	DITHER_MODE	*dither_modes; 		/* Liste der vom Treiber unterstÅtzten Rasterverfahren */
	long		reserved4;
	long		reserved5;

	long		reserved6;
	long		reserved7;
	long		reserved8;
	long		reserved9;
	
	char		device[128];		/* Ausgabedatei des Druckertreibers */
	
} DRV_INFO;

struct _drv_entry
{
	 DRV_ENTRY	*next;
};

#define	PDLG_CHG_SUB	0x80000000L
#define	PDLG_IS_BUTTON	0x40000000L

#define	PDLG_PREBUTTON	0x20000000L
#define	PDLG_PB_OK	1
#define	PDLG_PB_CANCEL	2
#define	PDLG_PB_DEVICE	3

#define	PDLG_BUT_OK 	(PDLG_PREBUTTON + PDLG_PB_OK)
#define	PDLG_BUT_CNCL	(PDLG_PREBUTTON + PDLG_PB_CANCEL)
#define	PDLG_BUT_DEV	(PDLG_PREBUTTON + PDLG_PB_DEVICE)

typedef long __CDECL (*PDLG_INIT)(PRN_SETTINGS *settings, PDLG_SUB *sub);
typedef long __CDECL (*PDLG_HNDL)(PRN_SETTINGS *settings, PDLG_SUB *sub, short exit_obj);
typedef long __CDECL (*PDLG_RESET)(PRN_SETTINGS *settings, PDLG_SUB *sub);

struct _pdlg_sub				/* Unterdialog fÅr GerÑteeinstellung */
{
	PDLG_SUB	*next; 			/* Zeiger auf den Nachfolger in der Liste */
	long		length;			/* StrukturlÑnge */
	long		format;			/* Datenformat */
	long		reserved;		/* reserviert */
	
	void		*drivers;		/* nur fÅr interne Dialoge */
	short 		option_flags;		/* Flags, u.a. PDLG_PRINTING, PDLG_PREFS */
	short 		sub_id;			/* Kennung des Unterdialogs, wird fÅr globale Unterdialoge von pdlg_add() eingetragen */
	void		*dialog; 		/* Zeiger auf die Struktur des Fensterdialogs oder 0L */
	OBJECT		*tree;			/* Zeiger auf den zusammengesetzen Objektbaum */
	short 		index_offset;		/* Indexverschiebung des Unterdialogs */
	short 		reserved1;
	long		reserved2;
	long		reserved3;
	long		reserved4;

	PDLG_INIT	init_dlg;		/* Initialisierungsfunktion */
	PDLG_HNDL	do_dlg;			/* Behandlungsfunktion */
	PDLG_RESET	reset_dlg;		/* ZurÅcksetzfunktion */
	long		reserved5;

	OBJECT		*sub_icon;		/* Zeiger auf das Icon fÅr die Listbox */
	OBJECT		*sub_tree;		/* Zeiger auf den Objektbaum des Unterdialogs */
	long		reserved6;
	long		reserved7;

	long		private1;		/* dialogeigene Informationen */
	long		private2;
	long		private3;
	long		private4;

};


/*----------------------------------------------------------------------------------------*/ 
/* einstellbare Farbmodi eines Druckermodus																*/
/*----------------------------------------------------------------------------------------*/ 
#define	CC_MONO			0x0001		/* 2 Grautîne */
#define	CC_4_GREY		0x0002		/* 4 Grautîne */
#define	CC_8_GREY		0x0004		/* 8 Grautîne */
#define	CC_16_GREY		0x0008		/* 16 Grautîne */
#define	CC_256_GREY 		0x0010		/* 256 Grautîne */
#define	CC_32K_GREY 		0x0020		/* 32768 Farben in Grautîne wandeln */
#define	CC_65K_GREY 		0x0040		/* 65536 Farben in Grautîne wandeln */
#define	CC_16M_GREY 		0x0080		/* 16777216 Farben in Grautîne wandeln */

#define	CC_2_COLOR		0x0100		/* 2 Farben */
#define	CC_4_COLOR		0x0200		/* 4 Farben */
#define	CC_8_COLOR		0x0400		/* 8 Farben */
#define	CC_16_COLOR 		0x0800		/* 16 Farben */
#define	CC_256_COLOR		0x1000		/* 256 Farben */
#define	CC_32K_COLOR		0x2000		/* 32768 Farben */
#define	CC_65K_COLOR		0x4000		/* 65536 Farben */
#define	CC_16M_COLOR		0x8000		/* 16777216 Farben */

#define	NO_CC_BITS		16

/*----------------------------------------------------------------------------------------*/ 
/* einstellbare Rasterverfahren																				*/
/*----------------------------------------------------------------------------------------*/ 
#define	DC_NONE			0		/* keine Rasterverfahren */
#define	DC_FLOYD 		1		/* einfacher Floyd-Steinberg */
#define	NO_DC_BITS		1

/*----------------------------------------------------------------------------------------*/ 
/* Druckereigenschaften 																						*/
/*----------------------------------------------------------------------------------------*/ 
#define	PC_FILE			0x0001		/* Drucker kann Åber GEMDOS-Dateien angesprochen werden */
#define	PC_SERIAL		0x0002		/* Drucker kann auf der seriellen Schnittstelle angesteuert werden */
#define	PC_PARALLEL 		0x0004		/* Drucker kann auf der parallelen Schnittstelle angesteuert werden */
#define	PC_ACSI			0x0008		/* Drucker kann auf der ACSI-Schnittstelle ausgeben */
#define	PC_SCSI			0x0010		/* Drucker kann auf der SCSI-Schnittstelle ausgeben */

#define	PC_BACKGROUND		0x0080		/* Treiber kann im Hintergrund ausdrucken */

#define	PC_SCALING		0x0100		/* Treiber kann Seite skalieren */
#define	PC_COPIES		0x0200		/* Treiber kann Kopien einer Seite erstellen */

/*----------------------------------------------------------------------------------------*/ 
/* Moduseigenschaften																							*/
/*----------------------------------------------------------------------------------------*/ 
#define	MC_PORTRAIT 		0x0001		/* Seite kann im Hochformat ausgegeben werden */
#define	MC_LANDSCAPE		0x0002		/* Seite kann im Querformat ausgegeben werden */
#define	MC_REV_PTRT 		0x0004		/* Seite kann um 180 Grad gedreht im Hochformat ausgegeben werden */
#define	MC_REV_LNDSCP		0x0008		/* Seite kann um 180 Grad gedreht im Querformat ausgegeben werden */
#define	MC_ORIENTATION		0x000f

#define	MC_SLCT_CMYK		0x0400		/* Treiber kann bestimmte Farbebenen ausgeben */
#define	MC_CTRST_BRGHT		0x0800		/* Treiber kann Kontrast und Helligkeit verÑndern */

/*----------------------------------------------------------------------------------------*/ 
/* plane_flags 																									*/
/*----------------------------------------------------------------------------------------*/ 
#define	PLANE_BLACK 		0x0001
#define	PLANE_YELLOW		0x0002
#define	PLANE_MAGENTA		0x0004
#define	PLANE_CYAN		0x0008


/* <driver_mode> */
#define	DM_BG_PRINTING		0x0001		/* Flag fÅr Hintergrunddruck */

/*----------------------------------------------------------------------------------------*/ 

/* <page_flags> */
#define	PG_EVEN_PAGES		0x0001		/* nur Seiten mit gerader Seitennummer ausgeben */
#define	PG_ODD_PAGES		0x0002		/* nur Seiten mit ungerader Seitennummer ausgeben */

/* <first_page/last_page> */
#define	PG_MIN_PAGE 		1
#define	PG_MAX_PAGE 		9999

/* <orientation> */
#define	PG_UNKNOWN		0x0000		/* Ausrichtung unbekannt und nicht verstellbar */
#define	PG_PORTRAIT 		0x0001		/* Seite im Hochformat ausgeben */
#define	PG_LANDSCAPE		0x0002		/* Seite im Querformat ausgeben */

struct _prn_settings
{
	long		magic;			/* 'pset' */
	long		length;			/* StrukturlÑnge */
	long		format;			/* Strukturtyp */
	long		reserved;

	long		page_flags; 		/* Flags, u.a. gerade Seiten, ungerade Seiten */
	short		first_page; 		/* erste zu druckende Seite */
	short		last_page;		/* letzte zu druckende Seite */
	short		no_copies;		/* Anzahl der Kopien */
	short		orientation;		/* Drehung */
	long		scale;			/* Skalierung: 0x10000L entspricht 100% */

	short		driver_id;		/* VDI-GerÑtenummer */
	short		driver_type;		/* Typ des eingestellten Treibers */
	long		driver_mode;		/* Flags, u.a. fÅr Hintergrunddruck */
	long		reserved1;
	long		reserved2;
	
	long		printer_id; 		/* Druckernummer */
	long		mode_id; 		/* Modusnummer */
	short		mode_hdpi;		/* horizontale Auflîsung in dpi */
	short		mode_vdpi;		/* vertikale Auflîsung in dpi */
	long		quality_id; 		/* Druckmodus (hardwÑremÑûige QualitÑt, z.B. Microweave oder Econofast) */

	long		color_mode; 		/* Farbmodus */
	long		plane_flags;		/* Flags fÅr auszugebende Farbebenen (z.B. nur cyan) */
	long		dither_mode;		/* Rasterverfahren */
	long		dither_value;		/* Parameter fÅr das Rasterverfahren */

	long		size_id; 		/* Papierformat */
	long		type_id; 		/* Papiertyp (normal, glossy) */
	long		input_id;		/* Papiereinzug */
	long		output_id;		/* Papierauswurf */

	long		contrast;		/* Kontrast: 0x10000L entspricht Normaleinstellung */
	long		brightness; 		/* Helligkeit: 0x1000L entspricht Normaleinstellung */
	long		reserved3;
	long		reserved4;

	long		reserved5;
	long		reserved6;
	long		reserved7;
	long		reserved8;

	char		device[128];		/* Dateiname fÅr den Ausdruck */

	struct
	{
		char	inside[120];
	} mac_settings;
};


/* <dialog_flags> fÅr pdlg_create() */
#define PDLG_3D			0x0001

/* <option_flags> fÅr pdlg_open/do() */
#define PDLG_PREFS		0x0000		/* Einstelldialog anzeigen */
#define PDLG_PRINT		0x0001		/* Druckdialog anzeigen */

#define PDLG_ALWAYS_COPIES	0x0010		/* immer Kopien anbieten */
#define PDLG_ALWAYS_ORIENT	0x0020		/* immer Querformat anbieten */
#define PDLG_ALWAYS_SCALE	0x0040		/* immer Skalierung anbieten */

#define	PDLG_EVENODD		0x0100		/* Option fÅr gerade und ungerade Seiten anbieten */

/* <button> fÅr pdlg_evnt()/pdlg_do */
#define	PDLG_CANCEL 1				/* "Abbruch" wurde angewÑhlt */
#define	PDLG_OK		2			/* "OK" wurde gedrÅckt */

short		pdlg_add_printers 		(PRN_DIALOG *prn_dialog, DRV_INFO *drv_info);
short		pdlg_add_sub_dialogs 		(PRN_DIALOG *prn_dialog, PDLG_SUB *sub_dialogs);
short		pdlg_close			(PRN_DIALOG *prn_dialog, short *x, short *y);
PRN_DIALOG *	pdlg_create			(short dialog_flags);
short		pdlg_delete 			(PRN_DIALOG *prn_dialog);
short		pdlg_dflt_settings		(PRN_DIALOG *prn_dialog, PRN_SETTINGS *settings);
short		pdlg_do				(PRN_DIALOG *prn_dialog, PRN_SETTINGS *settings, char *document_name, short option_flags);
short		pdlg_evnt			(PRN_DIALOG *prn_dialog, PRN_SETTINGS *settings, EVNT *events, short *button);
short		pdlg_free_settings		(PRN_SETTINGS *settings);
long		pdlg_get_setsize		(void);
PRN_SETTINGS *	pdlg_new_settings		(PRN_DIALOG *prn_dialog);
short		pdlg_open			(PRN_DIALOG *prn_dialog, PRN_SETTINGS *settings, char *document_name, short option_flags, short x, short y);
short		pdlg_remove_printers 		(PRN_DIALOG *prn_dialog);
short		pdlg_remove_sub_dialogs 	(PRN_DIALOG *prn_dialog);
short		pdlg_save_default_settings	(PRN_DIALOG *prn_dialog, PRN_SETTINGS *settings);
short		pdlg_update 			(PRN_DIALOG *prn_dialog, char *document_name);
short		pdlg_use_settings 		(PRN_DIALOG *prn_dialog, PRN_SETTINGS *settings);
short		pdlg_validate_settings		(PRN_DIALOG *prn_dialog, PRN_SETTINGS *settings);


/******************************************************************************
 * Listbox definitions
 */

typedef void * LIST_BOX;

typedef struct lbox_item LBOX_ITEM;
struct lbox_item
{
	LBOX_ITEM	*next;		/* Pointer to the next entry in the list */
	short		selected;	/* Specifies if the object is selected */

	short		data1;		/* Data for the program... */
	void		*data2;
	void		*data3;

};

typedef void  __CDECL (*SLCT_ITEM)(LIST_BOX *box, OBJECT *tree, struct lbox_item *item, void *user_data, short obj_index, short last_state);
typedef short __CDECL (*SET_ITEM)(LIST_BOX *box, OBJECT *tree, struct lbox_item *item, short obj_index, void *user_data, GRECT *rect, short first);

#define	LBOX_VERT		1	/* Listbox with vertical slider */
#define	LBOX_AUTO		2	/* Auto-scrolling */
#define	LBOX_AUTOSLCT		4	/* Automatic display during auto-scrolling */
#define	LBOX_REAL		8	/* Real-time slider */
#define	LBOX_SNGL		16	/* Only a selectable entry */
#define	LBOX_SHFT		32	/* Multi-selection with Shift */
#define	LBOX_TOGGLE		64	/* Toggle status of an entry at selection */
#define	LBOX_2SLDRS		128	/* Listbox has a horiz. and a vertical slider */

/* #defines for listboxes with only one slider */
#define	lbox_get_visible	lbox_get_avis
#define	lbox_get_first		lbox_get_afirst
#define	lbox_set_slider		lbox_set_asldr
#define	lbox_scroll_to		lbox_ascroll_to

LIST_BOX *	lbox_create (OBJECT *tree, SLCT_ITEM slct, SET_ITEM set,
			     LBOX_ITEM *items, short visible_a, short first_a,
			     short *ctrl_objs, short *objs, short flags,
			     short pause_a, void *user_data, void *dialog,
			     short visible_b, short first_b, short entries_b,
			     short pause_b);

void		lbox_update (LIST_BOX *box, GRECT *rect);
short		lbox_do (LIST_BOX *box, short obj);
short		lbox_delete (LIST_BOX *box);

short		lbox_cnt_items (LIST_BOX *box);
OBJECT *	lbox_get_tree (LIST_BOX *box);
short		lbox_get_avis (LIST_BOX *box);
void *		lbox_get_udata (LIST_BOX *box);
short		lbox_get_afirst (LIST_BOX *box);
short		lbox_get_slct_idx (LIST_BOX *box);
LBOX_ITEM *	lbox_get_items (LIST_BOX *box);
LBOX_ITEM *	lbox_get_item (LIST_BOX *box, short n);
LBOX_ITEM *	lbox_get_slct_item (LIST_BOX *box);
short		lbox_get_idx (LBOX_ITEM *items, LBOX_ITEM *search);
short		lbox_get_bvis (LIST_BOX *box);
short		lbox_get_bentries (LIST_BOX *box);
short		lbox_get_bfirst (LIST_BOX *box);

void		lbox_set_asldr (LIST_BOX *box, short first, GRECT *rect);
void		lbox_set_items (LIST_BOX *box, LBOX_ITEM *items);
void		lbox_free_items (LIST_BOX *box);
void		lbox_free_list (LBOX_ITEM *items);
void		lbox_ascroll_to (LIST_BOX *box, short first, GRECT *box_rect,
				 GRECT *slider_rect);
void		lbox_set_bsldr (LIST_BOX *box, short first, GRECT *rect);
void		lbox_set_bentries (LIST_BOX *box, short entries);
void		lbox_bscroll_to (LIST_BOX *box, short first, GRECT *box_rect,
				 GRECT *slider_rect);


/******************************************************************************
 * Wdialog definitions
 */

typedef void * DIALOG;
typedef short __CDECL (*HNDL_OBJ)(DIALOG *dialog, EVNT *events, short obj, short clicks, void *data);

DIALOG *wdlg_create (HNDL_OBJ handle_exit, OBJECT *tree, void *user_data, short code, void *data, short flags);
short	wdlg_open (DIALOG *dialog, char *title, short kind, short x, short y, short code, void *data);
short	wdlg_close (DIALOG *dialog, short *x, short *y);
short	wdlg_delete (DIALOG *dialog);
short	wdlg_get_tree (DIALOG *dialog, OBJECT **tree, GRECT *r);
short	wdlg_get_edit (DIALOG *dialog, short *cursor);
void *	wdlg_get_udata (DIALOG *dialog);
short	wdlg_get_handle (DIALOG *dialog);
short	wdlg_set_edit (DIALOG *dialog, short obj);
short	wdlg_set_tree (DIALOG *dialog, OBJECT *tree);
short	wdlg_set_size (DIALOG *dialog, GRECT *size);
short	wdlg_set_iconify (DIALOG *dialog, GRECT *g, char *title, OBJECT *tree, short obj);
short	wdlg_set_uniconify (DIALOG *dialog, GRECT *g, char *title, OBJECT *tree);
short	wdlg_evnt (DIALOG *dialog, EVNT *events );
void	wdlg_redraw (DIALOG *dialog, GRECT *rect, short obj, short depth);


/* Definitions for <flags> */
#define  WDLG_BKGD   1           /* Permit background operation */

/* Function numbers for <obj> with handle_exit(...) */
#define  HNDL_INIT   -1          /* Initialise dialog */
#define  HNDL_MESG   -2          /* Initialise dialog */
#define  HNDL_CLSD   -3          /* Dialog window was closed */
#define  HNDL_OPEN   -5          /* End of dialog initialisation (second  call at end of wdlg_init) */
#define  HNDL_EDIT   -6          /* Test characters for an edit-field */
#define  HNDL_EDDN   -7          /* Character was entered in edit-field */
#define  HNDL_EDCH   -8          /* Edit-field was changed */
#define  HNDL_MOVE   -9          /* Dialog was moved */
#define  HNDL_TOPW   -10         /* Dialog-window has been topped */
#define  HNDL_UNTP   -11         /* Dialog-window is not active */


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
short	mt_edit_get_colour	(OBJECT *tree, short obj, short *tcolour, short *bcolour, short *global);
short	mt_edit_get_cursor	(OBJECT *tree, short obj, char **cursorpos, short *global);
short	mt_edit_get_font	(OBJECT *tree, short obj, short *fontID, short *fontH, short *fontPix, short *mono, short *global);
void	mt_edit_set_buf		(OBJECT *tree, short obj, char *buf, long buflen, short *global);
void	mt_edit_set_format	(OBJECT *tree, short obj, short tabwidth, short autowrap, short *global);
void	mt_edit_set_font	(OBJECT *tree, short obj, short fontID, short fontH, short fontPix, short mono, short *global);
void	mt_edit_set_colour	(OBJECT *tree, short obj, short tcolour, short bcolour, short *global);
void	mt_edit_set_cursor	(OBJECT *tree, short obj, char *cursorpos, short *global);
short	mt_edit_resized		(OBJECT *tree, short obj, short *oldrh, short *newrh, short *global);
short	mt_edit_get_dirty	(OBJECT *tree, short obj, short *global);
void	mt_edit_set_dirty	(OBJECT *tree, short obj, short dirty, short *global);
void	mt_edit_get_sel		(OBJECT *tree, short obj, char **bsel, char **esel, short *global);
void	mt_edit_get_pos		(OBJECT *tree, short obj, short *xscroll, long *yscroll, char **cyscroll, char **cursorpos, short *cx, short *cy, short *global);
void	mt_edit_set_pos		(OBJECT *tree, short obj, short xscroll, long yscroll, char *cyscroll, char *cursorpos, short cx, short cy, short *global);
short	mt_edit_scroll		(OBJECT *tree, short obj, short whdl, long yscroll, short xscroll, short *global);
void	mt_edit_get_scrollinfo (OBJECT *tree, short obj, long *nlines, long *yscroll, short *yvis, short *yval, short *ncols, short *xscroll, short *xvis, short *global);
#define edit_create()  mt_edit_create(aes_global)
#define edit_open(a,b) mt_edit_open(a,b,aes_global)
#define edit_close(a,b) mt_edit_close(a,b,aes_global)
#define edit_delete(a) mt_edit_delete(a,aes_global)
#define edit_cursor(a,b,c,d) mt_edit_cursor(a,b,c,d,aes_global)
#define edit_evnt(a,b,c,d,e) mt_edit_evnt(a,b,c,d,e,aes_global)
#define edit_get_buf(a,b,c,d,e) mt_edit_get_buf(a,b,c,d,e,aes_global)
#define edit_set_buf(a,b,c,d) mt_edit_set_buf(a,b,c,d,aes_global)
#define edit_set_format(a,b,c,d) mt_edit_set_format(a,b,c,d,aes_global)
#define edit_get_format(a,b,c,d) mt_edit_get_format(a,b,c,d,aes_global)
#define edit_set_font(a,b,c,d,e,f) mt_edit_set_font(a,b,c,d,e,f,aes_global)
#define edit_get_font(a,b,c,d,e,f) mt_edit_get_font(a,b,c,d,e,f,aes_global)
#define edit_set_colour(a,b,c,d) mt_edit_set_colour(a,b,c,d,aes_global)
#define edit_resized(a,b,c,d) mt_edit_resized(a,b,c,d,aes_global)
#define edit_get_dirty(a,b) mt_edit_get_dirty(a,b,aes_global)
#define edit_set_dirty(a,b,c) mt_edit_set_dirty(a,b,c,aes_global)
#define edit_get_sel(a,b,c,d) mt_edit_get_sel(a,b,c,d,aes_global)
#define edit_get_pos(a,b,c,d,e,f,g,h) mt_edit_get_pos(a,b,c,d,e,f,g,h,aes_global)
#define edit_set_pos(a,b,c,d,e,f,g,h) mt_edit_set_pos(a,b,c,d,e,f,g,h,aes_global)
#define edit_get_scrollinfo(a,b,c,d,e,f,g,h,i) mt_edit_get_scrollinfo(a,b,c,d,e,f,g,h,i,aes_global)
#define edit_scroll(a,b,c,d,e) mt_edit_scroll(a,b,c,d,e,aes_global)
/**@}*/

/*******************************************************************************
 * The VDI extentsions of NVDI/FSM/Speedo
 */

/*
 * The following functions requires EdDI version 1.x or higher
 */
void	v_clsbm		(short handle);
void	v_opnbm		(short *work_in, MFDB *bitmap, short *handle, short *work_out);
void	vq_scrninfo	(short handle, short *work_out);


/*
 * The following functions requires NVDI version 2.x or higher
 */
short	v_bez_on	(short handle);
void	v_bez_off	(short handle);
void	v_bez		(short handle, short count, short *xyarr, char *bezarr, short *extent, short *totpts, short *totmoves);
void	v_bez_fill	(short handle, short count, short *xyarr, char *bezarr, short *extent, short *totpts, short *totmoves);
void 	v_bez_qual	(short handle, short percent, short *actual);


/*
 * The following functions requires NVDI version 3.x or higher
 */
typedef struct
{
	long		size;
	short		format;
	short		id;
	short		index;
	char		font_name[50];
	char		family_name[50];
	char		style_name[50];
	char		file_name1[200];
	char		file_name2[200];
	char		file_name3[200];
	short		pt_cnt;
	short		pt_sizes[64];
} XFNT_INFO;

typedef unsigned short WCHAR; /* 16bit string, eg. for unicode */

void	v_ftext         (VdiHdl, short x, short y, const char  *str);
void	v_ftext16       (VdiHdl, short x, short y, const WCHAR *wstr);
void	v_ftext16n      (VdiHdl, PXY pos, const WCHAR *wstr, short num);
void	v_ftext_offset  (VdiHdl, short x, short y,
                               const char  *str,  const short *offset);
void	v_ftext_offset16(VdiHdl, short x, short y,
                               const WCHAR *wstr, const short *offset);
void	v_getbitmap_info(VdiHdl, short ch, long *advancex, long *advancey,
                               long *xoffset, long *yoffset, short *width,
                               short *height, short **bitmap);
void	v_getoutline    (VdiHdl, short ch, short *xyarray, char *bezarray,
                               short maxverts, short *numverts);

void	vq_devinfo     (VdiHdl, short device, short *dev_open,
                              char *file_name, char *device_name);
short	vq_ext_devinfo (VdiHdl, short device, short *dev_exists,
                              char *file_path, char *file_name, char *name);

void	vqt_advance     (VdiHdl, short ch, short *advx, short *advy,
                               short *xrem, short *yrem);
void	vqt_advance32   (VdiHdl, short ch, long *advx, long *advy);
short	vqt_ext_name    (VdiHdl, short __index,
                               char *name, short *font_format, short *flags);
void	vqt_f_extent    (VdiHdl, const char  *str, short extent[]);
void	vqt_f_extent16  (VdiHdl, const WCHAR *str, short extent[]);
void	vqt_f_extent16n (VdiHdl, const WCHAR *str, short num, short extent[]);
void	vqt_fontheader  (VdiHdl, char *buffer, char *pathname);
short	vqt_name_and_id (VdiHdl, short font_format,
                               char *font_name, char *ret_name);
void	vqt_pairkern    (VdiHdl, short ch1, short ch2, long *x, long *y);
void	vqt_real_extent (VdiHdl, short x, short y, char *string, short extent[]);
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
void  vst_width	(VdiHdl, short width, short *char_width, short *char_height, short *cell_width, short *cell_height);


/*
 * The following functions requires NVDI version 4.x or higher
 */
short	vqt_char_index (short handle, short scr_index, short scr_mode, short dst_mode);
short vst_map_mode   (short handle, short mode);


/*
 * The following functions requires NVDI version 5.x or higher
 */
typedef struct
{
	unsigned short	reserved;
	unsigned short	red;
	unsigned short	green;
	unsigned short	blue;
} COLOR_RGB;

typedef struct
{
	unsigned short	cyan;
	unsigned short	magenta;
	unsigned short	yellow;
	unsigned short	black;
} COLOR_CMYK;

typedef union
{
	COLOR_RGB	rgb;
	COLOR_CMYK	cmyk;
} COLOR_ENTRY;

typedef struct
{
	long		magic;
	long		length;
	long		format;
	long		reserved;

	long		map_id;
	long		color_space;
	long		flags;
	long		no_colors;

	long		reserved1;
	long		reserved2;
	long		reserved3;
	long		reserved4;

#ifdef __GNUC__
	COLOR_ENTRY	colors[0];
#else
	COLOR_ENTRY	colors[];
#endif

} COLOR_TAB;

typedef COLOR_TAB *CTAB_PTR;
typedef COLOR_TAB *CTAB_REF;


typedef void INVERSE_CTAB;
typedef INVERSE_CTAB *ITAB_REF;

typedef struct _gcbitmap GCBITMAP;
struct _gcbitmap
{
	long		magic;
	long		length;
	long		format;
	long		reserved;

	unsigned char	*addr;
	long		width;
	long		bits;
	unsigned long	px_format;

	long		xmin;
	long		ymin;
	long		xmax;
	long		ymax;

	CTAB_REF	*ctab;
	ITAB_REF 	*itab;
	long		reserved0;
	long		reserved1;
};


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


__END_DECLS

#endif /* _GEMLIB_X_H_ */

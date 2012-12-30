/*
 * CFLIB, a GEM library for ATARI/TOS
 * Copyright (C) 1999, 2000 Christian Felsch
 * 
 * Modified for FreeMiNT CVS by Frank Naumann <fnaumann@freemint.de>
 * 
 * Please send suggestions, patches or bug reports to me or
 * the MiNT mailing list.
 * 
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
 * 
 */

#ifndef _cflib_h_
#define _cflib_h_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <gem.h>


/*******************************************************************************
 * Version
 *******************************************************************************/

/* Major and minor version number of the GEMLib package.  Use these macros 
   to test for features in specific releases.  */
#define __CFLIB__		__CFLIB_MAJOR__
#define	__CFLIB_MAJOR__		0
#define	__CFLIB_MINOR__		21
#define __CFLIB_REVISION__	0
#define __CFLIB_BETATAG__	""

#if !defined(__GEMLIB__)
    || (__GEMLIB_MAJOR__ != 0
        || __GEMLIB_MINOR__ < 43
        || (__GEMLIB_MINOR__ == 43 && __GEMLIB_REVISION__ < 2))
#error This cflib version require an up-to-date gemlib.
#endif

/*******************************************************************************
 * spezielle Typen der CF-Lib
 *******************************************************************************/

typedef enum
{
	null, Con, TCon, Datei, Terminal,
	Modem1, Modem2, Seriell1, Seriell2, Prn
} DEBUGDEV;


typedef struct popup POPUP;
struct popup
{
	OBJECT	*tree;			/* der Objektbaum */
	short	max_item;		/* maximal mgliche Anzahl */
	short	akt_item;		/* aktuelle Anzahl */
	short	item_len;		/* Lnge eines Eintrages */
};


typedef void (*MDIAL_WCB)(short *msg);

typedef struct mdial MDIAL;
struct mdial
{
	OBJECT	*tree;
	short	win_handle;
	char	*win_name;
	short	edit_obj,
		edit_idx,
		next_obj;
	short	save_frame, 
		delta_y;
	short	is_shaded;
	MDIAL	*next;
};


typedef struct wdialog WDIALOG;

typedef void (*WDIAL_OCB)(WDIALOG *dial);
typedef int  (*WDIAL_XCB)(WDIALOG *dial, short exit_obj);

#define WOCB_NULL	NULL
#define WXCB_NULL	NULL

struct wdialog
{
	WDIALOG	*next;

	OBJECT	*tree;			/* Objektbaum */
	OBJECT	*icon;			/* Icon fr Iconify */
	short	mode;			/* aktueller Status */
	short	win_handle;		/* Fensterhandle */
	char	win_name[80];		/* Fenstertitel */
	short	win_kind;		/* Elemente */
	GRECT	work;			/* Fenstergre */
	short	title_obj;		/* Objektnummer des Titelobjektes */
	short	cancel_obj;		/*       "      des Abbruchbuttons */
	short	delta_y;		/* Offset bis zum Titelobjekt */
	short	edit_idx,		/* Objektnummern fr die Editfelder */
		next_obj,
		edit_obj;

	WDIAL_OCB open_cb;	
	WDIAL_XCB exit_cb;	
};

/*******************************************************************************
 * globals.c
 *******************************************************************************/

extern short	gl_phys_handle;
extern GRECT	gl_desk;	

extern short	sys_big_id, sys_big_height, sys_big_pts,
		sys_sml_id, sys_sml_height, sys_sml_pts,
		sys_wchar, sys_hchar, sys_wbox, sys_hbox;

extern short	gl_wchar, gl_hchar, gl_wbox, gl_hbox;

extern short	gl_gdos;
extern short	gl_planes;

extern short	gl_gem;
extern short	gl_mint;
extern short	gl_naes;
extern long	gl_xaaes;
extern short	gl_magx;
extern short	gl_nvdi;

extern char 	gl_appdir[];

/*******************************************************************************
 * alerts functions
 *******************************************************************************/

short	do_alert	(short def, short undo, char *str);
short	do_walert	(short def, short undo, char *str, char *win_title);

/*******************************************************************************
 * app functions
 *******************************************************************************/
 
void	init_app	(char *rsc);
void	exit_gem	(void);
void	exit_app	(int ret);
void	hide_mouse	(void);
short  	hide_mouse_if_needed (GRECT *rect);
void	show_mouse	(void);
#if ! (( __GEMLIB_MAJOR__ > 0 ) || ( __GEMLIB_MINOR__ > 42 ) || (( __GEMLIB_MINOR__ == 42 ) && ( __GEMLIB_REVISION__ > 2 )))
short	appl_xgetinfo (short type, short *out1, short *out2, short *out3, short *out4);
#endif

/*******************************************************************************
 * asciitable functions
 *******************************************************************************/

short 	ascii_table (short id, short pts);
void	set_asciitable_strings (char *title, char *button);

/*******************************************************************************
 * colorpop functions
 *******************************************************************************/

#define MAX_COLORPOP 10 /* Maximale Anzahl von Farb-Objekten in einem Programm */

short	init_colorpop	(short maxplanes);
void	exit_colorpop	(void);

void	fix_colorpopobj	(OBJECT *tree, short obj, short color);
void	set_popobjcolor	(OBJECT *tree, short obj, short color);
short	get_popobjcolor	(OBJECT *tree, short obj);

short	do_colorpop	(short x, short y, short item, short planes, short show_noncolor);
short	handle_colorpop	(OBJECT *dial, short dial_obj, short mode, short planes, short show_noncolor);

/*******************************************************************************
 * comm functions
 *******************************************************************************/

void send_m_special	(int mode, int app);
void send_vastart	(int id, char *str);
void send_scchanged	(void);

/*******************************************************************************
 * cookie functions
 *******************************************************************************/

int	getcookie	(char *cookie, long *value);

/*******************************************************************************
 * debug functions
 *******************************************************************************/

int	gl_debug;

void	debug_init	(char *prgName, DEBUGDEV dev, char *file);
void	debug_exit	(void);
void	debug		(char *FormatString, ...);

/*******************************************************************************
 * dragdrop functions
 *******************************************************************************/

#ifndef DD_OK
#define DD_OK		0
#define DD_NAK		1
#define DD_EXT		2
#define DD_LEN		3
#define DD_TIMEOUT	4000
#define DD_NUMEXTS	8
#define DD_EXTSIZE	32
#define DD_NAMEMAX	128
#define DD_HDRMAX	(8+DD_NAMEMAX)
#endif

int	dd_create	(int apid, int winid, int msx, int msy, int kstate, char *exts);
int	dd_stry		(int fd, char *ext, char *name, long size);
void	dd_close	(int fd);
int	dd_open		(int ddnam, char *ext);
int	dd_rtry		(int fd, char *name, char *ext, long *size);
int	dd_reply	(int fd, int ack);

/*******************************************************************************
 * file functions
 *******************************************************************************/

int	file_exists	(char *filename);
int	path_exists	(char *pathname);

int	get_path	(char *path, char drive);
int	set_path	(char *path);

void	split_filename	(char *fullname, char *path, char *name);
void 	split_extension	(char *filename, char *name, char *extension);
void 	set_extension	(char *filename, char *new_ext);

int 	make_normalpath	(char *path);
void 	make_shortpath	(char *path, char *shortpath, int maxlen);

#define NO_CASE		0 /* TOS-FS */
#define HALF_CASE	1 /* VFAT/Mac */
#define FULL_CASE	2 /* Minix */
int	fs_long_name	(char *filename);
int	fs_case_sens	(char *filename);

/*******************************************************************************
 * filesel functions
 *******************************************************************************/

typedef int (*FSEL_CB)(char *path, char *name);
#define FSCB_NULL NULL

int select_file (char *path, char *name, char *mask, char *title, FSEL_CB open_cb);

/*******************************************************************************
 * fontsel functions
 *******************************************************************************/

#define FS_M_XFSL		1		/* Cookie xFSL */
#define FS_M_FPROT		2		/* Fontprotokoll */
#define FS_M_MAGX		4		/* MagiC fnts_* */
#define FS_M_ALL		(FS_M_XFSL|FS_M_FPROT|FS_M_MAGX)

#define FS_F_MONO		8		/* nur monospaced */

short do_fontsel (short flags, char *title, short *id, short *pts);

/*******************************************************************************
 * form_do functions
 *******************************************************************************/

short	cf_form_do (OBJECT *tree, short *ed_start);
short 	simple_dial (OBJECT *tree, short start_edit);

typedef short (*KEY_CB)(OBJECT *tree, short edit_obj, short kstate, short *kreturn, short *next_obj);

KEY_CB	set_formdo_keycb (KEY_CB keycb);

/*******************************************************************************
 * magx functions
 *******************************************************************************/
extern int	get_magx_version(void);

#define MX_NOTXOBJ		0		/* kein MagiC-Objekt */
#define MX_UNDERLINE		1		/* String als berschrift */
#define MX_RADIO		2		/* Radio ohne Shortcut */
#define MX_SCRADIO		3		/* Radio mit Shortcut */
#define MX_CHECK		4		/* Check ohne Shortcut */
#define MX_SCCHECK		5		/* Check mit Shortcut */
#define MX_SCEXIT		6		/* EXIT mit Shortcut */
#define MX_SCSTRING		7		/* String mit Shortcut */
#define MX_GROUPBOX		8		/* Gruppenrahmen */
#define MX_EDIT3D		9		/* 3D-Editfeld */

#define MX_GROUPBOX2		10		/* Gruppenrahmen, kleine Schrift */

#define MX_UNKNOWN		-1		/* Unbekanntes WHITEBACK-Obj */

short	get_magx_obj (OBJECT *tree, short obj);
short	get_magx_shortcut (OBJECT *tree, short obj, char *c);

/*******************************************************************************
 * mdial functions
 *******************************************************************************/

MDIAL *	open_mdial	(OBJECT *tree, short edit_start);
void	close_mdial	(MDIAL *mdial);
short	do_mdial	(MDIAL *mdial);

short 	simple_mdial	(OBJECT *tree, short edit_start);

void 	set_mdial_wincb(MDIAL_WCB cb);

void	redraw_mdobj	(MDIAL *mdial, short obj);
void 	change_mdedit	(MDIAL *mdial, short new);

/*******************************************************************************
 * menu functions
 *******************************************************************************/

short	create_menu (OBJECT *tree);
void 	delete_menu (void);

void 	disable_menu (void);
void 	enable_menu (void);

short	is_menu_key (short kreturn, short kstate, short *title, short *item);

/*******************************************************************************
 * misc functions
 *******************************************************************************/

long	ts2ol (short i1, short i2);
void 	ol2ts (long l, short *i1, short *i2);

void 	save_background (GRECT *box, MFDB *buffer);
void 	restore_background (GRECT *box, MFDB *buffer);

void *	malloc_global (long size);

int	get_patchlev (const char *id_str, char *pl);

/*******************************************************************************
 * nkcc functions
 *******************************************************************************/

   /* NKCC key code flags */
#define NKF_FUNC     0x8000         /* function          */
#define NKF_RESVD    0x4000         /* resvd, ignore it! */
#define NKF_NUM      0x2000         /* numeric pad       */
#define NKF_CAPS     0x1000         /* CapsLock          */
#define NKF_ALT      0x0800         /* Alternate         */
#define NKF_CTRL     0x0400         /* Control           */
#define NKF_SHIFT    0x0300         /* any Shift key     */
#define NKF_LSH      0x0200         /* left Shift key    */
#define NKF_RSH      0x0100         /* right Shift key   */

   /* special key codes for keys performing a function */
#define NK_INVALID   0x00           /* invalid key code  */
#define NK_UP        0x01           /* cursor up         */
#define NK_DOWN      0x02           /* cursor down       */
#define NK_RIGHT     0x03           /* cursor right      */
#define NK_LEFT      0x04           /* cursor left       */
#define NK_M_PGUP    0x05           /* Mac: page up      */
#define NK_M_PGDOWN  0x06           /* Mac: page down    */
#define NK_M_END     0x07           /* Mac: end          */
#define NK_BS        0x08           /* Backspace         */
#define NK_TAB       0x09           /* Tab               */
#define NK_ENTER     0x0a           /* Enter             */
#define NK_INS       0x0b           /* Insert            */
#define NK_CLRHOME   0x0c           /* Clr/Home          */
#define NK_RET       0x0d           /* Return            */
#define NK_HELP      0x0e           /* Help              */
#define NK_UNDO      0x0f           /* Undo              */
#define NK_F1        0x10           /* function key #1   */
#define NK_F2        0x11           /* function key #2   */
#define NK_F3        0x12           /* function key #3   */
#define NK_F4        0x13           /* function key #4   */
#define NK_F5        0x14           /* function key #5   */
#define NK_F6        0x15           /* function key #6   */
#define NK_F7        0x16           /* function key #7   */
#define NK_F8        0x17           /* function key #8   */
#define NK_F9        0x18           /* function key #9   */
#define NK_F10       0x19           /* function key #10  */
#define NK_M_F11     0x1a           /* Mac: func key #11 */
#define NK_ESC       0x1b           /* Esc               */
#define NK_M_F12     0x1c           /* Mac: func key #12 */
#define NK_M_F14     0x1d           /* Mac: func key #14 */
#define NK_RVD1E     0x1e           /* reserved!         */
#define NK_DEL       0x1f           /* Delete            */

short		nkc_init	(void);
unsigned short	nkc_tos2n	(long toskey);
long		nkc_n2tos	(long nkcode);
unsigned char	nkc_toupper	(unsigned char chr);
unsigned char	nkc_tolower	(unsigned char chr);

unsigned short	gem_to_norm	(short ks, short kr);
void 		norm_to_gem	(unsigned long norm, short *ks, short *kr);

void 		str_toupper	(char *str);
void 		str_tolower	(char *str);

/*******************************************************************************
 * objc functions
 *******************************************************************************/

void 	set_obspec	(OBJECT *tree, short obj, long spec);
long 	get_obspec	(OBJECT *tree, short obj);
	
short 	get_obtype	(OBJECT *tree, short obj, short *ud);
void 	get_objframe	(OBJECT *tree, short obj, GRECT *r);

void 	set_flag	(OBJECT *tree, short obj, short flag, short set);
short	get_flag	(OBJECT *tree, short obj, short flag);
short	find_flag	(OBJECT *tree, short flag);

void	set_state	(OBJECT *tree, short obj, short state, short set);
short	get_state	(OBJECT *tree, short obj, short state);
void	tree_state	(OBJECT *tree, short start_obj, short state, short set);

void	set_string	(OBJECT *tree, short obj, char *text);
void 	get_string	(OBJECT *tree, short obj, char *text);

void 	set_short	(OBJECT *tree, short obj, short i);
short  	get_short	(OBJECT *tree, short obj);

void 	set_long	(OBJECT *tree, short obj, long l);
void 	set_ulong	(OBJECT *tree, short obj, unsigned long l);
long 	get_long	(OBJECT *tree, short obj);

void 	redraw_obj	(OBJECT *tree, short obj);

/*******************************************************************************
 * popup functions
 *******************************************************************************/
 
short	create_popup	(POPUP *p, short anz, short maxlen, char *item);
short	free_popup	(POPUP *p);
short	append_popup	(POPUP *p, char *item);

short	do_popup	(POPUP *p, short button);
short	cf_menu_popup	(MENU *m1, short x, short y, MENU *m2, short button, short offset);

#define POP_OPEN	1
#define POP_CYCLE	2
short	handle_popup	(OBJECT *dial, short dial_obj, OBJECT *pop, short pop_obj, short mode);

/*******************************************************************************
 * scrap functions
 *******************************************************************************/

int	get_scrapdir	(char *scrap);
void	scrap_clear	(void);
char *	scrap_rtxt	(char *buf, long *len, long maxlen);
void	scrap_wtxt	(char *buf);

/*******************************************************************************
 * userdef functions
 *******************************************************************************/

void	fix_dial	(OBJECT *tree);
void	fix_menu	(OBJECT *tree);
void	fix_popup	(OBJECT *tree, short thin_line);

/*******************************************************************************
 * vdi functions
 *******************************************************************************/

short	open_vwork	(short *w_out);
void	set_clipping	(short handle, short x, short y, short w, short h, short on);
short 	height2pts	(short handle, short f_id, short f_height);

/*******************************************************************************
 * wdial functions
 *******************************************************************************/

/* wd->mode */
#define WD_OPEN   1
#define WD_ICON   2
#define WD_SHADE  4

#define WD_CLOSER	0xFF

WDIALOG	*create_wdial	(OBJECT *tree, OBJECT *icon, short edit_obj,
			 WDIAL_OCB open_cb, WDIAL_XCB exit_cb);
WDIALOG	*create_wdial_kind (OBJECT *tree, OBJECT *icon, short edit_obj,
			 WDIAL_OCB open_cb, WDIAL_XCB exit_cb, short win_kind);
void	delete_wdial	(WDIALOG *wd);
void	open_wdial	(WDIALOG *wd, short pos_x, short pos_y);
void	close_wdial	(WDIALOG *wd);

void	redraw_wdobj	(WDIALOG *wd, short obj);
void	redraw_wdicon	(WDIALOG *wd, short obj);
void	change_wdedit	(WDIALOG *wd, short new);

short	message_wdial	(short *msg);
short	click_wdial	(short clicks, short x, short y, short kshift, short mbutton);
short	key_wdial	(short kreturn, short kstate);

/*******************************************************************************
 * end
 *******************************************************************************/

#endif /* _cflib_h_ */

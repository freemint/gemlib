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

#ifdef __MINT__			/* MiNT/GEM-Lib */
#include <osbind.h>
#include <mintbind.h>
#include <gem.h>
#else				/* PureLIB/MT_AES */
#include <tos.h>
#include <mt_aes.h>
#include <vdi.h>
#endif


/*******************************************************************************
 * Version
 *******************************************************************************/

#ifdef __MINT__
#define CFLIB_PATCHLEVEL	"12m"
#else
#define CFLIB_PATCHLEVEL	"12p"
#endif
extern char __Ident_cflib[];

/*******************************************************************************
 * spezielle Typen der CF-Lib
 *******************************************************************************/

typedef enum
{
	null, Con, TCon, Datei, Terminal,
	Modem1, Modem2, Seriell1, Seriell2, Prn
} DEBUGDEV;

typedef struct _popup POPUP;
struct _popup
{
	OBJECT	*tree;			/* der Objektbaum */
	int	max_item;		/* maximal m”gliche Anzahl */
	int	akt_item;		/* aktuelle Anzahl */
	int	item_len;		/* L„nge eines Eintrages */
};

typedef int (*KEY_CB)(OBJECT *tree, int edit_obj, int kstate, int *kreturn, int *next_obj);


typedef struct _mdial MDIAL;
struct _mdial
{
	OBJECT	*tree;
	int	win_handle;
	char	*win_name;
	int	edit_obj,
		edit_idx,
		next_obj;
	int	save_frame, 
		delta_y;
	int	is_shaded;
	MDIAL	*next;
};

typedef void (*MDIAL_WCB)(int *msg);


typedef struct _wdial WDIALOG;
struct _wdial
{
	WDIALOG	*next;

	OBJECT	*tree;			/* Objektbaum */
	OBJECT	*icon;			/* Icon fr Iconify */
	int	mode;			/* aktueller Status */
	int	win_handle;		/* Fensterhandle */
	char	win_name[80];		/* Fenstertitel */
	int	win_kind;		/* Elemente */
	GRECT	work;			/* Fenstergr”že */
	int	title_obj;		/* Objektnummer des Titelobjektes */
	int	cancel_obj;		/*       "      des Abbruchbuttons */
	int	delta_y;		/* Offset bis zum Titelobjekt */
	int	edit_idx,		/* Objektnummern fr die Editfelder */
		next_obj,
		edit_obj;

	void	(*open_cb) (struct _wdial *dial);	
	int	(*exit_cb) (struct _wdial *dial, int exit_obj);	
};

typedef void 	(*WDIAL_OCB)(WDIALOG *dial);
typedef int	(*WDIAL_XCB)(WDIALOG *dial, int exit_obj);

#define WOCB_NULL	(WDIAL_OCB)NULL
#define WXCB_NULL	(WDIAL_XCB)NULL

typedef int (*FSEL_CB)(char *path, char *name);
#define FSCB_NULL	(FSEL_CB)NULL

/*******************************************************************************
 * globals.c
 *******************************************************************************/

extern int	gl_apid, gl_phys_handle;
extern GRECT	gl_desk;	

extern int	sys_big_id, sys_big_height, sys_big_pts,
		sys_sml_id, sys_sml_height, sys_sml_pts,
		sys_wchar, sys_hchar, sys_wbox, sys_hbox;

extern int	gl_wchar, gl_hchar, gl_wbox, gl_hbox;

extern int	gl_gdos;
extern int	gl_planes;

extern int	gl_gem;
extern int	gl_mint;
extern int	gl_naes;
extern int	gl_magx;
extern int	gl_nvdi;

extern char 	gl_appdir[];

/*******************************************************************************
 * alerts functions
 *******************************************************************************/

int	do_alert	(int def, int undo, char *str);
int	do_walert	(int def, int undo, char *str, char *win_title);

/*******************************************************************************
 * app functions
 *******************************************************************************/
 
void	init_app	(char *rsc);
void	exit_gem	(void);
void	exit_app	(int ret);
void	hide_mouse	(void);
int  	hide_mouse_if_needed (GRECT *rect);
void	show_mouse	(void);
int	appl_xgetinfo	(int type, int *out1, int *out2, int *out3, int *out4);

/*******************************************************************************
 * asciitable functions
 *******************************************************************************/

int 	ascii_table (int id, int pts);
void	set_asciitable_strings (char *title, char *button);

/*******************************************************************************
 * colorpop functions
 *******************************************************************************/

#define MAX_COLORPOP 10 /* Maximale Anzahl von Farb-Objekten in einem Programm */

int	init_colorpop	(int maxplanes);
void	exit_colorpop	(void);

void	fix_colorpopobj	(OBJECT *tree, int obj, int color);
void	set_popobjcolor	(OBJECT *tree, int obj, int color);
int	get_popobjcolor	(OBJECT *tree, int obj);

int	do_colorpop	(int x, int y, int item, int planes, int show_noncolor);
int	handle_colorpop	(OBJECT *dial, int dial_obj, int mode, int planes, int show_noncolor);

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

int select_file (char *path, char *name, char *mask, char *title, FSEL_CB open_cb);

/*******************************************************************************
 * fontsel functions
 *******************************************************************************/

#define FS_M_XFSL		1		/* Cookie xFSL */
#define FS_M_FPROT		2		/* Fontprotokoll */
#define FS_M_MAGX		4		/* MagiC fnts_* */
#define FS_M_ALL		(FS_M_XFSL|FS_M_FPROT|FS_M_MAGX)

#define FS_F_MONO		8		/* nur monospaced */

int do_fontsel (int flags, char *title, int *id, int *pts);

/*******************************************************************************
 * form_do functions
 *******************************************************************************/

int	cf_form_do (OBJECT *tree, int *ed_start);
int 	simple_dial (OBJECT *tree, int start_edit);
KEY_CB	set_formdo_keycb (KEY_CB keycb);

/*******************************************************************************
 * magx functions
 *******************************************************************************/
extern int	get_magx_version(void);

#define MX_NOTXOBJ		0		/* kein MagiC-Objekt */
#define MX_UNDERLINE		1		/* String als šberschrift */
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

int	get_magx_obj (OBJECT *tree, int obj);
int	get_magx_shortcut (OBJECT *tree, int obj, char *c);

/*******************************************************************************
 * mdial functions
 *******************************************************************************/

MDIAL *	open_mdial	(OBJECT *tree, int edit_start);
void	close_mdial	(MDIAL *mdial);
int	do_mdial	(MDIAL *mdial);

int 	simple_mdial	(OBJECT *tree, int edit_start);

void 	set_mdial_wincb(MDIAL_WCB cb);

void	redraw_mdobj	(MDIAL *mdial, int obj);
void 	change_mdedit	(MDIAL *mdial, int new);

/*******************************************************************************
 * menu functions
 *******************************************************************************/

int	create_menu (OBJECT *tree);
void 	delete_menu (void);

void 	disable_menu (void);
void 	enable_menu (void);

int	is_menu_key (int kreturn, int kstate, int *title, int *item);

/*******************************************************************************
 * misc functions
 *******************************************************************************/

long	ts2ol (short i1, short i2);
void 	ol2ts (long l, short *i1, short *i2);

void 	save_background (GRECT *box, MFDB *buffer);
void 	restore_background (GRECT *box, MFDB *buffer);

void *	malloc_global (long size);

int	get_patchlev (char *id_str, char *pl);
 
#ifndef _GEMLIB_H_
int *	grect_to_array (GRECT *g, int *pxy);
void 	array_to_grect (int *pxy, GRECT *g);
#endif

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

int		nkc_init	(void);
unsigned short	nkc_tos2n	(long toskey);
long		nkc_n2tos	(unsigned short nkcode);
unsigned char	nkc_toupper	(unsigned char chr);
unsigned char	nkc_tolower	(unsigned char chr);

unsigned short	gem_to_norm	(int ks, int kr);
void 		norm_to_gem	(unsigned int norm, int *ks, int *kr);

void 		str_toupper	(char *str);
void 		str_tolower	(char *str);

/*******************************************************************************
 * objc functions
 *******************************************************************************/

void 	set_obspec	(OBJECT *tree, int obj, long spec);
long 	get_obspec	(OBJECT *tree, int obj);
	
int 	get_obtype	(OBJECT *tree, int obj, short *ud);
void 	get_objframe	(OBJECT *tree, int obj, GRECT *r);

void 	set_flag	(OBJECT *tree, int obj, int flag, int set);
int	get_flag	(OBJECT *tree, int obj, int flag);
int	find_flag	(OBJECT *tree, int flag);

void	set_state	(OBJECT *tree, int obj, int state, int set);
int	get_state	(OBJECT *tree, int obj, int state);
void	tree_state	(OBJECT *tree, int start_obj, int state, int set);

void	set_string	(OBJECT *tree, int obj, char *text);
void 	get_string	(OBJECT *tree, int obj, char *text);

void 	set_int		(OBJECT *tree, int obj, int i);
int  	get_int		(OBJECT *tree, int obj);

void 	set_long	(OBJECT *tree, int obj, long l);
void 	set_ulong	(OBJECT *tree, int obj, unsigned long l);
long 	get_long	(OBJECT *tree, int obj);

void 	redraw_obj	(OBJECT *tree, int obj);

/*******************************************************************************
 * popup functions
 *******************************************************************************/
 
int	create_popup	(POPUP *p, int anz, int maxlen, char *item);
int	free_popup	(POPUP *p);
int	append_popup	(POPUP *p, char *item);

int	do_popup	(POPUP *p, int button);
int	cf_menu_popup	(MENU *m1, int x, int y, MENU *m2, int button, int offset);

#define POP_OPEN	1
#define POP_CYCLE	2
int	handle_popup	(OBJECT *dial, int dial_obj, OBJECT *pop, int pop_obj, int mode);

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
void	fix_popup	(OBJECT *tree, int thin_line);

/*******************************************************************************
 * vdi functions
 *******************************************************************************/

int	open_vwork	(int *w_out);
void	set_clipping	(int handle, int x, int y, int w, int h, int on);
int 	height2pts	(int handle, int f_id, int f_height);

/*******************************************************************************
 * wdial functions
 *******************************************************************************/

/* wd->mode */
#define WD_OPEN   1
#define WD_ICON   2
#define WD_SHADE  4

#define WD_CLOSER	0xFF

WDIALOG	*create_wdial	(OBJECT *tree, OBJECT *icon, int edit_obj,
			 WDIAL_OCB open_cb, WDIAL_XCB exit_cb);
void	delete_wdial	(WDIALOG *wd);
void	open_wdial	(WDIALOG *wd, int pos_x, int pos_y);
void	close_wdial	(WDIALOG *wd);

void	redraw_wdobj	(WDIALOG *wd, int obj);
void	redraw_wdicon	(WDIALOG *wd, int obj);
void	change_wdedit	(WDIALOG *wd, int new);

int	message_wdial	(int *msg);
int	click_wdial	(int clicks, int x, int y, int kshift, int mbutton);
int	key_wdial	(int kreturn, int kstate);

/*******************************************************************************
 * end
 *******************************************************************************/

#endif /* _cflib_h_ */

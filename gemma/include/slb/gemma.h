/* tab 8 */

# ifndef GEMMA_GEMMA_H
# define GEMMA_GEMMA_H

# include <mt_gem.h>
# include <mint/slb.h>
# include <slb/gemma-struct.h>

extern SLB gemma;
extern SLB kern;

/* SLB bindings for libgemma.a */

extern long _startup(void);
extern short call_aes(GEM_ARRAY *gem, short fn);
extern GEM_ARRAY *gem_control(void);
extern long appl_open(char *file, short thread, char *pname);
extern long appl_close(void);

/* SLB macros */

# ifdef __GNUC__

static inline
long appl_top(void)
{
	return (gemma.exec)(gemma.handle, (long)AP_TOP, (short)0);
}

static inline
long rsrc_xload(char *file)
{
	return (gemma.exec)(gemma.handle, (long)RSRC_XLOAD, (short)1, file);
}

static inline
long rsrc_xalloc(void)
{
	return (gemma.exec)(gemma.handle, (long)RSRC_XALLOC, (short)0);
}

static inline
long rsrc_xfree(void)
{
	return (gemma.exec)(gemma.handle, (long)RSRC_XFREE, (short)0);
}

static inline
long rsrc_xgaddr(short type, short obj)
{
	return (gemma.exec)(gemma.handle, (long)RSRC_XGADDR, (short)2, type, obj);
}

static inline
char *env_get(const char *var)
{
	return (char *)(gemma.exec)(gemma.handle, (long)ENV_GET, (short)1, var);
}

static inline
char *env_eval(const char *var)
{
	return (char *)(gemma.exec)(gemma.handle, (long)ENV_EVAL, (short)1, var);
}

static inline
long env_getargc(void)
{
	return (gemma.exec)(gemma.handle, (long)ENV_GETARGC, (short)0);
}

static inline
char *env_getargv(long argc)
{
	return (char *)(gemma.exec)(gemma.handle, (long)ENV_GETARGV, (short)1, argc);
}

static inline
long windial_size(void)
{
	return (gemma.exec)(gemma.handle, (long)WD_FIELD, (short)0);
}

static inline
WINDIAL *windial_create(WINDIAL *wd, short box, short icon, short ftext, char *title)
{
	return (WINDIAL *)(gemma.exec)(gemma.handle, (long)WD_CREATE, (short)5, wd, box, icon, ftext, title);
}

static inline
WINDIAL *windial_xcreate(WINDIAL *wd, short box, short icon, short ftext, char *title, short gadgets)
{
	return (WINDIAL *)(gemma.exec)(gemma.handle, (long)WD_CREATE, (short)6, wd, box, icon, ftext, title, gadgets);
}

static inline
long windial_open(WINDIAL *wd)
{
	return (gemma.exec)(gemma.handle, (long)WD_OPEN, (short)1, wd);
}

static inline
long windial_formdo(WINDIAL *wd)
{
	return (gemma.exec)(gemma.handle, (long)WD_FORMDO, (short)1, wd);
}

static inline
long windial_close(WINDIAL *wd)
{
	return (gemma.exec)(gemma.handle, (long)WD_CLOSE, (short)1, wd);
}

static inline
long windial_delete(WINDIAL *wd)
{
	return (gemma.exec)(gemma.handle, (long)WD_DELETE, (short)1, wd);
}

static inline
long windial_center(WINDIAL *wd)
{
	return (gemma.exec)(gemma.handle, (long)WD_CENTER, (short)1, wd);
}

static inline
long windial_link(WINDIAL *from, WINDIAL *to)
{
	return (gemma.exec)(gemma.handle, (long)WD_LINK, (short)2, from, to);
}

static inline
long windial_unlink(WINDIAL *wd)
{
	return (gemma.exec)(gemma.handle, (long)WD_UNLINK, (short)1, wd);
}

# if 0
static inline void windial_longjmp(WINDIAL *wd, short vec)  __attribute__((__noreturn__));
# endif

static inline
void windial_longjmp(WINDIAL *wd, short vec)
{
	(gemma.exec)(gemma.handle, (long)WD_RETURN, (short)2, wd, vec);
}

static inline
long windial_setjmp(WINDIAL *wd, short vec, void *adr)
{
	return (gemma.exec)(gemma.handle, (long)WD_HANDLER, (short)4, wd, vec, adr);
}

static inline
long windial_alert(short button, char *str)
{
	return (gemma.exec)(gemma.handle, (long)WD_ALERT, (short)2, button, str);
}

static inline
void windial_error(long error, char *msg)
{
	(gemma.exec)(gemma.handle, (long)WD_ERROR, (short)2, error, msg);
}

static inline
long thread_fork(void *addr, char *ptitle, long stack, long mode)
{
	return (gemma.exec)(gemma.handle, (long)TFORK, (short)5, _startup, addr, ptitle, stack, mode);
}

static inline
long thread_overlay(void *addr, char *ptitle, long stack, long mode)
{
	return (gemma.exec)(gemma.handle, (long)TOVL, (short)5, _startup, addr, ptitle, stack, mode);
}

static inline
void objc_xdraw(WINDIAL *wd, short obj)
{
	(gemma.exec)(gemma.handle, (long)OB_XDRAW, (short)2, wd, obj);
}

static inline
long av_dir_update(short drive)
{
	return (gemma.exec)(gemma.handle, (long)AV_DIR_UPD, (short)1, drive);
}

static inline
long av_view(char *pathname)
{
	return (gemma.exec)(gemma.handle, (long)AV_XVIEW, (short)1, pathname);
}

static inline
long av_help(char *fname)
{
	return (gemma.exec)(gemma.handle, (long)AV_HELP, (short)1, fname);
}

static inline
long open_url(char *url)
{
	return (gemma.exec)(gemma.handle, (long)NET_URL, (short)1, url);
}

static inline
short rc_intersect(const GRECT *src, GRECT *dest)
{
	return (gemma.exec)(gemma.handle, (long)RC_INTERSECT, (short)2, src, dest);
}

static inline
long objc_xchange(WINDIAL *wd, short obj, short newst, short redraw)
{
	return (gemma.exec)(gemma.handle, (long)OB_XCHANGE, (short)4, wd, obj, newst, redraw);
}

static inline
void ftext_init(short tree, short obj)
{
	(gemma.exec)(gemma.handle, (long)FT_FIX, (short)2, tree, obj);
}

static inline
char *file_select(char *title, char *mask, short flag)
{
	return (char *)(gemma.exec)(gemma.handle, (long)FSELINPUT, (short)3, title, mask, flag);
}

static inline
long menu_xpop(WINDIAL *wd, short obj, MENU *menu)
{
	return (gemma.exec)(gemma.handle, (long)MN_XPOP, (short)3, wd, obj, menu);
}

static inline
long proc_exec(short mode, long flag, char *cmd, char *tail, char *env)
{
	return (gemma.exec)(gemma.handle, (long)PROC_EXEC, (short)5, mode, flag, cmd, tail, env);
}

static inline
char *get_version(void)
{
	return (char *)(gemma.exec)(gemma.handle, (long)GET_VERSION, (short)0);
}

static inline
long get_users(void)
{
	return (gemma.exec)(gemma.handle, (long)GET_USERS, (short)0);
}

# else

# define appl_top() (gemma.exec)(gemma.handle, (long)AP_TOP, (short)0)
# define rsrc_xload(file) (gemma.exec)(gemma.handle, (long)RSRC_XLOAD, (short)1, (char *)file)
# define rsrc_xalloc() (gemma.exec)(gemma.handle, (long)RSRC_XALLOC, (short)0)
# define rsrc_xfree() (gemma.exec)(gemma.handle, (long)RSRC_XFREE, (short)0)
# define rsrc_xgaddr(type, obj) (gemma.exec)(gemma.handle, (long)RSRC_XGADDR, (short)2, (short)type, (short)obj)
# define env_get(var) (char *)(gemma.exec)(gemma.handle, (long)ENV_GET, (short)1, (const char *)var)
# define env_eval(var) (char *)(gemma.exec)(gemma.handle, (long)ENV_EVAL, (short)1, (const char *)var)
# define env_getargc() (gemma.exec)(gemma.handle, (long)ENV_GETARGC, (short)0)
# define env_getargv(argc) (char *)(gemma.exec)(gemma.handle, (long)ENV_GETARGV, (short)1, (long)argc)
# define windial_size() (gemma.exec)(gemma.handle, (long)WD_FIELD, (short)0)
# define windial_create(wd, box, icon, ftext, title) (gemma.exec)(gemma.handle, (long)WD_CREATE, (short)5, (WINDIAL *)wd, (short)box, (short)icon, (short)ftext, (char *)title)
# define windial_xcreate(wd, box, icon, ftext, title, gadgets) (gemma.exec)(gemma.handle, (long)WD_CREATE, (short)6, (WINDIAL *)wd, (short)box, (short)icon, (short)ftext, (char *)title, (short)gadgets)
# define windial_open(wd) (gemma.exec)(gemma.handle, (long)WD_OPEN, (short)1, (WINDIAL *)wd)
# define windial_formdo(wd) (gemma.exec)(gemma.handle, (long)WD_FORMDO, (short)1, (WINDIAL *)wd)
# define windial_close(wd) (gemma.exec)(gemma.handle, (long)WD_CLOSE, (short)1, (WINDIAL *)wd)
# define windial_delete(wd) (gemma.exec)(gemma.handle, (long)WD_DELETE, (short)1, (WINDIAL *)wd)
# define windial_center(wd) (gemma.exec)(gemma.handle, (long)WD_CENTER, (short)1, (WINDIAL *)wd)
# define windial_link(from, to) (gemma.exec)(gemma.handle, (long)WD_LINK, (short)2, (WINDIAL *)from, (WINDIAL *)to)
# define windial_longjmp(wd, vec) (gemma.exec)(gemma.handle, (long)WD_RETURN, (short)2, (WINDIAL *)wd, (short)vec)
# define windial_unlink(wd) (gemma.exec)(gemma.handle, (long)WD_UNLINK, (short)1, (WINDIAL *)wd)
# define windial_setjmp(wd, vec, adr) (gemma.exec)(gemma.handle, (long)WD_HANDLER, (short)4, (WINDIAL *)wd, (short)vec, (void *)adr)
# define windial_alert(button, str) (gemma.exec)(gemma.handle, (long)WD_ALERT, (short)2, (short)button, (char *)str)
# define windial_error(error, msg) (gemma.exec)(gemma.handle, (long)WD_ERROR, (short)2, (long)error, (char *)msg)
# define thread_fork(addr, ptitle, stack, mode) (gemma.exec)(gemma.handle, (long)TFORK, (short)5, _startup, (void *)addr, (char *)ptitle, (long)stack, (long)mode)
# define objc_xdraw(wd, obj) (gemma.exec)(gemma.handle, (long)OB_XDRAW, (short)2, (WINDIAL *)wd, (short)obj)
# define thread_overlay(addr, ptitle, stack, mode) (gemma.exec)(gemma.handle, (long)TOVL, (short)5, _startup, (void *)addr, (char *)ptitle, (long)stack, (long)mode)
# define av_dir_update(drive) (gemma.exec)(gemma.handle, (long)AV_DIR_UPD, (short)1, (short)drive)
# define av_view(pathname) (gemma.exec)(gemma.handle, (long)AV_XVIEW, (short)1, (char *)pathname)
# define av_help(fname) (gemma.exec)(gemma.handle, (long)AV_HELP, (short)1, (char *)fname)
# define open_url(url) (gemma.exec)(gemma.handle, (long)NET_URL, (short)1, (char *)url)
# define rc_intersect(src,dest) (gemma.exec)(gemma.handle, (long)RC_INTERSECT, (short)2, (RECT *)src, (RECT *)dest)
# define objc_xchange(wd, obj, newst, redraw) (gemma.exec)(gemma.handle, (long)OB_XCHANGE, (short)4, (WINDIAL *)wd, (short)obj, (short)newst, (short)redraw)
# define ftext_init(tree, obj) (gemma.exec)(gemma.handle, (long)FT_FIX, (short)2, (short)tree, (short)obj)
# define file_select(title, mask, flag) (char *)(gemma.exec)(gemma.handle, (long)FSELINPUT, (short)3, (char *)title, (char *)mask, (short)flag)
# define menu_xpop(wd, obj, menu) (gemma.exec)(gemma.handle, (long)MN_XPOP, (short)3, (WINDIAL *)wd, (short)obj, (MENU *)menu)
# define proc_exec(mode, flag, cmd, tail, env) (gemma.exec)(gemma.handle, (long)PROC_EXEC, (short)5, (short)mode, (long)flag, (char *)cmd, (char *)tail, (char *)env)
# define get_version() (gemma.exec)(gemma.handle, (long)GET_VERSION, (short)0)
# define get_users() (gemma.exec)(gemma.handle, (long)GET_USERS, (short)0)

# endif /* __GNUC__ */

/* AES bindings for libgemma.a */

extern long appl_control(short ap_cid, short ap_cwhat, void *ap_cout);
extern long appl_exit(void);
extern long appl_find(char *name);
extern long appl_getinfo(short cwhat, short *out1, short *out2, short *out3, short *out4);
extern long appl_init(void);
extern long appl_read(short ApId, short Length, void *ApPbuff);
extern long appl_search(short mode, char *fname, short *type, short *ap_id);
extern long appl_tplay(void *Mem, short Num, short Scale);
extern long appl_trecord(void *Mem, short Count);
extern long appl_write(short ApId, short Length, void *ApPbuff);
extern long appl_yield(void);
extern long appl_bvset(short flo, short hard);

extern long evnt_button(short Clicks, short WhichButton, short WhichState, short *Mx, short *My, short *ButtonState, short *KeyState);
extern long evnt_dclick(short ToSet, short SetGet);
extern long evnt_keybd(void);
extern long evnt_mesag(short MesagBuf[]);
extern long evnt_mouse(short EnterExit, short InX, short InY, short InW, short InH, short *OutX, short *OutY, short *ButtonState, short *KeyState);
extern long evnt_multi(short Type, short Clicks, short WhichButton, short WhichState,
			short EnterExit1, short In1X, short In1Y, short In1W, short In1H,
			short EnterExit2, short In2X, short In2Y, short In2W, short In2H,
			short MesagBuf[], unsigned long Interval, short *OutX, short *OutY,
			short *ButtonState, short *KeyState, short *Key, short *ReturnCount);
extern long evnt_timer(unsigned long msec);

extern long form_alert(short DefButton, char *Str);
extern long form_button(void *Btree, short Bobject, short Bclicks, short *Bnxtobj);
extern long form_center(void *Tree, short *Cx, short *Cy, short *Cw, short *Ch);
extern long form_dial(short Flag, short Sx, short Sy, short Sw, short Sh, short Bx, short By, short Bw, short Bh);
extern long form_do(void *Tree, short StartObj);
extern long form_error(short ErrorCode);
extern long form_keybd(void *Ktree, short Kobject, short Kobnext, short Kchar, short *Knxtobject, short *Knxtchar);
extern long form_popup(void *tree, short x, short y);

extern long fsel_exinput(char *Path, char *File, short *ExitButton, char *title);
extern long fsel_input(char *Path, char *File, short *ExitButton);

extern long graf_dragbox(short Sw, short Sh, short Sx, short Sy, short Bx, short By, short Bw, short Bh, short *Fw, short *Fh);
extern long graf_growbox(short Sx, short Sy, short Sw, short Sh, short Fx, short Fy, short Fw, short Fh);
extern long graf_handle(short *Wchar, short *Hchar, short *Wbox, short *Hbox);
extern long graf_movebox(short Sw, short Sh, short Sx, short Sy, short Dx, short Dy);
extern long graf_mkstate(short *Mx, short *My, short *ButtonState, short *KeyState);
extern long graf_mouse(short Form, void *FormAddress);
extern long graf_multirubber(short x, short y, short minw, short minh, GRECT *rec, short *outw, short *outh);
extern long graf_rubberbox(short Ix, short Iy, short Iw, short Ih, short *Fw, short *Fh);
extern long graf_shrinkbox(short Fx, short Fy, short Fw, short Fh, short Sx, short Sy, short Sw, short Sh);
extern long graf_slidebox(void *Tree, short Parent, short Object, short Direction);
extern long graf_watchbox(void *Tree, short Object, short InState, short OutState);

extern long menu_attach(short me_flag, OBJECT *me_tree, short me_item, MENU *me_mdata);
extern long menu_bar(void *Tree, short ShowFlag);
extern long menu_click(short click, short setit);
extern long menu_icheck(void *Tree, short Item, short CheckFlag);
extern long menu_ienable(void *Tree, short Item, short EnableFlag);
extern long menu_istart(short me_flag, OBJECT *me_tree, short me_imenu, short me_item);
extern long menu_popup(MENU *me_menu, short me_xpos, short me_ypos, MENU *me_mdata);
extern long menu_register(short ApId, char *MenuText);
extern long menu_settings(short me_flag, MN_SET *me_values);
extern long menu_text(void *Tree, short Item, char *Text);
extern long menu_tnormal(void *Tree, short Item, short NormalFlag);
extern long menu_unregister(short apid);

extern long objc_add(void *Tree, short Parent, short Child);
extern long objc_change(void *Tree, short Object, short Res, short Cx, short Cy, short Cw, short Ch, short NewState,short Redraw);
extern long objc_delete(void *Tree, short Object);
extern long objc_draw(void *tree, short obj, short depth, short wx, short wy, short ww, short wh);
extern long objc_edit(void *tree, short obj, short ch, short idx, short mode);
extern long objc_find(void *Tree, short Start, short Depth, short Mx, short My);
extern long objc_offset(void *tree, short obj, short *x, short *y);
extern long objc_order(void *Tree, short Object, short NewPos);
extern long objc_sysvar(short mode, short which, short in1, short in2, short *out1, short *out2);
extern long objc_xfind(void *tree, short start, short depth, short x, short y);

extern long rsrc_free(void);
extern long rsrc_gaddr(short Type, short Index, void **Address);
extern long rsrc_load(char *Name);
extern long rsrc_obfix(void *Tree, short Index);
extern long rsrc_rcfix(void *rc_header);
extern long rsrc_saddr(short Type, short Index, void *Address);

extern long scrp_read(char *Scrappath);
extern long scrp_write(char *Scrappath);
extern long scrp_clear(void);

extern long shel_envrn(char **result, char *param);
extern long shel_find(char *buf);
extern long shel_get(char *Buf, short Len);
extern long shel_help(short sh_hmode, char *sh_hfile, char *sh_hkey);
extern long shel_put(char *Buf, short Len);
extern long shel_rdef(char *lpcmd, char *lpdir);
extern long shel_read(char *Command, char *Tail);
extern long shel_wdef(char *lpcmd, char *lpdir);
extern long shel_write(short Exit, short Graphic, short Aes, void *Command, char *Tail);

extern long wind_calc(short Type, short Parts, short InX, short InY, short InW, short InH, short *OutX, short *OutY, short *OutW, short *OutH);
extern long wind_close(short WindowHandle);
extern long wind_create(short Parts, short Wx, short Wy, short Ww, short Wh);
extern long wind_delete(short WindowHandle);
extern long wind_draw(short handle, short startobj);
extern long wind_find(short X, short Y);
extern long wind_get(short WindowHandle, short What, short *W1, short *W2, short *W3, short *W4);
extern void wind_new(void);
extern long wind_open(short WindowHandle, short Wx, short Wy, short Ww, short Wh);
extern long wind_set(short WindowHandle, short What, short W1, short W2, short W3, short W4);
extern long wind_sget(short handle, short field, char *buf);
extern long wind_update(short Code);

# endif

/* EOF */

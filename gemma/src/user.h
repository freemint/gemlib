/* User function prototypes */

long appl_close(BASEPAGE *bp, long fn, short nargs, PROC_ARRAY *p);
long appl_open(BASEPAGE *bp, long fn, short nargs, char *name, short flag, char *desk, PROC_ARRAY *p);
long appl_top(BASEPAGE *bp, long fn, short nargs, PROC_ARRAY *p);
long gem_control(BASEPAGE *bp, long fn, short nargs);
long call_aes(BASEPAGE *bp, long fn, short nargs, PROC_ARRAY *p, short opcode);
long windial_size(BASEPAGE *bp, long fn, short nargs);
long windial_create(BASEPAGE *bp, long fn, short nargs, WINDIAL *wd, short obj, short icon, short field, char *title, short gadgets, PROC_ARRAY *p);
long windial_open(BASEPAGE *bp, long fn, short nargs, WINDIAL *wd, PROC_ARRAY *p);
long windial_close(BASEPAGE *bp, long fn, short nargs, WINDIAL *wd, PROC_ARRAY *p);
long windial_delete(BASEPAGE *bp, long fn, short nargs, WINDIAL *wd, PROC_ARRAY *p);
long windial_formdo(BASEPAGE *bp, long fn, short nargs, WINDIAL *wd, PROC_ARRAY *p);
long windial_center(BASEPAGE *bp, long fn, short nargs, WINDIAL *wd, PROC_ARRAY *p);
long windial_error(BASEPAGE *bp, long fn, short nargs, long error, char *msg, PROC_ARRAY *p);
long ftext_fix(BASEPAGE *bp, long fn, short nargs, short tree, short obj, PROC_ARRAY *p);
long rsrc_xgaddr(BASEPAGE *bp, long fn, short nargs, short type, short obj, PROC_ARRAY *p);
long rsrc_xload(BASEPAGE *bp, long fn, short nargs, char *name, PROC_ARRAY *p);
long rsrc_xalloc(BASEPAGE *bp, long fn, short nargs, PROC_ARRAY *p);
long rsrc_xfree(BASEPAGE *bp, long fn, short nargs, PROC_ARRAY *p);

/* EOF */


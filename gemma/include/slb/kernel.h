/* Prototypes for kernel.slb functions */

# ifndef _kernel_slb_h
# define _kernel_slb_h

# include <mint/basepage.h>
# include <mint/slb.h>

extern SLB kern;

static inline void
dos_pterm0(void)
{
	(kern.exec)(kern.handle, 0L, 0);
}

static inline long
dos_fopen(const char *name, short mode)
{
	return (kern.exec)(kern.handle, 0x003dL, 2, (long)name, mode);
}

static inline long
dos_fread(short handle, long size, void *buf)
{
	return (kern.exec)(kern.handle, 0x003fL, 3, handle, size, buf);
}

static inline long
dos_fclose(short handle)
{
	return (kern.exec)(kern.handle, 0x003eL, 1, handle);
}

static inline long
dos_pkill(short pid, short sig)
{
	return (kern.exec)(kern.handle, 0x0111L, 2, pid, sig);
}

static inline char *
dos_serror(long error)
{
	return (char *)(kern.exec)(kern.handle, 0x0200L, 1, error);
}

static inline long
dos_fsize(const char *fname)
{
	return (kern.exec)(kern.handle, 0x0201L, 1, fname);
}

static inline long
dos_fexists(const char *fname)
{
	return (kern.exec)(kern.handle, 0x0202L, 1, fname);
}

static inline long
dos_fsearch(const char *name, char *fullname, const char *pathvar)
{
	return (kern.exec)(kern.handle, 0x0203L, 3, name, fullname, pathvar);
}

static inline BASEPAGE *
dos_pbase(void)
{
	return (BASEPAGE *)(kern.exec)(kern.handle, 0x0204L, 0);
}

static inline long
dos_fload(const char *fname, char **buf, long *size, short *mode)
{
	return (kern.exec)(kern.handle, 0x0205L, 4, fname, buf, size, mode);
}

static inline long
dos_fsave(const char *fname, void *buf, long size, short mode)
{
	return (kern.exec)(kern.handle, 0x0206L, 4, fname, buf, size, mode);
}

static inline long
dos_finfdir(char *buf, long blen)
{
	return (kern.exec)(kern.handle, 0x0207L, 2, buf, blen);
}

static inline char *
dos_getenv(const char *var)
{
	return (char *)(kern.exec)(kern.handle, 0x0208L, 1, var);
}

static inline void
dos_setenv(const char *var, const char *value)
{
	(kern.exec)(kern.handle, 0x0209L, 2, var, value);
}

static inline void
dos_delenv(const char *var)
{
	(kern.exec)(kern.handle, 0x020aL, 1, var);
}

static inline long
dos_floadbuf(const char *fname, char *buf, long size, short *mode)
{
	return (kern.exec)(kern.handle, 0x020bL, 4, fname, buf, size, mode);
}

# endif

/* EOF */
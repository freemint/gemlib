/*
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 * 
 * This file is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see
 * <http://www.gnu.org/licenses/>. 
 *
 */

#include "kernel32.h"
#include <sys/stat.h>

#ifndef EEOF
#define EEOF	__KERNEL_NEG(230)
#endif

void add_driveu(const char *name, char *buf)
{
	if (name[1] != ':' && (name[0] == '\\' || name[0] == '/'))
	{
		strcpy(buf, "u:");
		strcat(buf, name);
	} else
	{
		strcpy(buf, name);
	}
}


static char *bp_getenv(BASEPAGE *bp, const char *var)
{
	char *env = bp->p_env;
	size_t len = strlen(var);

	do {
		if (strncmp(env, var, len) == 0)
			return env + len;
		while (*env++ != '\0')
		{
			/* nothing */
		}
	} while (*env != '\0');
	return NULL;
}


static size_t env_strlen(const char *str)
{
	size_t len = 0;

	while (str && *str)
	{
		do
		{
			++str;
			++len;
		} while (*str);
		++str;
		++len;
	}
	++len;
	return len;
}


long dos_fsize(BASEPAGE *bp, long fn, short nargs, const char *fname)
{
	char namebuf[PATH_MAX];
	struct stat st;
	struct xattr xattr;
	_DTA *olddta;
	_DTA dta;
	long ret;

	UNUSED(bp);
	UNUSED(fn);
	UNUSED(nargs);
	add_driveu(fname, namebuf);
	if (Fstat64(0, namebuf, &st) == 0)
		return st.st_size;
	if (Fxattr(0, namebuf, &xattr) == 0)
		return xattr.st_size;
	olddta = Fgetdta();
	Fsetdta(&dta);
	ret = Fsfirst(namebuf, 0);
	Fsetdta(olddta);
	if (ret == 0)
		return dta.dta_size;
	return ret;
}


long dos_fexists(BASEPAGE *bp, long fn, short nargs, const char *fname)
{
	if (nargs <= 0)
		return -EINVAL;
	return dos_fsize(bp, fn, (short)SLB_NARGS(1), fname) < 0 ? -ESRCH : 0;
}


long dos_fsearch(BASEPAGE *bp, long fn, short nargs, const char *name, char *fullname, const char *pathvar)
{
	const char *path;
	char *end;
	
	UNUSED(fn);
	if (nargs <= 1)
		return -EBADARG;
	path = bp_getenv(bp, nargs == 2 || (nargs >= 2 && pathvar == NULL) ? "PATH=" : pathvar);
	if (path == NULL)
		return -ESRCH;
	while (*path != '\0')
	{
		end = fullname;
		while (*path != '\0' && *path != ',' && *path != ';')
			*end++ = *path++;
		*end = '\0';
		if (*path != '\0')
			path++;
		strcat(fullname, "/");
		strcat(fullname, name);
		if (dos_fexists(bp, 0, (short)SLB_NARGS(1), fullname) == 0)
			return 0;
	}
	return -ESRCH;
}


BASEPAGE *dos_pbase(BASEPAGE *bp, long fn, short nargs)
{
	UNUSED(fn);
	UNUSED(nargs);
	return bp;
}


long dos_fload(BASEPAGE *bp, long fn, short nargs, const char *fname, char **buf, long *size, short *mode)
{
	long fsize;
	struct xattr xattr;
	long ret;
	long handle;
	char *bufp;
	
	UNUSED(fn);
	UNUSED(nargs);
	if ((fsize = dos_fsize(bp, 513, (short)SLB_NARGS(1), fname)) < 0)
		return fsize;
	if (fsize == 0)
		return -EEOF;
	*size = fsize;
	if (Fxattr(0, fname, &xattr) == 0)
	{
		*mode = xattr.st_mode;
	}
	if ((ret = dos_mxalloc(bp, 0x44, (short)SLB_NARGS(2), fsize, MX_PREFTTRAM|MX_PRIVATE)) < 0)
		return ret;
	bufp = (char *)ret;
	*buf = bufp;
	if ((ret = dos_fopen(bp, 0x3d, (short)SLB_NARGS(2), fname, FO_READ)) >= 0)
	{
		handle = ret;
		ret = dos_fread(bp, 0x3f, (short)SLB_NARGS(3), handle, fsize, bufp);
		dos_fclose(bp, 0x3e, (short)SLB_NARGS(1), handle);
		if (ret >= 0 && ret != fsize)
			ret = -EREAD;
	}
	if (ret < 0)
	{
		dos_mfree(bp, 0x49, (short)SLB_NARGS(1), bufp);
		*buf = NULL;
		return ret;
	}
	return 0;
}


long dos_fsave(BASEPAGE *bp, long fn, short nargs, const char *fname, const void *buf, long size, short mode)
{
	char namebuf[PATH_MAX];
	long ret;
	long handle;
	
	UNUSED(nargs);
	
	strcpy(namebuf, fname);
	strcat(namebuf, ".orig");
	dos_fdelete(bp, fn, (short)SLB_NARGS(1), namebuf);
	ret = dos_frename(bp, fn, (short)SLB_NARGS(2), fname, namebuf);
	if (ret < 0)
		return ret;
	handle = dos_fcreate(bp, fn, (short)SLB_NARGS(2), fname, 0);
	if (handle < 0)
		return handle;
	ret = dos_fwrite(bp, fn, (short)SLB_NARGS(3), handle, size, buf);
	dos_fclose(bp, fn, (short)SLB_NARGS(1), handle);
	if (ret < 0)
		return ret;
	if (ret != size)
		return -EWRITE;
	Fchmod(fname, mode & ALLPERMS);
	return 0;
}


long dos_floadbuf(BASEPAGE *bp, long fn, short nargs, const char *fname, char *buf, long size, short *mode)
{
	long fsize;
	struct xattr xattr;
	long ret;
	long handle;

	UNUSED(fn);
	UNUSED(nargs);

	fsize = dos_fsize(bp, 513, (short)SLB_NARGS(1), fname);
#if 0
	if (fsize < 0)
		return fsize;
#endif
	if (fsize > size)
		return -ESRCH;
	if (Fxattr(0, fname, &xattr) == 0)
	{
		*mode = xattr.st_mode;
	}
	if ((ret = dos_fopen(bp, 0x3d, (short)SLB_NARGS(2), fname, FO_READ)) >= 0)
	{
		handle = ret;
		ret = dos_fread(bp, 0x3f, (short)SLB_NARGS(3), handle, fsize, buf);
		dos_fclose(bp, 0x3e, (short)SLB_NARGS(1), handle);
		if (ret >= 0 && ret != fsize)
			ret = -EREAD;
	}
	if (ret < 0)
		return ret;
	return 0;
}


long dos_finfdir(BASEPAGE *bp, long fn, short nargs, char *buf, long blen)
{
	const char *home;
	const char *orighome;
	long ret;

	UNUSED(fn);
	UNUSED(blen);
	if (nargs <= 1)
		return -EINVAL;
	home = orighome = bp_getenv(bp, "HOME=");
	if (home == NULL)
		home = ".";
	strcpy(buf, home);
	strcat(buf, "\\defaults");
	if (dos_fexists(bp, 514, (short)SLB_NARGS(1), buf) == 0)
	{
		strcat(buf, "\\");
		return 0;
	}
	strcpy(buf, home);
	ret = orighome != NULL ? dos_fexists(bp, 514, (short)SLB_NARGS(1), buf) : 0;
	if (ret == 0)
	{
		if (orighome != NULL)
			strcat(buf, "\\");
		return 0;
	}
	strcpy(buf, ".\\");
	return 0;
}


char *dos_getenv(BASEPAGE *bp, long fn, short nargs, const char *var)
{
	UNUSED(fn);
	if (nargs <= 0 || var == NULL)
		return NULL;
	return bp_getenv(bp, var);
}


long dos_setenv(BASEPAGE *bp, long fn, short nargs, const char *var, const char *value)
{
	size_t envlen;
	char *env, *newenv;
	const char *oldvalue;
	char *end;

	UNUSED(fn);
	if (nargs <= 1 || var == NULL)
		return -EBADARG;
	if (value == NULL)
		return dos_delenv(bp, fn, (short)SLB_NARGS(1), var);
	env = bp->p_env;
	envlen = env_strlen(env);
	envlen += strlen(value) + 2;
	if ((oldvalue = bp_getenv(bp, var)) != NULL)
	{
		envlen -= strlen(oldvalue);
	} else
	{
		envlen += strlen(var);
	}
	newenv = (char *)dos_mxalloc(bp, 0x44, (short)SLB_NARGS(2), envlen, MX_PREFTTRAM);
	if (newenv == NULL)
		return 0;
	dos_delenv(bp, fn, (short)SLB_NARGS(1), var);
	end = newenv;
	if (*env != '\0')
	{
		while (*env)
		{
			while ((*end++ = *env++) != '\0')
				;
		}
	}
	strcpy(end, var);
	strcat(end, "=");
	strcat(end, value);
	end[strlen(end) + 1] = '\0';
	dos_mfree(bp, 0x49, (short)SLB_NARGS(1), bp->p_env);
	bp->p_env = newenv;

	return 0;
}


long dos_delenv(BASEPAGE *bp, long fn, short nargs, const char *var)
{
	char *value;
	char *next;

	UNUSED(fn);
	if (nargs <= 0)
		return -EBADARG;
	value = bp_getenv(bp, var);
	if (value == NULL)
		return 0;
	value -= strlen(var);
	next = value + strlen(value) + 1;
	while (*next)
	{
		while ((*value++ = *next++) != '\0')
			;
	}
	*value = '\0';
	return dos_mshrink(bp, 0x4a, (short)SLB_NARGS(2), bp->p_env, env_strlen(bp->p_env));
}

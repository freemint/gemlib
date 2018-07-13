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

long dos_pterm0(BASEPAGE *bp, long fn, short nargs)
{
	UNUSED(bp);
	UNUSED(fn);
	UNUSED(nargs);
	Pterm(0);
	return 0;
}


long dos_pterm(BASEPAGE *bp, long fn, short nargs, long retcode)
{
	UNUSED(bp);
	UNUSED(fn);
	if ((short) nargs <= 0)
		retcode = 0;
	Pterm(retcode);
	return 0;
}


/*
 * Simplified version of dos_pexec.
 * Does not handle ARGV argument passing, or hashbang scripts
 */
long dos_pexec(BASEPAGE *bp, long fn, short nargs, short mode, const char *ptr1, const char *ptr2, const void *ptr3)
{
	short mkname = 0;
	char *name;
	char namebuf[PATH_MAX];
	char pathbuf[PATH_MAX];
	char tail[128];
	
	size_t i, len;
	
	UNUSED(fn);
	if (nargs <= 3)
		return -EINVAL;

	if (mode != 5 && mode != 7)
	{
		if (mode < 5)
		{
			if (mode != 0 && mode != 3)
				goto do_exec; /* mode 4: just go */
		} else
		{
			if (mode != 100)
			{
				if (mode < 100)
				{
					if (mode != 7)
						goto do_exec; /* mode 6: just go */
				}
				if (mode != 200)
					goto do_exec;
			}
		}
		mkname = 1;
	}

	if (mkname)
	{
		strncpy(namebuf, ptr1, sizeof(namebuf));
		name = namebuf;
		for (i = 0; i < sizeof(namebuf); i++)
		{
			if (name[i] == '\\')
				name[i] = '/';
			if (name[i] == '\0')
				break;
		}
		
		ptr1 = name;
		if (strchr(name, '/') == NULL)
		{
			if (dos_fexists(bp, 514, (short)SLB_NARGS(1), name) < 0)
			{
				if (dos_fsearch(bp, 515, (short)SLB_NARGS(3), name, pathbuf, NULL) == 0)
					ptr1 = pathbuf;
			}
		}
	}

	if (ptr2 && *ptr2)
	{
		len = strlen(ptr2);
		if (len > 126)
			return -EBADARG;
		strncpy(tail + 1, ptr2, sizeof(tail) - 1);
		tail[0] = (char)len;
	} else
	{
		tail[0] = tail[1] = '\0';
	}
	ptr2 = tail;
	
do_exec:
	return Pexec(mode, ptr1, ptr2, ptr3);
}


#if 0

/*
 * Original version of dos_pexec, reconstructed from disassembly.
 * I got lost by all the strange optimizations gcc does,
 * so this way not even work.
 * Left in here only for reference.
 */

static size_t env_strlen(const char *str)
{
	size_t len = 0;
	size_t l;
	
	do
	{
		l = strlen(str) + 1;
		len += l;
		str += l;
	} while (*str);
	++len;
	return len;
}


static void add_env(char *env, const char *str)
{
	env += env_strlen(env) - 1;
	strcpy(env, str);
	env[strlen(env) + 1] = '\0';
}


/*                       8        12       16           22                24                28                32 */
long dos_pexec(BASEPAGE *bp, long fn, short nargs, short mode, const char *ptr1, const char *ptr2, const void *ptr3)
{
	const char *tail = ptr2;
	const void *newenv = ptr3; /* e6276 */
	short mkname = 0;
	void *e6280 = (void *)-1;
	void *envptr = (void *)-1;
	char headerbuf[128];
	char pathbuf[PATH_MAX]; /* e2176 f780 */
	char namebuf[PATH_MAX]; /* e4224 ef80 */
	char shellbuf[PATH_MAX]; /* e6272 e780 */
	char *name;
	size_t i;
	short handle;
	long nread;
	long ret;
	size_t len;
	size_t envlen;
	
	UNUSED(fn);
	if (nargs <= 3)
		return -EINVAL;
	if (mode != 5 && mode != 7)
	{
		if (mode < 5)
		{
			if (mode != 0 && mode != 3)
				goto do_exec;
		} else
		{
			if (mode != 100)
			{
				if (mode < 100)
				{
					if (mode != 7)
						goto do_exec;
				}
				if (mode != 200)
					goto do_exec;
			}
		}
		mkname = 1;
	}

	/* 0000304e */
	namebuf[0] = '\0';
	if (mkname)
	{
		if (*ptr1 == '/' || *ptr1 == '\\')
		{
			strcpy(namebuf, "u:");
			name = namebuf;
			strncpy(name + 2, ptr1, sizeof(namebuf) - 2);
		} else
		{
			strncpy(namebuf, ptr1, sizeof(namebuf));
			name = namebuf;
		}
		for (i = 0; i < sizeof(namebuf); i++)
		{
			if (name[i] == '\\')
				name[i] = '/';
			if (name[i] == '\0')
				break;
		}
		
		/* 000030f6 */
		ptr1 = name;
		pathbuf[0] = '\0';
		if (strchr(name, '/') == NULL)
		{
			if (dos_fexists(bp, 514, (short)SLB_NARGS(1), ptr1) < 0)
			{
				dos_fsearch(bp, 515, (short)SLB_NARGS(3), ptr1, pathbuf, NULL);
			}
		}
		/* 00003142 */
		if (pathbuf[0] == '\0')
		{
			strncpy(pathbuf, name, sizeof(pathbuf));
			ptr1 = pathbuf;
			namebuf[0] = '\0';
			if ((handle = dos_fopen(bp, 0x3d, (short)SLB_NARGS(2), pathbuf, FO_READ)) < 0)
				return handle;
			nread = dos_fread(bp, 0x3e, (short)SLB_NARGS(3), handle, sizeof(headerbuf), headerbuf);
			dos_fclose(bp, 0x3f, (short)SLB_NARGS(1), handle);
			if (nread <= 1)
				nread = -EFTYPE;
			if (nread < 0)
				return nread;
			if (headerbuf[0] == '#' && headerbuf[1] == '!')
			{
				if (ptr1[1] == ':')
				{
					strncpy(namebuf, ptr1 + 2, sizeof(namebuf));
				} else
				{
					strncpy(namebuf, ptr1, sizeof(namebuf));
				}
				pathbuf[0] = '\0';
				if (headerbuf[2] == '/')
				{
					strcpy(pathbuf, "u:");
				}
				for (i = 0; i < 126 && headerbuf[i] != '\0'; i++)
				{
					if (headerbuf[i] == '\n')
						headerbuf[i] = '\0';
				}
				strcat(pathbuf, &headerbuf[2]);
				shellbuf[0] = '\0';
				if (strchr(pathbuf, '/') == NULL)
				{
					if (dos_fexists(bp, 514, (short)SLB_NARGS(1), pathbuf) < 0)
					{
						dos_fsearch(bp, 513, (short)SLB_NARGS(3), pathbuf, shellbuf, NULL);
					}
				}
				/* 0000329e */
				if (shellbuf[0] != '\0')
				{
					name = shellbuf;
					for (i = 0; i < sizeof(namebuf); i++)
					{
						if (name[i] == '\\')
							name[i] = '/';
						if (name[i] == '\0')
							break;
					}
					strncpy(pathbuf, namebuf, sizeof(pathbuf));
				}
			}
		}
	}
	/* 000032e4 */
	
	if (namebuf[0] != '\0')
	{
		len = strlen(namebuf);
		if (ptr2 != NULL)
			len += strlen(ptr2);
		len = (len + DEF_PAGE_SIZE - 1) & ~(DEF_PAGE_SIZE - 1);
		e6280 = (void *)dos_mxalloc(bp, 0x44, (short)SLB_NARGS(2), len, MX_PREFTTRAM|MX_PRIVATE);
		if ((long)e6280 < 0)
			return (long)e6280;
		strcpy(e6280, namebuf);
		if (ptr2 != NULL && strlen(ptr2) != 0)
		{
			strcat(e6280, " ");
			strcat(e6280, ptr2);
		}
		ptr2 = e6280;
	}
	/* 0000337c */
	
	tail = headerbuf;
	envlen = 0;
	if (ptr2 == NULL || (len = strlen(ptr2)) == 0)
		goto do_exec;
	strncpy(headerbuf + 1, ptr2, sizeof(headerbuf) - 1);
	if (len > 126)
		headerbuf[0] = 0x7f;
	else
		headerbuf[0] = (char) len;
	/* 000033c0 */
	
	if ((long)ptr3 > 0)
		envlen = env_strlen(ptr3);
	if (ptr3 == NULL)
		envlen = env_strlen(bp->p_env),
	/* WTF: rounded up to just exceed a pagesize? wasting almost 8k */
	envlen = (envlen + DEF_PAGE_SIZE + 3) & ~3;
	
	envptr = (void *)dos_mxalloc(bp, 0x44, (short)SLB_NARGS(2), envlen, MX_PREFTTRAM|MX_PRIVATE);
	if ((long)envptr < 0)
	{
		if (e6280 != (void *)-1)
			dos_mfree(bp, 0x49, (short)SLB_NARGS(1), e6280);
		return (long)envptr;
	}

	/* 00003434 */
	{
		char *argv;
		char *ptr;
		
		newenv = envptr;
		bzero(envptr, envlen);
		if ((long)ptr3 > 0)
			memcpy(envptr, ptr3, env_strlen(ptr3));
		if (ptr3 == NULL)
			memcpy(envptr, bp->p_env, env_strlen(bp->p_env));
		argv = NULL;
		ptr = envptr;
		do
		{
			if (strncmp(ptr, "ARGV=", 6) == 0)
			{
				argv = ptr;
				break;
			}
			while (*ptr++ != '\0')
				;	
		} while (*ptr);
		if (argv != NULL)
			*argv = '\0';
		add_env(envptr, "ARGV=");
		add_env(envptr, ptr1); /* WTF? */
	}
	
	/* 000034d8 */
	{
		const char *ptr = ptr2;
		char *dst = shellbuf;
		short quotes;
		const char *end;
		char *cp;
		char c;
		
		len = 0;
		ptr = ptr2;
		while (*ptr != '\0')
		{
			if (*ptr == ' ')
			{
				do
				{
					++len;
					++ptr;
				} while (ptr2[len] == ' ');
			}
			/* 00003500 */
			quotes = 0;
			c = ptr[0];
			if (c == '\'' && ptr[1] != '\'')
			{
				++ptr;
				++len;
				end = ptr2 + len;
				cp = dst;
				for (;;)
				{
					c = *end++;
					++ptr;
					++len;
					if (c == '\0')
						break;
					if (c != '\'')
					{
						cp[quotes] = c;
						quotes++;
						continue;
					}
					if (*end == '\'')
					{
						end++;
						ptr++;
						len++;
						cp[quotes] = '\'';
						quotes++;
						continue;
					}
					if (c == ' ')
						break;
				}
			}
			/* 00003554 */
			if (c != '\0' && c != ' ')
			{
				cp = dst;
				end = ptr2 + len;
				do
				{
					cp[quotes] = *end++;
					ptr++;
					len++;
					quotes++;
				} while (*end != '\0' && *end != ' ');
			}
			dst[quotes] = '\0';
			add_env(envptr, dst);
		}
	}
	
	/* 0000358a */
	len = env_strlen(envptr);
	if (len < envlen)
		dos_mshrink(bp, 0x4a, (short)SLB_NARGS(2), envptr, len);
		
	/* 000035b0 */
do_exec:
	ret = Pexec(mode, ptr1, tail, newenv);
	
	if (e6280 != (void *)-1)
		dos_mfree(bp, 0x49, (short)SLB_NARGS(1), e6280);
		
	return ret;
}
#endif


long dos_pwait(BASEPAGE *bp, long fn, short nargs)
{
	UNUSED(bp);
	UNUSED(fn);
	UNUSED(nargs);
	return Pwait();
}


long dos_pnice(BASEPAGE *bp, long fn, short nargs, short delta)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 0)
		return -EBADARG;
	return Pnice(delta);
}


long dos_pgetpid(BASEPAGE *bp, long fn, short nargs)
{
	UNUSED(bp);
	UNUSED(fn);
	UNUSED(nargs);
	return Pgetpid();
}


long dos_pgetppid(BASEPAGE *bp, long fn, short nargs)
{
	UNUSED(bp);
	UNUSED(fn);
	UNUSED(nargs);
	return Pgetppid();
}


long dos_pgetpgrp(BASEPAGE *bp, long fn, short nargs)
{
	UNUSED(bp);
	UNUSED(fn);
	UNUSED(nargs);
	return Pgetpgrp();
}


long dos_psetpgrp(BASEPAGE *bp, long fn, short nargs, short pid, short newgrp)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 1)
		return -EBADARG;
	return Psetpgrp(pid, newgrp);
}


long dos_pgetuid(BASEPAGE *bp, long fn, short nargs)
{
	UNUSED(bp);
	UNUSED(fn);
	UNUSED(nargs);
	return Pgetuid();
}


long dos_psetuid(BASEPAGE *bp, long fn, short nargs, short id)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 0)
		return -EBADARG;
	return Psetuid(id);
}


long dos_pkill(BASEPAGE *bp, long fn, short nargs, short pid, short sig)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 1)
		return -EBADARG;
	return Pkill(pid, sig);
}


long dos_psignal(BASEPAGE *bp, long fn, short nargs, short sig, long handler)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 1)
		return -EBADARG;
	return (long)Psignal(sig, handler);
}


long dos_pvfork(BASEPAGE *bp, long fn, short nargs)
{
	UNUSED(bp);
	UNUSED(fn);
	UNUSED(nargs);
	return Pvfork();
}


long dos_pgetgid(BASEPAGE *bp, long fn, short nargs)
{
	UNUSED(bp);
	UNUSED(fn);
	UNUSED(nargs);
	return Pgetgid();
}


long dos_psetgid(BASEPAGE *bp, long fn, short nargs, short id)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 0)
		return -EBADARG;
	return Psetgid(id);
}


long dos_psigblock(BASEPAGE *bp, long fn, short nargs, long mask)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 0)
		return -EBADARG;
	return Psigblock(mask);
}


long dos_psigsetmask(BASEPAGE *bp, long fn, short nargs, long mask)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 0)
		return -EBADARG;
	return Psigsetmask(mask);
}


long dos_pusrval(BASEPAGE *bp, long fn, short nargs, long val)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 0)
		return -EBADARG;
	return Pusrval(val);
}


long dos_pdomain(BASEPAGE *bp, long fn, short nargs, short dom)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 0)
		return -EBADARG;
	return Pdomain(dom);
}


void dos_psigreturn(BASEPAGE *bp, long fn, short nargs)
{
	UNUSED(bp);
	UNUSED(fn);
	UNUSED(nargs);
	Psigreturn();
}


long dos_pfork(BASEPAGE *bp, long fn, short nargs)
{
	UNUSED(bp);
	UNUSED(fn);
	UNUSED(nargs);
	return Pfork();
}


long dos_pwait3(BASEPAGE *bp, long fn, short nargs, short flag, long *rusage)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 1)
		return -EBADARG;
	return Pwait3(flag, rusage);
}


long dos_prusage(BASEPAGE *bp, long fn, short nargs, long *rusage)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 0)
		return -EBADARG;
	return Prusage(rusage);
}


long dos_psetlimit(BASEPAGE *bp, long fn, short nargs, short lim, long val)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 1)
		return -EBADARG;
	return Psetlimit(lim, val);
}


void dos_pause(BASEPAGE *bp, long fn, short nargs)
{
	UNUSED(bp);
	UNUSED(fn);
	UNUSED(nargs);
	Pause();
}


long dos_psigpending(BASEPAGE *bp, long fn, short nargs)
{
	UNUSED(bp);
	UNUSED(fn);
	UNUSED(nargs);
	return Psigpending();
}


long dos_pmsg(BASEPAGE *bp, long fn, short nargs, short mode, long mbox, void *msg)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 2)
		return -EBADARG;
	return Pmsg(mode, mbox, msg);
}


long dos_prenice(BASEPAGE *bp, long fn, short nargs, short pid, short delta)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 1)
		return -EBADARG;
	return Prenice(pid, delta);
}


long dos_pumask(BASEPAGE *bp, long fn, short nargs, short mask)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 0)
		return -EBADARG;
	return Pumask(mask);
}


long dos_psemaphore(BASEPAGE *bp, long fn, short nargs, short mode, long id, long timeout)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 2)
		return -EBADARG;
	return Psemaphore(mode, id, timeout);
}


void dos_psigpause(BASEPAGE *bp, long fn, short nargs, long mask)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs > 0)
		Psigpause(mask);
}


long dos_psigaction(BASEPAGE *bp, long fn, short nargs, short sig, struct sigaction *act, struct sigaction *oact)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 2)
		return -EBADARG;
	return Psigaction(sig, act, oact);
}


long dos_pgeteuid(BASEPAGE *bp, long fn, short nargs)
{
	UNUSED(bp);
	UNUSED(fn);
	UNUSED(nargs);
	return Pgeteuid();
}


long dos_pgetegid(BASEPAGE *bp, long fn, short nargs)
{
	UNUSED(bp);
	UNUSED(fn);
	UNUSED(nargs);
	return Pgetegid();
}


long dos_pwaitpid(BASEPAGE *bp, long fn, short nargs, short pid, short flag, long *rusage)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 2)
		return -EBADARG;
	return Pwaitpid(pid, flag, rusage);
}


long dos_pseteuid(BASEPAGE *bp, long fn, short nargs, short euid)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 0)
		return -EBADARG;
	return Pseteuid(euid);
}


long dos_psetegid(BASEPAGE *bp, long fn, short nargs, short egid)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 0)
		return -EBADARG;
	return Psetegid(egid);
}


long dos_pgetauid(BASEPAGE *bp, long fn, short nargs)
{
	UNUSED(bp);
	UNUSED(fn);
	UNUSED(nargs);
	return Pgetauid();
}


long dos_psetauid(BASEPAGE *bp, long fn, short nargs, short auid)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 0)
		return -EBADARG;
	return Psetauid(auid);
}


long dos_pgetgroups(BASEPAGE *bp, long fn, short nargs, short len, unsigned short *gidset)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 1)
		return -EBADARG;
	return Pgetgroups(len, gidset);
}


long dos_psetgroups(BASEPAGE *bp, long fn, short nargs, short len, const unsigned short *gidset)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 1)
		return -EBADARG;
	return Psetgroups(len, gidset);
}


long dos_psetreuid(BASEPAGE *bp, long fn, short nargs, short ruid, short euid)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 1)
		return -EBADARG;
	return Psetreuid(ruid, euid);
}


long dos_psetregid(BASEPAGE *bp, long fn, short nargs, short rgid, short egid)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 1)
		return -EBADARG;
	return Psetregid(rgid, egid);
}


long dos_pgetpriority(BASEPAGE *bp, long fn, short nargs, short which, short who)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 1)
		return -EBADARG;
	return Pgetpriority(which, who);
}


long dos_psetpriority(BASEPAGE *bp, long fn, short nargs, short which, short who, short pri)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 2)
		return -EBADARG;
	return Psetpriority(which, who, pri);
}

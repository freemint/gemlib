/* Process & thread functions
 */

# include <st-out.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include <mintbind.h>
# include <errno.h>
# include <mint/dcntl.h>

# include "gemma.h"
# include "xattr.h"

# define SMS_JUSTSEND	0
# define SMS_REPLSEND	1
# define SMS_PID2APID	0x8000

extern const long sema_fork;
static const char selfname[] = "u:\\proc\\.-1";
static const char smsname[] = "u:\\pipe\\sms";

typedef struct smsblk SMSBLK;

struct smsblk
{
	unsigned short command;
	short destproc;
	short length;
	short res[5];
	short msg[8];
};

static inline long
smswrite(SMSBLK *smsblk)
{
	long file, r;

	file = r = Fopen(smsname, O_WRONLY|O_DENYNONE);
	if (r < 0)
		return r;
	r = Fwrite(file, sizeof(SMSBLK), (void *)smsblk);
	(void)Fclose(file);

	return 0;
}

void
sig_child(void)
{
	long p;
	SMSBLK sms;

	p = Pwait3(1, 0L);
	if (p == 0)
		return;
	bzero(&sms, sizeof(SMSBLK));

	sms.command = (unsigned short)(SMS_JUSTSEND|SMS_PID2APID);
	sms.destproc = (short)Pgetpid();
	sms.length = 16;
	sms.msg[0] = CH_EXIT;
	sms.msg[1] = 0;
	sms.msg[2] = 0;
	sms.msg[3] = (short)(p>>16);
	sms.msg[4] = (short)p;
	smswrite(&sms);
}

static inline long
getprgflags(void)
{
	long file, r, flags;

	file = r = Fopen(selfname, O_RDONLY);
	if (r < 0)
		return (F_FASTLOAD | F_ALTLOAD | F_ALTALLOC);
	r = Fcntl(file, &flags, PGETFLAGS);
	(void)Fclose(file);
	if (r < 0)
		return (F_FASTLOAD | F_ALTLOAD | F_ALTALLOC);

	return flags;
}

/* Find the `file' in `path'. That last
 * is the list of folders to search by.
 */

static inline char *
fsearch(char *path, char *file)
{
	struct xattr xa;
	char cpath[1024], *tok = 0, *sav;
	long r;

	do {
		tok = strtok_r(path, ";,", &sav);
		if (!tok)
			return 0;
		strcpy(cpath, tok);
		strcat(cpath, "\\");
		strcat(cpath, file);
		r = Fxattr(0, cpath, &xa);
	} while(r);

	return tok;
}

/* Return the size of the environment pointed to by `env' */

static long
getenvsize(char *env)
{
	long s, size = 0;

	do {
		s = strlen(env);
		s++;			/* trailing NULL */
		size += s;
		env += s;
	} while(*env);

	size++;				/* the additional NULL at the end */

	return size;
}

/* Add string `var' at the end of the environment `env'.
 * Assumes there is enough space there.
 */

static void
setvar(char *env, char *var)
{
	long len;

	env += (getenvsize(env) - 1);

	strcpy(env, var);
	len = strlen(env);
	len++;
	env[len] = 0;
}

/* Like Pexec(), but constructs ARGV command line,
 * and searches through $PATH.
 *
 * `flags' is reserved.
 */

long
proc_exec(BASEPAGE *bp, long fn, short nargs, \
		short mode, long flags, char *cmd, char *tail, char *env, PROC_ARRAY *p)
{
	PROC_ARRAY *proc = 0;
	char *path, *file = cmd, *newcmd, *newenv = env;
	char cmdline[128], *filespec;
	short load = 0, script = 0;
	long r, envbuf = -1, fsbuf = -1;
	struct xattr xa;

	if (nargs < 5) return -EINVAL;
	if (nargs >= 6) proc = p;
	if ((nargs < 6) || (proc == 0)) proc = get_contrl(bp);

/* 0, filename, command tail, env
 * 3, filename, command tail, env
 * 5, unused, command tail, env
 * 7, flags, command tail, env
 * 100, filename, command tail, env
 * 200, filename, command tail, env
 */
	switch(mode)
	{
		case 0:
		case 3:
		case 100:
		case 200:
			load = 1;
		case 5:			/* fall sru */
		case 7:
			break;
		default:		/* 4, 6, 104, 106, 204, 206, ... */
			return Pexec(mode, cmd, tail, env);
	}

	if (load)
	{
		long x;
		short handle, id;

		fsbuf = _malloc(DEF_PAGE_SIZE);
		if (fsbuf < 0)
			return fsbuf;
		filespec = (char *)fsbuf;

		r = strlen(file);
		if (r)
		{
			for (x = 0; x < r; x++)
			{
				if (file[x] == '/')
					file[x] = '\\';
			}
		}

		filespec[0] = 0;
		if (!strchr(file, '\\'))
		{
			if (Fxattr(0, file, &xa) < 0)
			{
				char *full = 0;

				path = getenv(proc->base, "PATH=");
				if (path)
					full = fsearch(path, file);
				if (full)
				{
					strcpy(filespec, full);
					strcat(filespec, "\\");
				}

			}
		}
		strcat(filespec, file);
		file = filespec;

		handle = Fopen(file, O_RDONLY);
		if (handle < 0)
			return (long)handle;
		r = Fread(handle, sizeof(short), &id);
		Fclose(handle);
		if (r < 2)
			r = -EFTYPE;
		if (r < 0)
			return r;
		if (id == 0x2321)	/* `#!' */
			script++;
	}

	cmdline[0] = 0;
	newcmd = cmdline;

	if (tail)
	{
		long x, envsize = 0;

		r = strlen(tail);
		if (r)
		{
			strncpy(newcmd + 1, tail, 127);
			if (r > 127)
				newcmd[0] = 127;
			else
				newcmd[0] = (char)r;
			if ((long)env > 0)
				envsize = getenvsize(env);
			if (!env)
				envsize = getenvsize(proc->base->p_env);
			envsize += DEF_PAGE_SIZE;	/* should be enough for ARGV string */
			envsize = LROUND(envsize);
			envbuf = _malloc(envsize);
			if (envbuf < 0)
				return envbuf;
			newenv = (char *)envbuf;
			bzero(newenv, envsize);
			if ((long)env > 0)
				memcpy(newenv, env, getenvsize(env));
			if (!env)
				memcpy(newenv, proc->base->p_env, getenvsize(proc->base->p_env));
			setvar(newenv, "ARGV=9XII2000");	/* 9 December 2000, i.e. today ;) */
			x = 0;
			while (tail[x])
			{
				char tmp[512];
				short i;

				while(tail[x] == 0x20)
					x++;
				i = 0;
				if ((tail[x] == '\'') && (tail[x + 1] != '\''))
				{
					x++;
					for(;;)
					{
						char c;

						c = tail[x++];
						if (!c)
							break;		/* broken argument */
						if (c != '\'')
							tmp[i++] = c;
						else
						{
							if (tail[x] == '\'')
							{
								x++;
								tmp[i++] = c;
							}
							else if (tail[x] == 0x20)
								break;
						}
					}
				}
				else
					while(tail[x] && (tail[x] != 0x20))
						tmp[i++] = tail[x++];
				tmp[i] = 0;
				setvar(newenv, tmp);
			}
		}
	}

	r = Pexec(mode, file, newcmd, newenv);

	if (fsbuf != -1)
		_mfree(fsbuf);
	if (envbuf != -1)
		_mfree(envbuf);

	return r;
}

long
thread_fork(BASEPAGE *bp, long fn, short nargs, \
		void *startup, void *address, char *proctitle, long stacksize, PROC_ARRAY *p)
{
	PROC_ARRAY *proc = 0;
	BASEPAGE *new;
	long flags, size, oldsig, pid;

	if (nargs < 3) return -EINVAL;
	if (nargs >= 5) proc = p;
	if ((nargs < 5) || (proc == 0)) proc = get_contrl(bp);

	flags = getprgflags();

	sema_request(sema_fork);

	new = (BASEPAGE *)Pexec(7, flags, "", 0);
	if ((long)new < 0)
		new = (BASEPAGE *)Pexec(5, 0, "", 0);
	if ((long)new <= 0)
	{
		sema_release(sema_fork);
		if (!(long)new)
			return -ENOMEM;
		return (long)new;
	}
	if (nargs >= 4)
		size = stacksize;
	else
		size = 0x00001f00L;
	size += 0x00000100L;
	Mshrink((long)new, size);

	sema_release(sema_fork);

	new->p_tbase = startup;
	new->p_dbase = address;

	oldsig = Psignal(SIGCHLD, sig_child);

	pid = Pexec(104, proctitle, new, 0);

	_mfree((long)new->p_env);
	_mfree((long)new);

	if (pid < 0)
		Psignal(SIGCHLD, oldsig);

	return pid;
}

/* EOF */

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
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

/* This module is quite big, because it needs to cope with the situation,
 * when multiple threads want to open and use the same library, using
 * different private handles and entry vectors.
 *
 * Such data is stored in an array, and the array is updated accordingly
 * on every appl_open(), appl_close() and child death.
 *
 */

# include <signal.h>
# include <mintbind.h>
# include "../include/slb/gemma.h"

# define GEMMA_MAX_THREADS	32

# define sema_create(s) Psemaphore(0, s, 0L)
# define sema_destroy(s) Psemaphore(1, s, 0L)
# define sema_request(s) Psemaphore(2, s, -1L)
# define sema_release(s) Psemaphore(3, s, 0L)

typedef struct
{
	SLB lib;
	long pid;
} LIBPID;

static LIBPID gemma_ident_array[GEMMA_MAX_THREADS];
static LIBPID kernel_ident_array[GEMMA_MAX_THREADS];

static const long sema_appl_open = (const long)appl_open;	/* semaphore for adding/removing pids */
static short appl_inits;

/* Returns a pointer to the library structure */
SLB *
get_gemma_p(void)
{
	long x, dos_pid = Pgetpid();

	for (x = 0; x < GEMMA_MAX_THREADS; x++)
	{
		if (gemma_ident_array[x].pid == dos_pid)
			return &gemma_ident_array[x].lib;
	}

	return 0;	/* huh? */
}

SLB *
get_kern_p(void)
{
	long x, dos_pid = Pgetpid();

	for (x = 0; x < GEMMA_MAX_THREADS; x++)
	{
		if (kernel_ident_array[x].pid == dos_pid)
			return &kernel_ident_array[x].lib;
	}

	return 0;	/* huh? */
}

/* Removes a dead process from the list */
static void
pid_remove(long pid)
{
	long x;

	sema_request(sema_appl_open);

	for (x = 0; x < GEMMA_MAX_THREADS; x++)
	{
		if (gemma_ident_array[x].pid == pid)
		{
			gemma_ident_array[x].pid = 0;
			gemma_ident_array[x].lib.exec = 0;
			gemma_ident_array[x].lib.handle = 0;

			kernel_ident_array[x].pid = 0;
			kernel_ident_array[x].lib.exec = 0;
			kernel_ident_array[x].lib.handle = 0;

			break;
		}
	}

	sema_release(sema_appl_open);
}

# if 0
/* Handler for SIGCHLD */
static void
child_died(long sig)
{
	long r, pid;

	if (sig == SIGCHLD)
	{
		r = Pwaitpid(-1, 1, 0L);
		if (r > 0)
		{
			pid = (r >> 16);
			pid_remove(pid);
		}
	}
}
# endif

/* User functions */

/* These functions are always used, so there is no sense in putting them
 * into separate modules.
 */

GEM_ARRAY *
gem_control(void)
{
	SLB *g = get_gemma_p();
	long _CDECL (*exec)(SLB_HANDLE, long, long) = (long _CDECL (*)(SLB_HANDLE, long, long))g->exec;

	return (GEM_ARRAY *)(*exec)(g->handle, GEM_CTRL, SLB_NARGS(0));
}

long
appl_open(const char *file, short thread, const char *pname)
{
	long r;
	SLB temp;
	long _CDECL (*exec)(SLB_HANDLE, long, long, const char *, long, const char *);
	long _CDECL (*exec2)(SLB_HANDLE, long, long, long, long);
	long _CDECL (*exec3)(SLB_HANDLE, long, long, long, void *);
	long _CDECL (*exec4)(SLB_HANDLE, long, long);

	if (!appl_inits)
	{
		r = sema_create(sema_appl_open);
		if (r >= 0)
			sema_release(sema_appl_open);

		appl_inits = 1;
	}

	r = Slbopen("gemma32.slb", 0L, GEMMA_VERSION, &temp.handle, &temp.exec);
	if (r < 0)
		return r;

	/* This will fail, when the same process tries
	 * to call appl_open() twice without calling
	 * appl_close().
	 */
	exec = (long _CDECL (*)(SLB_HANDLE, long, long, const char *, long, const char *))temp.exec;
	r = (*exec)(temp.handle, AP_OPEN, SLB_NARGS(3), file, thread, pname);
	if (r > 0)
	{
		SLB *kern_p;
		long mark = 0, x, pid = Pgetpid();

		/* Gets the kernel library pointer */
		exec2 = (long _CDECL (*)(SLB_HANDLE, long, long, long, long))temp.exec;
		kern_p = (SLB *)(*exec2)(temp.handle, LIB_CTRL, SLB_NARGS(2), 0x0001, 0);

		/* This operation must be atomic; set a semaphore */
		sema_request(sema_appl_open);

		for (x = 0; x < GEMMA_MAX_THREADS; x++)
		{
			if (gemma_ident_array[x].pid == 0)
			{
				gemma_ident_array[x].pid = pid;
				gemma_ident_array[x].lib = temp;
				/* Sets the gemma pointer inside itself */
				exec3 = (long _CDECL (*)(SLB_HANDLE, long, long, long, void *))temp.exec;
				(*exec3)(temp.handle, LIB_CTRL, SLB_NARGS(2), 0x0003, &gemma_ident_array[x].lib);

				kernel_ident_array[x].pid = pid;
				if (kern_p)
					kernel_ident_array[x].lib = *kern_p;

				mark = 1;

				break;
			}
		}

		sema_release(sema_appl_open);

		if (mark == 0)
		{
			exec4 = (long _CDECL (*)(SLB_HANDLE, long, long))temp.exec;
			(*exec4)(temp.handle, AP_CLOSE, SLB_NARGS(0));
			r = -1;
		}

# if 0
		Psignal(SIGCHLD, child_died);
# endif
	}
	if (r < 0)
		Slbclose(temp.handle);

	return r;
}

long
appl_close(void)
{
	long r = 0;
	SLB *g = get_gemma_p();

	if (g->handle)
	{
		long _CDECL (*exec)(SLB_HANDLE, long, long) = (long _CDECL (*)(SLB_HANDLE, long, long))g->exec;
		r = (*exec)(g->handle, AP_CLOSE, SLB_NARGS(0));
		Slbclose(g->handle);

		pid_remove(Pgetpid());
	}

	return r;
}

/* EOF */

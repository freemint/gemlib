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

/* User functions */

/* These functions are always used, so there is no sense in putting them
 * into separate modules.
 */

GEM_ARRAY *
gem_control(void)
{
	SLB *g = get_gemma_p();

	return (GEM_ARRAY *)(g->exec)(g->handle, (long)GEM_CTRL, (short)0);
}

long
appl_open(char *file, short thread, char *pname)
{
	long r;
	SLB temp;

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
	r = (temp.exec)(temp.handle, (long)AP_OPEN, (short)3, (char *)file, (short)thread, (char *)pname);
	if (r > 0)
	{
		SLB *kern_p;
		long mark = 0, x, pid = Pgetpid();

		/* Sets the gemma pointer inside itself */
		(temp.exec)(temp.handle, (long)34, (short)2, 0x0003, (long)&temp);
		/* Gets the kernel library pointer */
		kern_p = (SLB *)(temp.exec)(temp.handle, (long)34, (short)2, 0x0001, 0);

		/* This operation must be atomic; set a semaphore */
		sema_request(sema_appl_open);

		for (x = 0; x < GEMMA_MAX_THREADS; x++)
		{
			if (gemma_ident_array[x].pid == 0)
			{
				gemma_ident_array[x].pid = pid;
				gemma_ident_array[x].lib.exec = temp.exec;
				gemma_ident_array[x].lib.handle = temp.handle;

				kernel_ident_array[x].pid = pid;
				kernel_ident_array[x].lib.exec = kern_p->exec;
				kernel_ident_array[x].lib.handle = kern_p->handle;

				mark = 1;

				break;
			}
		}

		sema_release(sema_appl_open);

		if (mark == 0)
		{
			(temp.exec)(temp.handle, (long)AP_CLOSE, (short)0);
			Slbclose((long)temp.handle);

			return -1;
		}

		Psignal(SIGCHLD, child_died);
	}
	else
		Slbclose((long)temp.handle);

	return r;
}

long
appl_close()
{
	long r = 0;
	SLB *g = get_gemma_p();

	if (g->handle)
	{
		r = (g->exec)(g->handle, (long)AP_CLOSE, (short)0);
		Slbclose((long)g->handle);

		pid_remove(Pgetpid());
	}

	return r;
}

/* EOF */

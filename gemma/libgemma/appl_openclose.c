# include <mintbind.h>
# include <gemma/gemma.h>

# ifndef GEMMA_MULTIPROC

SLB gemma;

long	appl_open(char *file, short thread, char *pname)
{
	long r;

	r = _slbopen("gemma.slb", 0L, GEMMA_VERSION, &gemma.handle, &gemma.exec);
	if (r < 0)
		return r;

	return (gemma.exec)(gemma.handle, (long)AP_OPEN, (short)3, (char *)file, (short)thread, (char *)pname);
}

long	appl_close()
{
	long r;

	r = (gemma.exec)(gemma.handle, (long)AP_CLOSE, (short)0);
	(void)Slbclose((long)gemma.handle);

	return r;
}

# else /* MULTIPROC */

SLB gemma[1000];

long	appl_open(char *file, short thread, char *pname)
{
	long r, pid = Pgetpid();

	r = _slbopen("gemma.slb", 0L, GEMMA_VERSION, &gemma[pid].handle, &gemma[pid].exec);
	if (r < 0)
		return r;

	return (gemma[pid].exec)(gemma[pid].handle, (long)AP_OPEN, (short)3, (char *)file, (short)thread, (char *)pname);
}

long	appl_close()
{
	long r, pid = Pgetpid();

	r = (gemma[pid].exec)(gemma[pid].handle, (long)AP_CLOSE, (short)0);
	(void)Slbclose((long)gemma[pid].handle);

	return r;
}

# endif

/* EOF */

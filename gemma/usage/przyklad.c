/* Simple GEM application
 */

# include <stdlib.h>
# include <mintbind.h>

# include <gemma/gemma.h>

# include "przyklad.h"

long
newmsg(WINDIAL *wd, short vec, short *msg)
{
	if (msg[0] == AP_TERM)
		windial_longjmp(wd, vec);	/* never returns */
	return 0;
}

/* `flag' is 1 when the function is executed
 * as a result of thread_fork()
 */

long
thread(short flag)
{
	WINDIAL window, *wd = &window;
	long r;
	short m = 0;

	r = appl_open("przyklad.rsc", flag, PNAME);
	if (r < 0)
		return r;

	windial_create(wd, WINDOW, 0, 0, WINTITLE);

	if (windial_setjmp(wd, 0, newmsg) == 0)
	{
		windial_open(wd);

		while((m != EXIT) && (m != -1))
		{
			m = windial_formdo(wd);
			objc_xchange(wd, m, 0, 1);
			if (m == FORK)
				thread_fork(thread, NULL, 8192L);
		}
	}

	windial_close(wd);
	windial_delete(wd);

	return appl_close();
}

int
main()
{
	return thread(0);
}

/* EOF */

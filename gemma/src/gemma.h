/* Constant definitions for gemma.c & other modules */

# include <basepage.h>
# include <gem.h>
# include "gemma/struct.h"

# define VDISYS	115L
# define AESSYS	200L

# define MAX_LINE	25	/* for alerts, real max is 40 */
# define MAX_PID	999
# define MAX_AES_OP	199
# define DEF_PAGE_SIZE	8192
# define MIN_PAGE_SIZE	1024

# define WINDIAL_MAGIC	25091973L

# ifndef ulong
#  define ulong unsigned long
# endif
# ifndef ushort
#  define ushort unsigned short
# endif
# ifndef uchar
#  define uchar unsigned char
# endif

struct gemma_flags {
	long parameters;
	long max_pid;
	long pagesize;
	long minpagesize;
	long access_check;
	long res1;
	long button_delay;
	long release_delay;
	long maxaesop;
	const long *ctrl;
	long zoomboxes;
	long moveboxes;
	long screen_comp;
	long system_alerts;
	long blocking_alerts;
};

struct gproc {
	GEM_ARRAY gem;
	char *rawrscaddr;		/* from here user doesn't know */
	char *rscaddr;
	long rsclength;
	char *rscname;			/* for broken systems */
	short fsel_init_done;
	char fsel_path[1024];
	char fsel_file[256];
	char fsel_outname[1024];
	short env_refs;
	BASEPAGE *base;
	WINDIAL window;
};

typedef struct gproc PROC_ARRAY;
extern struct gemma_flags sflags;

/* Common macros & function prototypes */

# ifdef DEBUG
#  define DEBUGMSG(p)	debug_print(p)
# else
#  define DEBUGMSG(p)
# endif

# define UNUSED(p)	(void)p
# define LMASK		(sizeof(long) - 1)
# define LROUND(x)	((x + LMASK) & ~LMASK)
# define TOUCH(p)	\
{\
	if (sflags.access_check)		\
		(void)*(volatile char *)p;	\
}

# define aes40(p) (p->gem.global[0] >= 0x0400)
# define bell()	Cconout(7)
# define _malloc(s) __malloc(s, 0x0003)
# define _malloc_read(s) __malloc(s, 0x0043)
# define sema_create(s) Psemaphore(0, s, 0L)
# define sema_destroy(s) Psemaphore(1, s, 0L)
# define sema_request(s) Psemaphore(2, s, -1L)
# define sema_release(s) Psemaphore(3, s, 0L)

# ifdef DEBUG
void debug_print(char *string);
# endif

char *getenv(BASEPAGE *bp, const char *var);
OBJECT *obj2addr(PROC_ARRAY *proc, short type, ulong obj);
PROC_ARRAY *get_contrl(BASEPAGE *bp);
long __malloc(long size, short mode);
void _mfree(long adr);

/* EOF */

/* Constant definitions for gemma.c & other modules */

/*  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

# include <mint/basepage.h>
# include <mint/slb.h>

# include "../../gemlib/gem.h"
# include "../include/slb/gemma-struct.h"

# include "../config.h"

# ifndef APP_DESK
#  define APP_DESK	2
# endif

# ifndef AES_MESSAGE
#  define AES_MESSAGE	12
# endif

# ifndef AES_OBJECT
#  define AES_OBJECT	13
# endif

# ifndef AES_FORM
#  define AES_FORM	14
# endif

# ifndef ulong
#  define ulong unsigned long
# endif
# ifndef ushort
#  define ushort unsigned short
# endif
# ifndef uchar
#  define uchar unsigned char
# endif

struct xattr
{
	ushort	mode;
	long	index;
	ushort	dev;
	ushort	rdev;		/* "real" device */
	ushort	nlink;
	ushort	uid;
	ushort	gid;
	long	size;
	long	blksize;
	long	nblocks;
	ushort	mtime, mdate;
	ushort	atime, adate;
	ushort	ctime, cdate;
	short	attr;
	short	reserved2;
	long	reserved3[2];
};

struct gemma_flags
{
	long magic;
	long parameters;
	long max_pid;
	long pagesize;
	long minpagesize;
	long maxaesop;
	const long *ctrl;
	long button_delay;
	long release_delay;
	long access_check;
	long zoomboxes;
	long moveboxes;
	long screen_comp;
	long system_alerts;
	long blocking_alerts;
	long debug;
	long xfselect;
	long reserved;
};

typedef struct
{
	GEM_ARRAY gem;			/* user-visible part of this structure */
	BASEPAGE *base;			/* process basepage address */
	SLB *ego;			/* a pointer to the library itself */
	SLB kern;			/* The kernel library structure */
	SLB fsel;			/* The fileselector library structure */
	WINDIAL *wchain;		/* the begin of the window chain */
	char *rawrscaddr;		/* address for the raw RSC buffer */
	char *rscaddr;			/* address for the RSC buffer */
	long rsclength;			/* RSC file length (rounded up to longword) */
	char *rscname;			/* RSC filename for broken systems */
	ulong bvset;			/* A value passed from appl_bvset() */
	short env_refs;			/* counter for recursions in env_eval() */
	ushort debug;			/* debugging enable flag */
	ushort alert;			/* an alert box is being displayed */
	ushort cb_fsel;			/* flag for call-backs from fileselector.slb */
	short fontw;			/* returned by graf_handle() */
	short fonth;
	short cellw;
	short cellh;
	WINDIAL window;			/* window 0, integrated here to save some RAM */
	short fsel_init_done;		/* is 1 when fselector was called at least once */
	char fsel_path[1024];		/* retains last selected path */
	char fsel_file[256];		/* retains last selected filename */
	char fsel_outname[1024];	/* the complete filename returned */
} PROC_ARRAY;

/* Global data structures */

extern struct gemma_flags sflags;	/* in callout.c */
extern short whitebak;			/* in gemma.c */
extern const long sema_fork;		/* in gemma.c */
extern PROC_ARRAY *pidtable[];		/* in gemma.c */
extern short menu_height;		/* in appl.c */

/* Common macros & function prototypes */

# ifdef __GNUC__
#  define INLINE	static inline
#  define UNUSED(p)
# else
#  define INLINE	static
#  define UNUSED(p)	(void)p
# endif

# define VDISYS	115L
# define AESSYS	200L
# define MAX_AES_OP	159
# define WINDIAL_MAGIC	25091973L

# ifdef DEBUG
#  define DEBUGMSG(p)					\
{							\
	if (sflags.debug && proc->debug)		\
		debug_print(__FUNCTION__,p);	\
}
# else
#  define DEBUGMSG(p)
# endif

# ifdef _ROBUST_AES
#  define TOUCH(p)
# else
#  define TOUCH(p)				\
{						\
	if (sflags.access_check)		\
		(void)*(volatile char *)p;	\
}
# endif

# define LMASK		(sizeof(long) - 1)
# define LROUND(x)	((x + LMASK) & ~LMASK)
# define aes40(p) 	(p->gem.global[0] >= 0x0400)

# ifdef DEBUG
void debug_print(char *fn, char *string);
# endif

const long sema_users;

void bin2asc(long number, char *out);			/* in bodajze alert.c */
OBJECT *obj2addr(PROC_ARRAY *proc, short type, ulong obj);
PROC_ARRAY *get_contrl(BASEPAGE *bp);

/* EOF */

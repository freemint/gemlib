# define ushort unsigned short
# define ulong unsigned long

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

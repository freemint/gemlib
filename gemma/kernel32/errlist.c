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

#ifndef EMOUNT
#define EMOUNT __KERNEL_NEG(200)
#endif
#ifndef EEOF
#define EEOF	__KERNEL_NEG(230)
#endif
#ifndef ENOTSUP
#define ENOTSUP __KERNEL_NEG(350)
#endif
#ifndef ECANCELLED
#define ECANCELLED __KERNEL_NEG(351)
#endif
#ifndef EOWNERDEAD
#define EOWNERDEAD __KERNEL_NEG(352)
#endif
#ifndef ENOTRECOVERABLE
#define ENOTRECOVERABLE __KERNEL_NEG(353)
#endif

struct error {
	short code;
	const char *text;
};
static struct error const errorlist[] = {
	{ -EERROR, "General error" },
	{ -EBUSY, "Resource busy" },
	{ -EUKCMD, "Unknown command" },
	{ -ECRC, "Checksum error" },
	{ -EBADR, "Bad request" },
	{ -ESPIPE, "Illegal seek" },
	{ -EMEDIUMTYPE, "Wrong media type" },
	{ -ESECTOR, "Sector not found" },
	{ -EPAPER, "The printer is out of paper" },
	{ -EWRITE, "Write fault" },
	{ -EREAD, "Read fault" },
	{ -EGENERIC, "General mishap" },
	{ -EROFS, "Write protected" },
	{ -ECHMEDIA, "Unexpected media change" },
	{ -ENODEV, "No such device" },
	{ -EBADSEC, "Bad sectors found" },
	{ -ENOMEDIUM, "No media inserted" },
	{ -EINSERT, "Insert media" },
	{ -EDRVNRSP, "Device not responding" },
	{ -ESRCH, "No such process" },
	{ -ECHILD, "No child processes" },
	{ -EDEADLK, "Resource deadlock would occur" },
	{ -ENOTBLK, "Block device required" },
	{ -EISDIR, "The file specified is a directory" },
	{ -EINVAL, "Invalid argument" },
	{ -EFTYPE, "Inappropriate file type or format" },
	{ -EILSEQ, "Illegal byte sequence" },
	{ -ENOSYS, "Function not implemented" },
	{ -ENOENT, "No such file or directory" },
	{ -ENOTDIR, "Object is not a directory" },
	{ -EMFILE, "Too many open files for a process" },
	{ -EACCES, "Operation not permitted" },
	{ -EBADF, "Bad file descriptor" },
	{ -EPERM, "Permission denied" },
	{ -ENOMEM, "Virtual memory exhausted" },
	{ -EFAULT, "Bad address" },
	{ -ENXIO, "No such device or address" },
	{ -EXDEV, "Cross device rename" },
	{ -ENMFILES, "No more matching filenames" },
	{ -ENFILE, "File table overflow, too many files open" },
	{ -ELOCKED, "Locking conflict" },
	{ -ENSLOCK, "No such lock" },
	{ -EBADARG, "Bad argument" },
	{ -EINTERNAL, "Internal error" },
	{ -ENOEXEC, "Invalid executable file format" },
	{ -ESBLOCK, "Memory block growth failure" },
	{ -EBREAK, "Aborted by user" },
	{ -EXCPT, "Terminated with bombs" },
	{ -ETXTBSY, "Text file busy" },
	{ -EFBIG, "File too big" },
	{ -ELOOP, "Too many symbolic links" },
	{ -EPIPE, "Broken pipe" },
	{ -EMLINK, "Too many links" },
	{ -ENOTEMPTY, "Directory not empty" },
	{ -EEXIST, "File already exists" },
	{ -ENAMETOOLONG, "Name too long" },
	{ -ENOTTY, "Object is not a tty" },
	{ -ERANGE, "Range error" },
	{ -EDOM, "Domain error" },
	{ -EIO, "I/O error" },
	{ -ENOSPC, "No space left on device" },
	{ -EPROCLIM, "Too many processes for user" },
	{ -EUSERS, "Too many users" },
	{ -EDQUOT, "Quota exceeded" },
	{ -ESTALE, "Stale NFS file handle" },
	{ -EREMOTE, "Object is remote" },
	{ -EBADRPC, "RPC struct is bad" },
	{ -ERPCMISMATCH, "RPC mismatch" },
	{ -EPROGUNAVAIL, "RPC program not available" },
	{ -EPROGMISMATCH, "RPC program mismatch" },
	{ -EPROCUNAVAIL, "RPC bad procedure for program" },
	{ -ENOLCK, "No locks available" },
	{ -EAUTH, "Authentication error" },
	{ -ENEEDAUTH, "Need authenticator" },
	{ -EBACKGROUND, "Inappropriate operation for background process" },
	{ -EBADMSG, "Not a data message" },
	{ -EIDRM, "Identifier removed" },
	{ -EMULTIHOP, "Multihop attempted" },
	{ -ENODATA, "No data available" },
	{ -ENOLINK, "Link has been severed" },
	{ -ENOMSG, "No message of desired type" },
	{ -ENOSR, "Out of stream resources" },
	{ -ENOSTR, "Device not a stream" },
	{ -EOVERFLOW, "Value too large for defined data type" },
	{ -EPROTO, "Protocol error" },
	{ -ETIME, "Timer expired" },
	{ -E2BIG, "Argument list too long" },
	{ -ERESTART, "Interrupted system call should be restarted" },
	{ -ECHRNG, "Channel number is out of range" },
	{ -EINTR, "Interrupted function call" },
	{ -ESNDLOCKED, "The sound subsystem is already in use" },
	{ -ESNDNOTLOCK, "The sound subsystem was not locked" },
	{ -EL2NSYNC, "Level 2 not synchronized" },
	{ -EL3HLT, "Level 3 halted" },
	{ -EL3RST, "Level 3 reset" },
	{ -ELNRNG, "Link number out of range" },
	{ -EUNATCH, "Protocol driver not attached" },
	{ -ENOCSI, "No CSI structure available" },
	{ -EL2HLT, "Level 2 halted" },
	{ -EBADE, "Invalid exchange" },
	{ -EXFULL, "Exchange full" },
	{ -ENOANO, "No anode" },
	{ -EBADRQC, "Invalid request code" },
	{ -EBADSLT, "Invalid slot" },
	{ -EBFONT, "Bad font file format" },
	{ -ENONET, "Machine is not on the network" },
	{ -ENOPKG, "Package is not installed" },
	{ -EADV, "Advertise error" },
	{ -ESRMNT, "Srmount error" },
	{ -ECOMM, "Communication error on send" },
	{ -EDOTDOT, "RFS specific error" },
	{ -ELIBACC, "Cannot access the required shared library" },
	{ -ELIBBAD, "Accessing a corrupted shared library" },
	{ -ELIBSCN, ".lib section in a.out corrupted" },
	{ -ELIBMAX, "Attempting to link too many shared libraries" },
	{ -ELIBEXEC, "Cannot exec a shared library directly" },
	{ -ESTRPIPE, "Streams pipe error" },
	{ -EUCLEAN, "Structure needs cleaning" },
	{ -ENOTNAM, "Not a XENIX named type file" },
	{ -ENAVAIL, "No XENIX semaphores available" },
	{ -EREMOTEIO, "Remote I/O error" },
	{ -EMOUNT, "Crossing the mount point" },
	{ -EEOF, "End of file" },
	{ -ENOTSOCK, "Socket operation requested on something not a socket" },
	{ -EDESTADDRREQ, "Destination address required" },
	{ -EMSGSIZE, "Message too long" },
	{ -EPROTOTYPE, "Wrong protocol type" },
	{ -ENOPROTOOPT, "Protocol not available" },
	{ -EPROTONOSUPPORT, "Protocol not supported" },
	{ -ESOCKTNOSUPPORT, "Socket type not suported" },
	{ -EOPNOTSUPP, "Operation not supported" },
	{ -EPFNOSUPPORT, "Protocol family not supported" },
	{ -EAFNOSUPPORT, "Address family not supported by protocol" },
	{ -EADDRINUSE, "Address already in use" },
	{ -EADDRNOTAVAIL, "Cannot assign the requested address" },
	{ -ENETDOWN, "Network is down" },
	{ -ENETUNREACH, "Network unreachable" },
	{ -ENETRESET, "Network dropped connection because of reset" },
	{ -ECONNABORTED, "Software caused connection abort" },
	{ -ECONNRESET, "Connection reset by peer" },
	{ -EISCONN, "Socket is already connected" },
	{ -ENOTCONN, "Socket is not connected" },
	{ -ESHUTDOWN, "Cannot send after shutdown" },
	{ -ETIMEDOUT, "Connection timed out" },
	{ -ECONNREFUSED, "Connection refused" },
	{ -EHOSTDOWN, "Host is down" },
	{ -EHOSTUNREACH, "No route to host" },
	{ -EALREADY, "Operation is already in progress" },
	{ -EINPROGRESS, "Operation now in progress" },
	{ -EAGAIN, "Resource temporarily unavailable" },
	{ -ENOBUFS, "No buffer space available" },
	{ -ETOOMANYREFS, "Too many references" },
	{ -ENOTSUP, "Function not implemented" },
	{ -ECANCELLED, "aio request was canceled before complete" },
	{ -EOWNERDEAD, "Owner died" },
	{ -ENOTRECOVERABLE, "State not recoverable" },

	{ 0, NULL }
};

const char *dos_serror(BASEPAGE *bp, long fn, short nargs, long error)
{
	short i;
	
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 0)
		return "[Wrong call to kernel.slb]";
	if (error != 0)
	{
		for (i = 0; errorlist[i].code != 0; i++)
		{
			if (errorlist[i].code == error)
				return errorlist[i].text;
		}
		return "Unknown error";
	}
	return "No errors";
}

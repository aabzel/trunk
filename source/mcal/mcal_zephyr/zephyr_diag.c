#include "zephyr_diag.h"

#include <errno.h>

#include "log.h"

const char* ErrNo2Str(int err_no) {
    const char *name = "?";
    switch (err_no) {
    case 0:
        name = "Ok!";
        break;
    case -EPERM:
        name = "Not owner";
        break;
    case -ENOENT:
        name = "No such file or directory";
        break;
    case -ESRCH:
        name = "No such context";
        break;
    case -EINTR:
        name = "Interrupted system call";
        break;
    case -EIO:
        name = "I/OErr";
        break;
    case -ENXIO:
        name = "No such device or address";
        break;
    case -E2BIG:
        name = "Arg list too long";
        break;
    case -ENOEXEC:
        name = "Exec formatErr";
        break;
    case -EBADF:
        name = "Bad file number";
        break;
    case -ECHILD:
        name = "No children";
        break;
    case -EAGAIN:
        name = "WaitingPeriodTimedOut(NoMoreContexts)";
        break;
    case -ENOMEM:
        name = "Not enough core";
        break;
    case -EACCES:
        name = "Permission denied";
        break;
    case -EFAULT:
        name = "Bad address";
        break;
    case -ENOTBLK:
        name = "Block device required";
        break;
    case -EBUSY:
        name = "Mount device busy";
        break;
    case -EEXIST:
        name = "File exists";
        break;
    case -EXDEV:
        name = "Cross-device link";
        break;
    case -ENODEV:
        name = "No such device";
        break;
    case -ENOTDIR:
        name = "Not a directory";
        break;
    case -EISDIR:
        name = "Is a directory";
        break;
    case -EINVAL:
        name = "Invalid argument";
        break;
    case -ENFILE:
        name = "File table overflow";
        break;
    case -EMFILE:
        name = "Too many open files";
        break;
    case -ENOTTY:
        name = "Not a typewriter";
        break;
    case -ETXTBSY:
        name = "Text file busy";
        break;
    case -EFBIG:
        name = "File too large";
        break;
    case -ENOSPC:
        name = "No space left on device";
        break;
    case -ESPIPE:
        name = "Illegal seek";
        break;
    case -EROFS:
        name = "Read-only file system";
        break;
    case -EMLINK:
        name = "Too many links";
        break;
    case -EPIPE:
        name = "Broken pipe";
        break;
    case -EDOM:
        name = "Argument too large";
        break;
    case -ERANGE:
        name = "Result too large";
        break;
    case -ENOMSG:
        name = "Unexpected message type";
        break;
    case -EDEADLK:
        name = "Resource deadlock avoided";
        break;
    case -ENOLCK:
        name = "No locks available";
        break;
    case -ENOSTR:
        name = "STREAMS device required";
        break;
    case -ENODATA:
        name = "Missing expected message data";
        break;
    case -ETIME:
        name = "STREAMS timeout occurred";
        break;
    case -ENOSR:
        name = "Insufficient memory";
        break;
    case -EPROTO:
        name = "Generic STREAMSErr";
        break;
    case -EBADMSG:
        name = "Invalid STREAMS message";
        break;
    case -ENOSYS:
        name = "FunctionNotImplemented";
        break;
    case -ENOTEMPTY:
        name = "Directory not empty";
        break;
    case -ENAMETOOLONG:
        name = "File name too long";
        break;
    case -ELOOP:
        name = "Too many levels of symbolic links";
        break;
    case -EOPNOTSUPP:
        name = "Operation not supported on socket";
        break;
    case -EPFNOSUPPORT:
        name = "Protocol family not supported";
        break;
    case -ECONNRESET:
        name = "Connection reset by peer";
        break;
    case -ENOBUFS:
        name = "No buffer space available";
        break;
    case -EAFNOSUPPORT:
        name = "Addr family not supported";
        break;
    case -EPROTOTYPE:
        name = "Protocol wrong type for socket";
        break;
    case -ENOTSOCK:
        name = "Socket operation on non-socket";
        break;
    case -ENOPROTOOPT:
        name = "Protocol not available";
        break;
    case -ESHUTDOWN:
        name = "Can't send after socket shutdown";
        break;
    case -ECONNREFUSED:
        name = "Connection refused";
        break;
    case -EADDRINUSE:
        name = "Address already in use";
        break;
    case -ECONNABORTED:
        name = "Software caused connection abort";
        break;
    case -ENETUNREACH:
        name = "Network is unreachable";
        break;
    case -ENETDOWN:
        name = "Network is down";
        break;
    case -ETIMEDOUT:
        name = "Connection timed out";
        break;
    case -EHOSTDOWN:
        name = "Host is down";
        break;
    case -EHOSTUNREACH:
        name = "No route to host";
        break;
    case -EINPROGRESS:
        name = "Operation now in progress";
        break;
    case -EALREADY:
        name = "Operation already in progress";
        break;
    case -EDESTADDRREQ:
        name = "Destination address required";
        break;
    case -EMSGSIZE:
        name = "Message size";
        break;
    case -EPROTONOSUPPORT:
        name = "Protocol not supported";
        break;
    case -ESOCKTNOSUPPORT:
        name = "Socket type not supported";
        break;
    case -EADDRNOTAVAIL:
        name = "Can't assign requested address";
        break;
    case -ENETRESET:
        name = "Network dropped connection on reset";
        break;
    case -EISCONN:
        name = "Socket is already connected";
        break;
    case -ENOTCONN:
        name = "Socket is not connected";
        break;
    case -ETOOMANYREFS:
        name = "Too many references: can't splice";
        break;
    case -ENOTSUP:
        name = "Unsupported value";
        break;
    case -EILSEQ:
        name = "Illegal byte sequence";
        break;
    case -EOVERFLOW:
        name = "Value overflow";
        break;
    case -ECANCELED:
        name = "Operation canceled";
        break;
    default:
        name = "?";
        break;
    }
    return name;
}

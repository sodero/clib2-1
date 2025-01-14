/*
 * $Id: netdb.h,v 1.4 2006-01-08 12:06:14 clib2devs Exp $
*/

#ifndef _NETDB_H
#define _NETDB_H

#include <features.h>

#ifndef _SYS_SOCKET_H
#include <sys/socket.h>
#endif /* _SYS_SOCKET_H */

#ifndef _NETINET_IN_H
#include <netinet/in.h>
#endif /* _NETINET_IN_H */

#ifndef _STDBOOL_H
#include <stdbool.h>
#endif

#include <features.h>

__BEGIN_DECLS

#ifdef __GNUC__
 #ifdef __PPC__
  #pragma pack(2)
 #endif
#elif defined(__VBCC__)
 #pragma amiga-align
#endif

/****************************************************************************/

#define MAXHOSTNAMELEN 256 /* max hostname size */

/****************************************************************************/

/*
 * Structures returned by network data base library.  All addresses are
 * supplied in host order, and returned in network order (suitable for
 * use in system calls).
 */
struct hostent
{
	char *	h_name;				/* official name of host */
	char **	h_aliases;			/* alias list */
	int		h_addrtype;			/* host address type */
	int		h_length;			/* length of address */
	char **	h_addr_list;		/* list of addresses from name server */
};

#define	h_addr h_addr_list[0] /* address, for backward compatiblity */

/*
 * Assumption here is that a network number
 * fits in an unsigned long -- probably a poor one.
 */
struct netent
{
	char *			n_name;		/* official name of net */
	char **			n_aliases;	/* alias list */
	int				n_addrtype;	/* net address type */
	in_addr_t		n_net;		/* network # */
};

struct servent
{
	char *		s_name;		/* official service name */
	char **		s_aliases;	/* alias list */
	int			s_port;		/* port # */
	char *		s_proto;	/* protocol to use */
};

struct protoent
{
	char *		p_name;		/* official protocol name */
	char **		p_aliases;	/* alias list */
	int			p_proto;	/* protocol # */
};

/****************************************************************************/

/*
 * Error return codes from gethostbyname() and gethostbyaddr()
 * (left in extern int h_errno).
 */

#define	NETDB_INTERNAL	-1	/* see errno */
#define	NETDB_SUCCESS	0	/* no problem */
#define	HOST_NOT_FOUND	1 	/* Authoritative Answer Host not found */
#define	TRY_AGAIN		2 	/* Non-Authoritive Host not found, or SERVERFAIL */
#define	NO_RECOVERY		3 	/* Non recoverable errors, FORMERR, REFUSED, NOTIMP */
#define	NO_DATA			4 	/* Valid name, no data record of requested type */
#define	NO_ADDRESS		NO_DATA	/* no address, look for MX record */

/****************************************************************************/

/* Possible values for `ai_flags' field in `addrinfo' structure.  */
#define AI_PASSIVE      0x01
#define AI_CANONNAME    0x02
#define AI_NUMERICHOST  0x04
#define AI_V4MAPPED     0x08
#define AI_ALL          0x10
#define AI_ADDRCONFIG   0x20
#define AI_NUMERICSERV  0x400

/* Possible flags for getnameinfo.  */
#define NI_NUMERICHOST  1
#define NI_NUMERICSERV  2
#define NI_NOFQDN       4
#define NI_NAMEREQD     8
#define NI_DGRAM        16
#define NI_NUMERICSCOPE 256

#define NI_MAXSERV      32

#define EAI_NOERROR 0

/* Error values for `getaddrinfo' function.  */
# define EAI_BADFLAGS     -1    /* Invalid value for `ai_flags' field.  */
# define EAI_NONAME       -2    /* NAME or SERVICE is unknown.  */
# define EAI_AGAIN        -3    /* Temporary failure in name resolution.  */
# define EAI_FAIL         -4    /* Non-recoverable failure in name res.  */
# define EAI_FAMILY       -6    /* `ai_family' not supported.  */
# define EAI_SOCKTYPE     -7    /* `ai_socktype' not supported.  */
# define EAI_SERVICE      -8    /* SERVICE not supported for `ai_socktype'.  */
# define EAI_MEMORY       -10   /* Memory allocation failure.  */
# define EAI_SYSTEM       -11   /* System error returned in `errno'.  */
# define EAI_OVERFLOW     -12   /* Argument buffer overflow.  */

/* Structure to contain information about address of a service provider.  */
struct addrinfo
{
  int ai_flags;                 /* Input flags.  */
  int ai_family;                /* Protocol family for socket.  */
  int ai_socktype;              /* Socket type.  */
  int ai_protocol;              /* Protocol for socket.  */
  socklen_t ai_addrlen;         /* Length of socket address.  */
  struct sockaddr *ai_addr;     /* Socket address for socket.  */
  char *ai_canonname;           /* Canonical name for service location.  */
  struct addrinfo *ai_next;     /* Pointer to next in list.  */
};

extern int h_errno;

extern struct hostent *gethostbyaddr(const void *addr, socklen_t len, int type);
extern struct hostent *gethostbyname(const char *name);
extern struct netent *getnetbyaddr(in_addr_t net, int type);
extern struct netent *getnetbyname(const char *name);
extern struct protoent *getprotobyname(const char *name);
extern struct protoent *getprotobynumber(int proto);
extern struct servent *getservbyname(const char *name, const char *proto);
extern struct servent *getservbyport(int port, const char *proto);

#if defined(_GNU_SOURCE) || defined(_BSD_SOURCE)
extern void herror(const char *);
extern const char *hstrerror(int);
extern int gethostbyname_r(const char *, struct hostent *, char *, size_t, struct hostent **, int *);
extern int gethostbyname2_r(const char *, int, struct hostent *, char *, size_t, struct hostent **, int *);
extern struct hostent *gethostbyname2(const char *, int);
extern int gethostbyaddr_r(const void *, socklen_t, int, struct hostent *, char *, size_t, struct hostent **, int *);
extern int getservbyport_r(int, const char *, struct servent *, char *, size_t, struct servent **);
extern int getservbyname_r(const char *, const char *, struct servent *, char *, size_t, struct servent **);
#define EAI_NODATA     -5
#define EAI_ADDRFAMILY -9
#define EAI_INPROGRESS -100
#define EAI_CANCELED   -101
#define EAI_NOTCANCELED -102
#define EAI_ALLDONE    -103
#define EAI_INTR       -104
#define EAI_IDN_ENCODE -105
#endif

#define NI_MAXHOST 1025
#define NI_MAXSERV 32

extern const char *gai_strerror(int ecode);
extern int getaddrinfo (const char *name, const char *service, const struct addrinfo *req, struct addrinfo **pai);
extern void freeaddrinfo (struct addrinfo *ai);
extern int getnameinfo(const struct sockaddr *sa, socklen_t salen, char *node, socklen_t nodelen, char *service, socklen_t servicelen, int flags);

#ifdef __GNUC__
 #ifdef __PPC__
  #pragma pack()
 #endif
#elif defined(__VBCC__)
 #pragma default-align
#endif

__END_DECLS

#endif /* _NETDB_H */

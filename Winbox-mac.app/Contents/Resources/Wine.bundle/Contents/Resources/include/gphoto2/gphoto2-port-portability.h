/** \file gphoto2-port-log.h
 *
 * Copyright 2001 Lutz Mueller <lutz@users.sf.net>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details. 
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301  USA
 */
#ifndef __GPHOTO2_PORT_PORTABILITY_H__
#define __GPHOTO2_PORT_PORTABILITY_H__

#ifdef _GPHOTO2_INTERNAL_CODE

#if defined(WIN32) && !defined(__WINESRC__)

/************************************************************************
 * Begin Windows definitions (but not during WINE compilation)
 ************************************************************************/

# include <windows.h>
/* done by mingw/wine headers ... defined to struct ... tsaes*/
#undef interface
# include <sys/types.h>
# include <sys/stat.h>
# include <string.h>
# include <stdio.h>
# include <direct.h>

# ifdef IOLIBS
# undef IOLIBS
# endif
# define IOLIBS			"."
# define strcasecmp		_stricmp
# ifndef snprintf
#  define snprintf		_snprintf
# endif

#define __func__ __FUNCTION__

typedef SSIZE_T ssize_t;

/* Work-around for readdir() */
typedef struct {
	HANDLE handle;
	int got_first;
	WIN32_FIND_DATA search;
	char dir[1024];
	char drive[32][2];
	int  drive_count;
	int  drive_index;
} GPPORTWINDIR;


/* Directory-oriented functions */
# define gp_system_dir		  GPPORTWINDIR *
# define gp_system_dirent	  WIN32_FIND_DATA *
# define gp_system_dir_delim	  '\\'

# define sleep(x) usleep((x) * 1000 * 1000)



/************************************************************************
 * End WIN32 definitions
 ************************************************************************/

#elif defined(__SOME_OS2_MAGIC_HERE__)

/************************************************************************
 * Begin OS/2 definitions
 ************************************************************************/

# define strcasecmp(foo,bar) stricmp(foo,bar)
# define gp_system_dir_delim		'\\'

# ifndef GPIO_OS2_INCLUDED
#  define GPIO_OS2_INCLUDED
#  define IOLIBS getenv("IOLIBS")
/*#define IOLIBS "./libgphoto2_port"*/
#  define RTLD_LAZY       0x001


#  ifndef HAVE_TERMIOS_H
#   define  INCL_DOSDEVIOCTL   /* DosDevIOCtl values */
#   define IOCTL_ASYNC                        0x0001
#   define ASYNC_SETBAUDRATE                  0x0041
/* c_cflag bit meaning */
#   define CBAUD   0x0000100f
#   define  B0     0x00000000      /* hang up */
#   define  B50    0x00000001
#   define  B75    0x00000002
#   define  B110   0x00000003
#   define  B134   0x00000004
#   define  B150   0x00000005
#   define  B200   0x00000006
#   define  B300   0x00000007
#   define  B600   0x00000008
#   define  B1200  0x00000009
#   define  B1800  0x0000000a
#   define  B2400  0x0000000b
#   define  B4800  0x0000000c
#   define  B9600  0x0000000d
#   define  B19200 0x0000000e
#   define  B38400 0x0000000f
#   define EXTA    B19200
#   define EXTB    B38400
#   define  CSIZE  0x00000030
#   define   CS5   0x00000000
#   define   CS6   0x00000010
#   define   CS7   0x00000020
#   define   CS8   0x00000030
#   define CSTOPB  0x00000040
#   define CREAD   0x00000080
#   define PARENB  0x00000100
#   define PARODD  0x00000200
#   define HUPCL   0x00000400
#   define CLOCAL  0x00000800
#   define CBAUDEX 0x00001000
#   define  B57600  0x00001001
#   define  B115200 0x00001002
#   define  B230400 0x00001003
#   define  B460800 0x00001004
#   define  B76800  0x00001005
#   define  B153600 0x00001006
#   define  B307200 0x00001007
#   define  B614400 0x00001008
#   define  B921600 0x00001009
#   define  B500000 0x0000100a
#   define  B576000 0x0000100b
#   define B1000000 0x0000100c
#   define B1152000 0x0000100d
#   define B1500000 0x0000100e
#   define B2000000 0x0000100f

#  endif /* HAVE_TERMIOS_H */

#  define CIBAUD  0x100f0000      /* input baud rate (not used) */
#  define CMSPAR  0x40000000      /* mark or space (stick) parity */
/* #define CRTSCTS 0x80000000  */    /* flow control */

/* modem lines */
#  define TIOCM_LE        0x001
#  define TIOCM_DTR       0x002
#  define TIOCM_RTS       0x004
#  define TIOCM_ST        0x008
#  define TIOCM_SR        0x010
#  define TIOCM_CTS       0x020
#  define TIOCM_CAR       0x040
#  define TIOCM_RNG       0x080
#  define TIOCM_DSR       0x100
#  define TIOCM_CD        TIOCM_CAR
#  define TIOCM_RI        TIOCM_RNG

#  define TIOCMBIC        0x06C
#  define TIOCMBIS        0x06B
#  define TIOCMGET        0x06E

# endif /* GPIO_OS2_INCLUDED */

/************************************************************************
 * End OS/2 definitions
 ************************************************************************/

#else 

/************************************************************************
 * Begin POSIX/XOPEN definitions
 ************************************************************************/

/* yummy. :) */

/* XOPEN needed for usleep */
#ifndef _XOPEN_SOURCE
# define _XOPEN_SOURCE 500
#else
# if ((_XOPEN_SOURCE - 0) < 500)
#  undef _XOPEN_SOURCE
#  define _XOPEN_SOURCE 500
# endif
#endif

/* for nanosleep */
# ifndef _POSIX_C_SOURCE
#  define _POSIX_C_SOURCE 199309
# endif
# include <time.h>

# include <strings.h>
# include <sys/types.h>
# include <dirent.h>
#ifdef HAVE_SYS_PARAM_H
# include <sys/param.h>
#endif
# include <sys/stat.h>
# include <unistd.h>


/* Directory-oriented functions */
/** A system directory handle */
# define gp_system_dir           DIR *
/** A system directory entry */
# define gp_system_dirent	 struct dirent *
/** The directory delimiter character on this platform. */
# define gp_system_dir_delim	 '/'

/************************************************************************
 * End POSIX/XOPEN definitions
 ************************************************************************/

#endif /* else */


/************************************************************************
 * Begin platform independent portability functions
 ************************************************************************/

int		 gp_system_mkdir	(const char *dirname);
int              gp_system_rmdir        (const char *dirname);
gp_system_dir	 gp_system_opendir	(const char *dirname);
gp_system_dirent gp_system_readdir	(gp_system_dir d);
const char*	 gp_system_filename	(gp_system_dirent de);
int		 gp_system_closedir	(gp_system_dir dir);
int		 gp_system_is_file	(const char *filename);
int		 gp_system_is_dir	(const char *dirname);

/************************************************************************
 * End platform independent portability functions
 ************************************************************************/
#endif /* _GPHOTO2_INTERNAL_CODE */

#endif /* ifndef __GPHOTO2_PORT_PORTABILITY_H__ */
/* end of file */

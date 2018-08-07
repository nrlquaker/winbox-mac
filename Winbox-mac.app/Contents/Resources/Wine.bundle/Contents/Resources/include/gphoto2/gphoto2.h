/** \file
 * \brief Convenience header for gphoto2
 *
 * \author Copyright 2001 Lutz Mueller <lutz@users.sf.net>
 *
 * \note
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * \note
 * This library is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details. 
 *
 * \note
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301  USA
 */
#ifndef __GPHOTO2_H__
#define __GPHOTO2_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifdef OS2
#  include <db.h>
#  include <sys/param.h>
#  define CAMLIBS     getenv("CAMLIBS")
#  define RTLD_LAZY   0x001
#  define VERSION     "2"
#  define usleep(t)   _sleep2(((t)+500)/ 1000)
#endif

#ifdef WIN32
#undef CAMLIBS
#define CAMLIBS "."
#endif

#include <gphoto2/gphoto2-port.h>
#include <gphoto2/gphoto2-port-log.h>
#include <gphoto2/gphoto2-port-result.h>

#include <gphoto2/gphoto2-file.h>
#include <gphoto2/gphoto2-library.h>
#include <gphoto2/gphoto2-setting.h>

#ifdef __cplusplus
}
#endif

#endif /* __GPHOTO2_H__ */

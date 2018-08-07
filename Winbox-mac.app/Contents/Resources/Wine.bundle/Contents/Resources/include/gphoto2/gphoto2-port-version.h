/** \file gphoto2-port-version.h
 *
 * Copyright 2002 Hans Ulrich Niedermann <gp@n-dimensional.de>
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

#ifndef __GPHOTO2_PORT_VERSION_H__
#define __GPHOTO2_PORT_VERSION_H__

typedef enum {
  GP_VERSION_SHORT = 0,
  GP_VERSION_VERBOSE = 1
} GPVersionVerbosity;


#ifdef __cplusplus
extern "C" {
#endif

typedef const char **(*GPVersionFunc)(GPVersionVerbosity verbose);
const char **gp_port_library_version(GPVersionVerbosity verbose);

#ifdef __cplusplus
}
#endif

#endif /* __GPHOTO2_PORT_VERSION_H__ */

/*
 * Local Variables:
 * c-file-style:"linux"
 * indent-tabs-mode:t
 * End:
 */

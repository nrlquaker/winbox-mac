/** \file
 * \brief Camery driver header.
 * 
 * \author Copyright 2000 Scott Fritzinger
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

#ifndef __GPHOTO2_LIBRARY_H__
#define __GPHOTO2_LIBRARY_H__

#include <gphoto2/gphoto2-abilities-list.h>
#include <gphoto2/gphoto2-camera.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * \brief Returns a unique id for the camera driver.
 *
 * \param id a #CameraText
 * \return a gphoto2 error code
 *
 **/
typedef int (* CameraLibraryIdFunc)        (CameraText *id);

/**
 * \brief Adds the abilities of the supported models to the supplied list.
 *
 * \param list a #CameraAbilitiesList
 * \return a gphoto2 error code
 *
 **/
typedef int (* CameraLibraryAbilitiesFunc) (CameraAbilitiesList *list);

/**
 * \brief Initializes the camera.
 *
 * \param camera a #Camera
 * \param context a #GPContext
 * \return a gphoto2 error code
 *
 * The camera driver will establish a first connection
 * to the camera and configure the camera variable (i.e. using 
 * #gp_filesystem_set_list_funcs or #gp_port_get_settings).
 *
 **/
typedef int (* CameraLibraryInitFunc)      (Camera *camera, GPContext *context);

/*
 * If you want to write a camera library, you need to implement 
 * the following three functions. Everything else should be declared
 * as static.
 */
int camera_id		(CameraText *id);
int camera_abilities 	(CameraAbilitiesList *list);
int camera_init 	(Camera *camera, GPContext *context);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __GPHOTO2_LIBRARY_H__ */

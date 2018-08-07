/** \file
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

#ifndef __GPHOTO2_RESULT_H__
#define __GPHOTO2_RESULT_H__

/* Additional error codes are defined here */
#include <gphoto2/gphoto2-port-result.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * \brief Corrupted data received
 *
 * Data is corrupt. This error is reported by camera drivers if corrupted
 * data has been received that can not be automatically handled. Normally,
 * drivers will do everything possible to automatically recover from this
 * error.
 **/
#define GP_ERROR_CORRUPTED_DATA      -102 /* Corrupted data             */

/**
 * \brief File already exists
 *
 * An operation failed because a file existed. This error is reported for
 * example when the user tries to create a file that already exists.
 **/
#define GP_ERROR_FILE_EXISTS         -103

/**
 * \brief Specified camera model was not found
 *
 * The specified model could not be found. This error is reported when
 * the user specified a model that does not seem to be supported by 
 * any driver.
 **/
#define GP_ERROR_MODEL_NOT_FOUND     -105

/**
 * \brief Specified directory was not found
 *
 * The specified directory could not be found. This error is reported when
 * the user specified a directory that is non-existent.
 **/
#define GP_ERROR_DIRECTORY_NOT_FOUND -107

/**
 * \brief Specified file was not found
 *
 * The specified file could not be found. This error is reported when
 * the user wants to access a file that is non-existent.
 **/
#define GP_ERROR_FILE_NOT_FOUND      -108

/**
 * \brief Specified directory already exists
 *
 * The specified directory already exists. This error is reported for example 
 * when the user wants to create a directory that already exists.
 **/
#define GP_ERROR_DIRECTORY_EXISTS    -109

/**
 * \brief The camera is already busy 
 *
 * Camera I/O or a command is in progress.
 **/
#define GP_ERROR_CAMERA_BUSY    -110

/**
 * \brief Path is not absolute
 * 
 * The specified path is not absolute. This error is reported when the user
 * specifies paths that are not absolute, i.e. paths like "path/to/directory".
 * As a rule of thumb, in gphoto2, there is nothing like relative paths.
 **/
#define GP_ERROR_PATH_NOT_ABSOLUTE   -111

/**
 * \brief Cancellation successful.
 *
 * A cancellation requestion by the frontend via progress callback and
 * GP_CONTEXT_FEEDBACK_CANCEL was successful and the transfer has been aborted.
 */
#define GP_ERROR_CANCEL              -112

/**
 * \brief Unspecified camera error
 *
 * The camera reported some kind of error. This can be either a
 * photographic error, such as failure to autofocus, underexposure, or
 * violating storage permission, anything else that stops the camera
 * from performing the operation.
 */
#define GP_ERROR_CAMERA_ERROR	     -113

/**
 * \brief Unspecified failure of the operating system
 *
 * There was some sort of OS error in communicating with the camera,
 * e.g. lack of permission for an operation.
 */
#define GP_ERROR_OS_FAILURE	     -114

/**
 * \brief Not enough space
 *
 * There was not enough free space when uploading a file.
 */
#define GP_ERROR_NO_SPACE	     -115


const char *gp_result_as_string      (int result);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __GPHOTO2_RESULT_H__ */

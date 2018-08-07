/** \file gphoto2-list.h
 *
 * Lists of files, folders, cameras, etc.
 *
 * \author Copyright 2001 Scott Fritzinger
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

#ifndef __GPHOTO2_LIST_H__
#define __GPHOTO2_LIST_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** 
 * \brief A generic list
 * 
 * This structure provides a list with \a name:value pairs that is used in various
 * parts of libgphoto2. Its details are internal, please use the
 * gp_list_xxx accessor functions.
 * 
 * Usage pattern for CameraList for users external of
 * libgphoto2, such as libgphoto2 frontends:
 *
 * \code
 *    CameraList *list;
 *    gp_list_new (&list);
 *    init_list_somehow (list);
 *    for (i=0; i < gp_list_count(list); i++) {
 *        char *name, *value;
 *        gp_list_get_name (list, i, &name);
 *        gp_list_get_name (list, i, &value);
 *        do_something_with (name, value);
 *    }
 *    gp_list_free (list);
 * \endcode
 *
 * Please do NOT directly instantiate a CameraList object like this:
 * \code
 *               CameraList foo;     // DO NOT DO THIS
 * \endcode
 * 
 * Please do NOT directly access the structure members like this:
 * \code
 *               list->entry[i].name // DO NOT DO THIS
 * \endcode
 */
typedef struct _CameraList CameraList;

int     gp_list_new   (CameraList **list);
int     gp_list_ref   (CameraList *list);
int     gp_list_unref (CameraList *list);
int     gp_list_free  (CameraList *list);

int	gp_list_count	   (CameraList *list);
int	gp_list_append	   (CameraList *list,
			    const char *name, const char *value);
int     gp_list_reset      (CameraList *list);
int     gp_list_sort       (CameraList *list);

int gp_list_find_by_name (CameraList *list, int *index, const char *name);

int gp_list_get_name  (CameraList *list, int index, const char **name);
int gp_list_get_value (CameraList *list, int index, const char **value);

int gp_list_set_name  (CameraList *list, int index, const char *name);
int gp_list_set_value (CameraList *list, int index, const char *value);

int gp_list_populate  (CameraList *list, const char *format, int count);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __GPHOTO2_LIST_H__ */

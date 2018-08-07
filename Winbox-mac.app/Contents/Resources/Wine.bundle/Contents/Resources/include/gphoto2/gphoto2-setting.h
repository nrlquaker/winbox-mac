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

#ifndef __GPHOTO2_SETTING_H__
#define __GPHOTO2_SETTING_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

int gp_setting_set (char *id, char *key, char *value);
int gp_setting_get (char *id, char *key, char *value);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __GPHOTO2_SETTING_H__ */

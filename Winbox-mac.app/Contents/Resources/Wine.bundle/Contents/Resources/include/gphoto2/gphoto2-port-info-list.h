/** \file
 *
 * \author Copyright 2001 Lutz Mueller <lutz@users.sf.net>
 *
 * \par License
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * \par
 * This library is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details. 
 *
 * \par
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301  USA
 */

#ifndef __GPHOTO2_PORT_INFO_LIST_H__
#define __GPHOTO2_PORT_INFO_LIST_H__

/**
 * \brief The gphoto port type.
 *
 * Enumeration specifying the port type.
 * The enum is providing bitmasks, but most code uses it as
 * just the one specific values.
 */
typedef enum { 
	GP_PORT_NONE        =      0,	/**< \brief No specific type associated. */
	GP_PORT_SERIAL      = 1 << 0,	/**< \brief Serial port. */
	GP_PORT_USB         = 1 << 2,	/**< \brief USB port. */
	GP_PORT_DISK        = 1 << 3,	/**< \brief Disk / local mountpoint port. */
	GP_PORT_PTPIP       = 1 << 4,	/**< \brief PTP/IP port. */
	GP_PORT_USB_DISK_DIRECT = 1 << 5, /**< \brief Direct IO to an usb mass storage device. */
	GP_PORT_USB_SCSI    = 1 << 6	/**< \brief USB Mass Storage raw SCSI port. */
} GPPortType;

/**
 * \brief Information about the current port.
 * 
 * Specific information about the current port. Usually taken from the
 * "--port=XXXX" setting from the frontend.
 *
 * This is not to be confused with the driver configurable port settings
 * in \ref GPPortSettings.
 */
struct _GPPortInfo;
typedef struct _GPPortInfo *GPPortInfo;

#include <gphoto2/gphoto2-port.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef _GPHOTO2_INTERNAL_CODE
#include <gphoto2/gphoto2-port-log.h>
extern const StringFlagItem gpi_gphoto_port_type_map[];
#endif

int gp_port_info_new (GPPortInfo *info);
int gp_port_info_get_name (GPPortInfo info, char **name);
int gp_port_info_set_name (GPPortInfo info, const char *name);
int gp_port_info_get_path (GPPortInfo info, char **path);
int gp_port_info_set_path (GPPortInfo info, const char *path);
int gp_port_info_get_type (GPPortInfo info, GPPortType *type);
int gp_port_info_set_type (GPPortInfo info, const GPPortType type);
int gp_port_info_get_library_filename (GPPortInfo info, char **lib);
int gp_port_info_set_library_filename (GPPortInfo info, char *lib);

/* Internals are private */
typedef struct _GPPortInfoList GPPortInfoList;

int gp_port_info_list_new  (GPPortInfoList **list);
int gp_port_info_list_free (GPPortInfoList *list);

int gp_port_info_list_append (GPPortInfoList *list, GPPortInfo info);

int gp_port_info_list_load (GPPortInfoList *list);

int gp_port_info_list_count (GPPortInfoList *list);

int gp_port_info_list_lookup_path (GPPortInfoList *list, const char *path);
int gp_port_info_list_lookup_name (GPPortInfoList *list, const char *name);

int gp_port_info_list_get_info (GPPortInfoList *list, int n, GPPortInfo *info);

const char *gp_port_message_codeset (const char*);

/**
 * Name of the environment variable which may contain the path where
 * to look for the IO libs. If this environment variable is not defined,
 * use the compiled-in default constant.
 *
 * \internal Internal use only.
 */
#ifdef _GPHOTO2_INTERNAL_CODE
#define IOLIBDIR_ENV "IOLIBS"
#endif /* _GPHOTO2_INTERNAL_CODE */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __GPHOTO2_PORT_INFO_LIST_H__ */

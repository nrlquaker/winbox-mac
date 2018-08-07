/** \file gphoto2-abilities-list.h
 * \brief List of supported camera models including their abilities.
 *
 * \author Copyright 2000 Scott Fritzinger
 *
 * \par
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

#ifndef __GPHOTO2_ABILITIES_LIST_H__
#define __GPHOTO2_ABILITIES_LIST_H__

#include <gphoto2/gphoto2-context.h>
#include <gphoto2/gphoto2-list.h>
#include <gphoto2/gphoto2-port-info-list.h>

#include <gphoto2/gphoto2-port-log.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * Current implementation status of the camera driver.
 */
typedef enum {
	GP_DRIVER_STATUS_PRODUCTION,	/**< Driver is production ready. */
	GP_DRIVER_STATUS_TESTING,	/**< Driver is beta quality. */
	GP_DRIVER_STATUS_EXPERIMENTAL,	/**< Driver is alpha quality and might even not work. */
	GP_DRIVER_STATUS_DEPRECATED	/**< Driver is no longer recommended to use and will be removed. */
} CameraDriverStatus;

/**
 * Type of the device represented. Currently we have Still Cameras
 * and MTP Audio Players.
 */
typedef enum {
        GP_DEVICE_STILL_CAMERA          = 0,	 /**< Traditional still camera */
        GP_DEVICE_AUDIO_PLAYER          = 1 << 0 /**< Audio player */
} GphotoDeviceType;

/**
 * A bitmask of remote control related operations of the device.
 * Some drivers might support additional dynamic capabilities (like the PTP driver).
 */
typedef enum {
        GP_OPERATION_NONE       	= 0,	  /**< No remote control operation supported. */
        GP_OPERATION_CAPTURE_IMAGE      = 1 << 0, /**< Capturing images supported. */
        GP_OPERATION_CAPTURE_VIDEO      = 1 << 1, /**< Capturing videos supported. */
        GP_OPERATION_CAPTURE_AUDIO      = 1 << 2, /**< Capturing audio supported. */
        GP_OPERATION_CAPTURE_PREVIEW    = 1 << 3, /**< Capturing image previews supported. */
        GP_OPERATION_CONFIG             = 1 << 4, /**< Camera and Driver configuration supported. */
        GP_OPERATION_TRIGGER_CAPTURE    = 1 << 5  /**< Camera can trigger capture and wait for events. */
} CameraOperation;

/**
 * A bitmask of image related operations of the device.
 */
typedef enum {
        GP_FILE_OPERATION_NONE          = 0,      /**< No special file operations, just download. */
        GP_FILE_OPERATION_DELETE        = 1 << 1, /**< Deletion of files is possible. */
        GP_FILE_OPERATION_PREVIEW       = 1 << 3, /**< Previewing viewfinder content is possible. */
        GP_FILE_OPERATION_RAW           = 1 << 4, /**< Raw retrieval is possible (used by non-JPEG cameras) */
        GP_FILE_OPERATION_AUDIO         = 1 << 5, /**< Audio retrieval is possible. */
        GP_FILE_OPERATION_EXIF          = 1 << 6  /**< EXIF retrieval is possible. */
} CameraFileOperation;

/**
 * A bitmask of filesystem related operations of the device.
 */
typedef enum {
        GP_FOLDER_OPERATION_NONE        = 0,	  /**< No special filesystem operation. */
        GP_FOLDER_OPERATION_DELETE_ALL  = 1 << 0, /**< Deletion of all files on the device. */
        GP_FOLDER_OPERATION_PUT_FILE    = 1 << 1, /**< Upload of files to the device possible. */
        GP_FOLDER_OPERATION_MAKE_DIR    = 1 << 2, /**< Making directories on the device possible. */
        GP_FOLDER_OPERATION_REMOVE_DIR  = 1 << 3  /**< Removing directories from the device possible. */
} CameraFolderOperation;

#ifdef _GPHOTO2_INTERNAL_CODE

  /* enum CameraOperation */
  extern const StringFlagItem gpi_camera_operation_map[];

  /* enum CameraFileOperation */
  extern const StringFlagItem gpi_file_operation_map[];

  /* enum CameraFolderOperation */
  extern const StringFlagItem gpi_folder_operation_map[];

  /* enum GphotoDeviceType */
  extern const StringFlagItem gpi_gphoto_device_type_map[];

  /* enum CameraDriverStatus */
  extern const StringFlagItem gpi_camera_driver_status_map[];

#endif /* _GPHOTO2_INTERNAL_CODE */


/** 
 * \brief Describes the properties of a specific camera.
 *
 * The internals of this structures are used extensively by the
 * camlibs, but the status regarding use by frontends is questionable.
 */
typedef struct {
        char model [128];			/**< \brief name of camera model */
        CameraDriverStatus status;		/**< \brief driver quality */

	/** \brief Supported port types. */
	GPPortType port;
	/** \brief Supported serial port speeds (terminated with a value of 0). */
        int speed [64];

        /* Supported operations */
        CameraOperation       operations;	/**< \brief Camera operation funcs */
        CameraFileOperation   file_operations;  /**< \brief Camera file op funcs */
        CameraFolderOperation folder_operations;/**< \brief Camera folder op funcs */

	int usb_vendor;		/**< \brief USB Vendor D */
	int usb_product;	/**< \brief USB Product ID */
	int usb_class;          /**< \brief USB device class */
	int usb_subclass;	/**< \brief USB device subclass */
	int usb_protocol;	/**< \brief USB device protocol */

        /* For core use */
        char library [1024];	/**< \brief (Internal) library filename */
        char id [1024];		/**< \brief (Internal) camera ID name */

	GphotoDeviceType 	device_type;	/**< \brief Device type. */
	/** Reserved space to use in the future w/out changing the 
	 * struct size */
        int reserved2;		/**< reserved space \internal */
        int reserved3;		/**< reserved space \internal */
        int reserved4;		/**< reserved space \internal */
        int reserved5;		/**< reserved space \internal */
        int reserved6;		/**< reserved space \internal */
        int reserved7;		/**< reserved space \internal */
        int reserved8;		/**< reserved space \internal */
} CameraAbilities;


/**
 * \brief List of supported camera models including their abilities
 *
 * The internals of this list are hidden - use the access functions.
 */
typedef struct _CameraAbilitiesList CameraAbilitiesList;


int gp_abilities_list_new    (CameraAbilitiesList **list);
int gp_abilities_list_free   (CameraAbilitiesList *list);

int gp_abilities_list_load   (CameraAbilitiesList *list, GPContext *context);
int gp_abilities_list_load_dir   (CameraAbilitiesList *list, const char *dir, GPContext *context);
int gp_abilities_list_reset  (CameraAbilitiesList *list);

int gp_abilities_list_detect (CameraAbilitiesList *list,
			      GPPortInfoList *info_list, CameraList *l,
			      GPContext *context);

int gp_abilities_list_append (CameraAbilitiesList *list,
			      CameraAbilities abilities);

int gp_abilities_list_count  (CameraAbilitiesList *list);

int gp_abilities_list_lookup_model (CameraAbilitiesList *list,
				    const char *model);

int gp_abilities_list_get_abilities (CameraAbilitiesList *list, int index,
				     CameraAbilities *abilities);

const char *gp_message_codeset (const char *);


/**
 * Name of the environment variable which may contain the path where
 * to look for the camlibs. If this environment variable is not defined,
 * use the compiled-in default constant.
 *
 * \internal Internal use only.
 */
#ifdef _GPHOTO2_INTERNAL_CODE
#define CAMLIBDIR_ENV "CAMLIBS"
#endif /* _GPHOTO2_INTERNAL_CODE */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __GPHOTO2_ABILITIES_LIST_H__ */

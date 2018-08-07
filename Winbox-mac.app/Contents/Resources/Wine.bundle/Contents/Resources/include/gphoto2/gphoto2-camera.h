/** \file
 *
 * \brief Implement Camera object representing a camera attached to the system.
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

#ifndef __GPHOTO2_CAMERA_H__
#define __GPHOTO2_CAMERA_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * \brief Object representing a camera attached to the system.
 *
 * A Camera object represents a specific instance of a (physical of
 * virtual) camera attached to the system.
 * 
 * The abilities of this type of camera are stored in a CameraAbility
 * object.
 *
 * The details of the Camera object are internal.
 */
typedef struct _Camera Camera;
#ifdef __cplusplus
}
#endif /* __cplusplus */


#include <gphoto2/gphoto2-abilities-list.h>
#include <gphoto2/gphoto2-port.h>

#include <gphoto2/gphoto2-widget.h>
#include <gphoto2/gphoto2-filesys.h>
#include <gphoto2/gphoto2-result.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** 
 * \brief CameraText structure used in various functions.
 *
 * A text structure containing translated text returned
 * by various functions (about, manual, summary). You should
 * not assume a size.
 */
typedef struct {
	char text [32 * 1024]; /**< \brief Character string containing the translated text. */
} CameraText;

/** 
 * \brief A structure created by the capture operation.
 *
 * A structure containing the folder and filename of an object
 * after a successful capture and is passed as reference to the
 * gp_camera_capture() function.
 */
typedef struct {
	char name [128];	/**< \brief Name of the captured file. */
	char folder [1024];	/**< \brief Name of the folder of the captured file. */
} CameraFilePath;

/**
 * \brief Type of the capture to do.
 *
 * Specifies the type of capture the user wants to do with the
 * gp_camera_capture() function.
 */
typedef enum {
	GP_CAPTURE_IMAGE,	/**< \brief Capture an image. */
	GP_CAPTURE_MOVIE,	/**< \brief Capture a movie. */
	GP_CAPTURE_SOUND	/**< \brief Capture audio. */
} CameraCaptureType;

/**
 * \brief Specify what event we received from the camera.
 *
 * Used by gp_camera_wait_for_event() to specify what
 * event happened on the camera.
 *
 */
typedef enum {
	GP_EVENT_UNKNOWN,	/**< unknown and unhandled event. argument is a char* or NULL */
	GP_EVENT_TIMEOUT,	/**< timeout, no arguments */
	GP_EVENT_FILE_ADDED,	/**< CameraFilePath* = file path on camfs */
	GP_EVENT_FOLDER_ADDED,	/**< CameraFilePath* = folder on camfs */
	GP_EVENT_CAPTURE_COMPLETE	/**< last capture is complete */
} CameraEventType;

/**
 * \name Camera object member functions
 *
 * These functions must be implemented by a camlib and the camlib's 
 * camera_init() function will add them to a Camera object.
 *
 * @{
 */
/**
 * \brief The camera exit function
 *
 * \param camera the current camera
 * \param context a #GPContext
 *
 * This functions is called in the camera driver for closing the camera
 * connection. It should do the necessary cleanups of the internal camera
 * state, free allocated private structures and similar.
 *
 * The driver does not need to close the #GPPort, this is done by libgphoto2
 * itself.
 *
 * Implement this function if you need to any of this stuff, otherwise leave
 * it out.
 *
 * \returns a gphoto error code 
 */
typedef int (*CameraExitFunc)      (Camera *camera, GPContext *context);

/**
 * \brief Get a configuration tree for the camera and its driver
 *
 * \param camera the current camera
 * \param widget pointer to store the toplevel widget of the tree
 * \param context the active #GPContext
 *
 * A camera driver can support configuration of either its own behaviour
 * or the camera device itself. To allow a flexible driver framework,
 * the camera driver provides a generic configuration widget tree to the
 * frontend, which then renders it, allows user input and sends it back
 * via the #CameraSetConfigFunc function to have the driver configure itself
 * or the camera.
 *
 * If you do not have configuration ability, there is no need to specify this
 * function.
 *
 * \returns a gphoto error code
 */
typedef int (*CameraGetConfigFunc) (Camera *camera, CameraWidget **widget,
				    GPContext *context);
/**
 * \brief Get a configuration widget for a specific configuration
 *
 * \param camera the current camera
 * \param name the name of the widget
 * \param widget pointer to store the toplevel widget of the tree
 * \param context the active #GPContext
 *
 * A camera driver can support configuration of either its own behaviour
 * or the camera device itself. To allow a flexible driver framework,
 * the camera driver provides a generic configuration widget tree to the
 * frontend, which then renders it, allows user input and sends it back
 * via the #CameraSetConfigFunc function to have the driver configure itself
 * or the camera.
 * 
 * This specific function retrieves one specific named entry, and not the full
 * tree to allow for querying specific settings faster.
 *
 * If you do not have configuration ability, there is no need to specify this
 * function.
 *
 * \returns a gphoto error code
 */
typedef int (*CameraGetSingleConfigFunc) (Camera *camera, const char *name, CameraWidget **widget,
				    GPContext *context);
/**
 * \brief List all configuration widgets for a specific configuration
 *
 * \param camera the current camera
 * \param list the list of widgets available
 * \param context the active #GPContext
 *
 * A camera driver can support configuration of either its own behaviour
 * or the camera device itself. To allow a flexible driver framework,
 * the camera driver provides a generic configuration widget tree to the
 * frontend, which then renders it, allows user input and sends it back
 * via the #CameraSetConfigFunc function to have the driver configure itself
 * or the camera.
 * 
 * This specific function retrieves all the available configuration values in a flat list.
 *
 * This is different than the GetConfigFunc, which returns a configuration tree.
 *
 * If you do not have configuration ability, there is no need to specify this
 * function.
 *
 * \returns a gphoto error code
 */
typedef int (*CameraListConfigFunc) (Camera *camera, CameraList *list, GPContext *context);
/**
 * \brief Set the configuration in the camera
 *
 * \param camera the current camera 
 * \param widget the configuration widget tree that was changed
 * \param context the active #GPContext
 *
 * This function is called in the driver after the configuration is set.
 * It is called directly after setting the value and might called multiple
 * times (or never) after just one #CameraGetConfigFunc.
 * 
 * \returns a gphoto error code
 */
typedef int (*CameraSetConfigFunc) (Camera *camera, CameraWidget  *widget,
				    GPContext *context);
/**
 * \brief Set a single configuration variable in the camera
 *
 * \param camera the current camera 
 * \param name the widget to set
 * \param widget the configuration widget tree that was changed
 * \param context the active #GPContext
 *
 * This function is called in the driver after the configuration value is set.
 * 
 * \returns a gphoto error code
 */
typedef int (*CameraSetSingleConfigFunc) (Camera *camera, const char *name, CameraWidget  *widget,
				    GPContext *context);

typedef int (*CameraCaptureFunc)   (Camera *camera, CameraCaptureType type,
				    CameraFilePath *path, GPContext *context);
typedef int (*CameraTriggerCaptureFunc)   (Camera *camera, GPContext *context);
typedef int (*CameraCapturePreviewFunc) (Camera *camera, CameraFile *file,
					 GPContext *context);
typedef int (*CameraSummaryFunc)   (Camera *camera, CameraText *text,
				    GPContext *context);
typedef int (*CameraManualFunc)    (Camera *camera, CameraText *text,
				    GPContext *context);
typedef int (*CameraAboutFunc)     (Camera *camera, CameraText *text,
				    GPContext *context);
typedef int (*CameraWaitForEvent)  (Camera *camera, int timeout,
				    CameraEventType *eventtype, void **eventdata,
				    GPContext *context);
/**@}*/


/**
 * \param camera a \ref Camera object
 * \param context a \ref GPContext object
 * \return a gphoto2 error code
 *
 * Implement this function in the camera driver if the camera needs to
 * be initialized before or reset the after each access from
 * libgphoto2.
 *
 * For example, you would probably set the speed to the highest one 
 * right before downloading an image, and reset it to the default speed 
 * afterwards so that other programs will not be affected by this speed
 * change.
 */
typedef int (*CameraPrePostFunc) (Camera *camera, GPContext *context);

/**
 * \brief Various camera specific functions.
 *
 * This structure contains various pointers to functions that apply to
 * the camera itself, and not the filesystem (which is handled by the
 * filesystem functions). Set the ones you want to provide, leave the rest
 * unset.
 *
 * This structure should only used by the driver itself, the frontend
 * should use the gp_camera_xxx wrapper functions for it, who handle
 * opening and locking around those hooks.
 */
typedef struct _CameraFunctions {
	CameraPrePostFunc pre_func;	/**< \brief Function called before each camera operation. */
	CameraPrePostFunc post_func;	/**< \brief Function called after each camera operation. */

	CameraExitFunc exit;		/**< \brief Function called on closing the camera. */

	/* Configuration */
	CameraGetConfigFunc       get_config;	/**< \brief Called for requesting the configuration widgets. */
	CameraSetConfigFunc       set_config;	/**< \brief Called after a configuration was changed */

	CameraListConfigFunc      list_config;	/**< \brief Called for listing the available configuration widgets. */
	CameraGetSingleConfigFunc get_single_config;	/**< \brief Called for requesteing a single widget. */
	CameraSetSingleConfigFunc set_single_config;	/**< \brief Called for setting a single configuration widget. */

	/* Capturing */
	CameraCaptureFunc        capture;	/**< \brief Remote control the camera to capture */
	CameraTriggerCaptureFunc trigger_capture;/**< \brief Remote control the camera to trigger capture */
	CameraCapturePreviewFunc capture_preview;/**< \brief Preview viewfinder content. */

	/* Textual information */
	CameraSummaryFunc summary;		/**< \brief Give a summary about the current camera status, translated. */
	CameraManualFunc  manual;		/**< \brief Give a brief manual about any specific items a user has to know, translated. */
	CameraAboutFunc   about;		/**< \brief A little About text, including authors and credits. */

	/* Event Interface */
	CameraWaitForEvent wait_for_event;	/**< \brief Wait for a specific event from the camera */
	/* Reserved space to use in the future without changing the struct size */
	void *reserved1;			/**< \brief reserved for future use */
	void *reserved2;			/**< \brief reserved for future use */
	void *reserved3;			/**< \brief reserved for future use */
	void *reserved4;			/**< \brief reserved for future use */
	void *reserved5;			/**< \brief reserved for future use */
	void *reserved6;			/**< \brief reserved for future use */
	void *reserved7;			/**< \brief reserved for future use */
	void *reserved8;			/**< \brief reserved for future use */
} CameraFunctions;

typedef struct _CameraPrivateLibrary  CameraPrivateLibrary;
typedef struct _CameraPrivateCore     CameraPrivateCore;

struct _Camera {

	/** \name Those should be accessed only by the camera driver.
	 * @{ */
	GPPort           *port;
	CameraFilesystem *fs;
	CameraFunctions  *functions;
 	/**@}*/

	CameraPrivateLibrary  *pl; /**< Private data of camera libraries.    */
	CameraPrivateCore     *pc; /**< Private data of the core of gphoto2. */
};


/** Create a new camera device. */
int gp_camera_new               (Camera **camera);


/** \name Preparing initialization 
 * @{
 */
int gp_camera_set_abilities     (Camera *camera, CameraAbilities  abilities);
int gp_camera_get_abilities	(Camera *camera, CameraAbilities *abilities);
int gp_camera_set_port_info     (Camera *camera, GPPortInfo  info);
int gp_camera_get_port_info     (Camera *camera, GPPortInfo *info);

/**@}*/


/**
 * \name camera speed
 *
 * You normally don't use that. If you do, you prevent the camera driver
 * from selecting the optimal speed.
 *
 * @{
 */
int gp_camera_set_port_speed    (Camera *camera, int speed);
int gp_camera_get_port_speed    (Camera *camera);

/**@}*/


/** \name Initialization 
 * @{ 
 */
int gp_camera_autodetect 	 (CameraList *list, GPContext *context);
int gp_camera_init               (Camera *camera, GPContext *context);
int gp_camera_exit               (Camera *camera, GPContext *context);

/**@}*/
 


/** \name Operations on cameras 
 * @{ 
 */
int gp_camera_ref   		 (Camera *camera);
int gp_camera_unref 		 (Camera *camera);
int gp_camera_free 		 (Camera *camera);

int gp_camera_get_config	 (Camera *camera, CameraWidget **window,
				  GPContext *context);
int gp_camera_list_config	 (Camera *camera, CameraList *list,
				  GPContext *context);
int gp_camera_get_single_config	 (Camera *camera, const char *name, CameraWidget **widget,
				  GPContext *context);
int gp_camera_set_config	 (Camera *camera, CameraWidget  *window,
				  GPContext *context);
int gp_camera_set_single_config	 (Camera *camera, const char *name, CameraWidget  *widget,
				  GPContext *context);
int gp_camera_get_summary	 (Camera *camera, CameraText *summary,
				  GPContext *context);
int gp_camera_get_manual	 (Camera *camera, CameraText *manual,
				  GPContext *context);
int gp_camera_get_about		 (Camera *camera, CameraText *about,
				  GPContext *context);
int gp_camera_capture 		 (Camera *camera, CameraCaptureType type,
				  CameraFilePath *path, GPContext *context);
int gp_camera_trigger_capture 	 (Camera *camera, GPContext *context);
int gp_camera_capture_preview 	 (Camera *camera, CameraFile *file,
				  GPContext *context);
int gp_camera_wait_for_event     (Camera *camera, int timeout,
		                  CameraEventType *eventtype, void **eventdata,
			          GPContext *context);

int gp_camera_get_storageinfo    (Camera *camera, CameraStorageInformation**,
				   int *, GPContext *context);

/**@}*/


/** \name Operations on folders 
 * @{
 */
int gp_camera_folder_list_files   (Camera *camera, const char *folder, 
				   CameraList *list, GPContext *context);
int gp_camera_folder_list_folders (Camera *camera, const char *folder, 
				   CameraList *list, GPContext *context);
int gp_camera_folder_delete_all   (Camera *camera, const char *folder,
				   GPContext *context);
int gp_camera_folder_put_file     (Camera *camera,
				   const char *folder, const char *filename,
				   CameraFileType type,
				   CameraFile *file, GPContext *context);
int gp_camera_folder_make_dir     (Camera *camera, const char *folder,
				   const char *name, GPContext *context);
int gp_camera_folder_remove_dir   (Camera *camera, const char *folder,
				   const char *name, GPContext *context);
/**@}*/


/** \name Operations on files 
 * @{
 */
int gp_camera_file_get_info 	(Camera *camera, const char *folder, 
				 const char *file, CameraFileInfo *info,
				 GPContext *context);
int gp_camera_file_set_info 	(Camera *camera, const char *folder, 
				 const char *file, CameraFileInfo info,
				 GPContext *context);
int gp_camera_file_get		(Camera *camera, const char *folder, 
				 const char *file, CameraFileType type,
				 CameraFile *camera_file, GPContext *context);
int gp_camera_file_read		(Camera *camera, const char *folder, const char *file,
		    		 CameraFileType type, 
		    		 uint64_t offset, char *buf, uint64_t *size,
		    		 GPContext *context);
int gp_camera_file_delete     	(Camera *camera, const char *folder, 
				 const char *file, GPContext *context);
/**@}*/


/**
 * \name Some cameras need 'keep-alive-messages'. 
 * @{
 */
typedef int          (* CameraTimeoutFunc)      (Camera *camera,
						 GPContext *context);
typedef unsigned int (* CameraTimeoutStartFunc) (Camera *camera,
						 unsigned int timeout,
						 CameraTimeoutFunc func,
						 void *data);
typedef void         (* CameraTimeoutStopFunc)  (Camera *camera,
						 unsigned int id, void *data);
void         gp_camera_set_timeout_funcs (Camera *camera,
				          CameraTimeoutStartFunc start_func,
				          CameraTimeoutStopFunc  stop_func,
				          void *data);
int          gp_camera_start_timeout     (Camera *camera, unsigned int timeout,
					  CameraTimeoutFunc func);
void         gp_camera_stop_timeout      (Camera *camera, unsigned int id);

/**@}*/
#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __GPHOTO2_CAMERA_H__ */

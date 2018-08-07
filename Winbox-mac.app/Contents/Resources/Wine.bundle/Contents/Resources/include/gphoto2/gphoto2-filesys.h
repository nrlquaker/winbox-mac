/** \file
 * \brief Filesystem related operations and declarations.
 *
 * \author Copyright 2000 Scott Fritzinger
 * \author Copyright 2008-2009 Marcus Meissner
 *
 * \note
 * Contributions:
 * 	Lutz Mueller <lutz@users.sf.net> (2001)
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

#ifndef __GPHOTO2_FILESYS_H__
#define __GPHOTO2_FILESYS_H__

#include <time.h>
#include <stdint.h>

#include <gphoto2/gphoto2-context.h>
#include <gphoto2/gphoto2-list.h>
#include <gphoto2/gphoto2-file.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** 
 * \brief Bitmask on what fields are set in the CameraFileInfo structure.
 *
 * Bitmask to mark up which fields are set in the CameraFileInfo
 * structure. The other fields might be uninitialized.
 * If you set information via gp_camera_file_set_info() you 
 * need to set those flags. If you retrieve information via
 * gp_camera_file_get_info() you need to check those flags.
 * They are seperate for both "normal" and "preview" parts
 * and are mostly image related.
 */
typedef enum {
	GP_FILE_INFO_NONE            = 0,	/**< \brief No fields set. */
	GP_FILE_INFO_TYPE            = 1 << 0,	/**< \brief The MIME type is set. */
	GP_FILE_INFO_SIZE            = 1 << 2,	/**< \brief The filesize is set. */
	GP_FILE_INFO_WIDTH           = 1 << 3,	/**< \brief The width is set. */
	GP_FILE_INFO_HEIGHT          = 1 << 4,	/**< \brief The height is set. */
	GP_FILE_INFO_PERMISSIONS     = 1 << 5,	/**< \brief The access permissions are set. */
	GP_FILE_INFO_STATUS	     = 1 << 6,	/**< \brief The status is set (downloaded). */
	GP_FILE_INFO_MTIME	     = 1 << 7,	/**< \brief The modification time is set. */
	GP_FILE_INFO_ALL             = 0xFF	/**< \brief All possible fields set. Internal. */
} CameraFileInfoFields;

/**
 * \brief Bitmask containing the file permission flags.
 *
 * Possible flag values of the permission entry in the file information.
 */
typedef enum {
	GP_FILE_PERM_NONE       = 0,		/**< \brief No permissions. */
	GP_FILE_PERM_READ       = 1 << 0,	/**< \brief Read permissions. */
	GP_FILE_PERM_DELETE     = 1 << 1,	/**< \brief Write permissions */
	GP_FILE_PERM_ALL        = 0xFF		/**< \brief Internal. */
} CameraFilePermissions;

/**
 * \brief Possible status values.
 *
 * Bitmask of possible stati. Currently only download is supported.
 */
typedef enum {
	GP_FILE_STATUS_NOT_DOWNLOADED,	/**< File is not downloaded. */
	GP_FILE_STATUS_DOWNLOADED	/**< File is already downloaded. */
} CameraFileStatus;

/**
 * \brief File information of a regular file.
 *
 * Contains information a regular file with fields being
 * set depending on the bitmask in the fields member.
 */
typedef struct _CameraFileInfoFile {
	CameraFileInfoFields fields;	/**< \brief Bitmask containing the set members. */
	CameraFileStatus status;	/**< \brief Status of the file. */
	uint64_t size;			/**< \brief Size of the file. */
	char type[64];			/**< \brief MIME type of the file. */
	uint32_t width;			/**< \brief Height of the file. */
	uint32_t height;		/**< \brief Width of the file. */
	CameraFilePermissions permissions;/**< \brief Permissions of the file. */
	time_t mtime;			/**< \brief Modification time of the file. */
} CameraFileInfoFile;

/**
 * \brief File information of a preview file.
 *
 * Contains information of a preview file with fields being
 * set depending on the bitmask in the fields member.
 */
typedef struct _CameraFileInfoPreview {
	CameraFileInfoFields fields;	/**< \brief Bitmask containing the set members. */
	CameraFileStatus status;	/**< \brief Status of the preview. */
	uint64_t size;			/**< \brief Size of the preview. */
	char type[64];			/**< \brief MIME type of the preview. */

	uint32_t width;			/**< \brief Width of the preview. */
	uint32_t height;		/**< \brief Height of the preview. */
} CameraFileInfoPreview;

/**
 * \brief File information of an audio file.
 *
 * Contains information of an audio file with fields being
 * set depending on the bitmask in the fields member.
 */
typedef struct _CameraFileInfoAudio {
	CameraFileInfoFields fields;	/**< \brief Bitmask containing the set members. */
	CameraFileStatus status;	/**< \brief Status of the preview file. */
	uint64_t size;		/**< \brief Size of the audio file. */
	char type[64];			/**< \brief MIME type of the audio file. */
} CameraFileInfoAudio;

/** 
 * \brief File information structure.
 *
 * Contains the normal, preview and audio file information structures
 * for a specific file.
 */
typedef struct _CameraFileInfo {
	CameraFileInfoPreview preview;
	CameraFileInfoFile    file;
	CameraFileInfoAudio   audio;
} CameraFileInfo;

/** 
 * \brief Storage information flags.
 *
 * Bitmask to specify which entries of the filesystem
 * storage information is set.
 */
typedef enum {
	GP_STORAGEINFO_BASE		= (1<<0),	/**< \brief The base directory. 
							 * Usually / if just 1 storage is attached.
							 */
	GP_STORAGEINFO_LABEL		= (1<<1),	/**< \brief Label of the filesystem.
							 * Could also be a DOS label.
							 */
	GP_STORAGEINFO_DESCRIPTION	= (1<<2),	/**< \brief More verbose description. */
	GP_STORAGEINFO_ACCESS		= (1<<3),	/**< \brief Access permissions. */
	GP_STORAGEINFO_STORAGETYPE	= (1<<4),	/**< \brief Hardware type. */
	GP_STORAGEINFO_FILESYSTEMTYPE	= (1<<5),	/**< \brief Filesystem type. */
	GP_STORAGEINFO_MAXCAPACITY	= (1<<6),	/**< \brief Maximum capacity in kbytes */
	GP_STORAGEINFO_FREESPACEKBYTES	= (1<<7),	/**< \brief Free space in kbytes. */
	GP_STORAGEINFO_FREESPACEIMAGES	= (1<<8)	/**< \brief Free space in images. */
} CameraStorageInfoFields;

/**
 * \brief Hardware storage types.
 * 
 * Type of hardware this storage is on. The types and values
 * are the same as the PTP standard uses (PTP_ST_xxx).
 */
typedef enum {
	GP_STORAGEINFO_ST_UNKNOWN	= 0,	/**< \brief Unknown storage type. */
	GP_STORAGEINFO_ST_FIXED_ROM	= 1,	/**< \brief A fixed ROM storage. */
	GP_STORAGEINFO_ST_REMOVABLE_ROM	= 2,	/**< \brief A removable ROM storage. */
	GP_STORAGEINFO_ST_FIXED_RAM	= 3,	/**< \brief A fixed RAM storage. (e.g. SDRAM) */
	GP_STORAGEINFO_ST_REMOVABLE_RAM	= 4	/**< \brief A removable RAM storage. (any kind of cards etc) */
} CameraStorageType;

/**
 * \brief Storage access modes.
 * 
 * The modes we can access the storage with. Uses the same
 * types and values as the PTP standard (PTP_AC_xxx).
 */
typedef enum {
	GP_STORAGEINFO_AC_READWRITE		= 0,	/**< \brief Storage is Read / Write. */
	GP_STORAGEINFO_AC_READONLY		= 1,	/**< \brief Storage is Ready Only. */
	GP_STORAGEINFO_AC_READONLY_WITH_DELETE	= 2	/**< \brief Storage is Ready Only, but allows Delete.*/
} CameraStorageAccessType;

/**
 * \brief Filesystem hierarchy types.
 * 
 * The type of the filesystem hierarchy the devices uses.
 * Same types and values as the PTP standard defines (PTP_FST_xxx).
 */
typedef enum {
	GP_STORAGEINFO_FST_UNDEFINED		= 0,	/**< \brief Undefined or unknown filesystem hierarchy. */
	GP_STORAGEINFO_FST_GENERICFLAT		= 1,	/**< \brief Generic flat storage (all in 1 directory). */
	GP_STORAGEINFO_FST_GENERICHIERARCHICAL	= 2,	/**< \brief Generic tree hierarchy. */
	GP_STORAGEINFO_FST_DCF			= 3	/**< \brief DCIM style storage. */
} CameraStorageFilesystemType;

/**
 * \brief Storage information structue.
 *
 * This structure contains the information of a specific camera storage.
 * Only the members as specified by the \a fields member are valid.
 */
typedef struct _CameraStorageInformation {
	CameraStorageInfoFields		fields;	/**< \brief Bitmask of struct members that are specified. */
	char				basedir[256];	/**< \brief Basedirectory of the storage. Will be "/" if just 1 storage on the camera. */
	char				label[256];	/**< \brief Label of the storage. Similar to DOS label. */
	char				description[256];/**< \brief Description of the storage. */
	CameraStorageType		type;		/**< \brief Hardware type of the storage. */
	CameraStorageFilesystemType	fstype;		/**< \brief Hierarchy type of the filesystem. */
	CameraStorageAccessType		access;		/**< \brief Access permissions. */
	uint64_t			capacitykbytes;	/**< \brief Total capacity in kbytes. */
	uint64_t			freekbytes;	/**< \brief Free space in kbytes. */
	uint64_t			freeimages;	/**< \brief Free space in images (guessed by camera). */
} CameraStorageInformation;

/** 
 * \brief Filesystem structure, only exposed to camera drivers.
 *
 * Internal structure, contents not exposed to frontends. Camera
 * drivers get these passed to filesystem related functions and
 * are supposed to use it only via the accessor functions.
 */
typedef struct _CameraFilesystem CameraFilesystem;

int gp_filesystem_new	 (CameraFilesystem **fs);
int gp_filesystem_free	 (CameraFilesystem *fs);

/* Manual editing */
int gp_filesystem_append           (CameraFilesystem *fs, const char *folder,
			            const char *filename, GPContext *context);
int gp_filesystem_set_info_noop    (CameraFilesystem *fs,
				    const char *folder, const char *filename,
				    CameraFileInfo info, GPContext *context);
int gp_filesystem_set_file_noop    (CameraFilesystem *fs,
				    const char *folder, const char *filename,
				    CameraFileType type,
				    CameraFile *file, GPContext *context);
int gp_filesystem_delete_file_noop (CameraFilesystem *fs, const char *folder,
				    const char *filename, GPContext *context);
int gp_filesystem_reset            (CameraFilesystem *fs);

/* Information retrieval */
int gp_filesystem_count	       (CameraFilesystem *fs, const char *folder,
				GPContext *context);
int gp_filesystem_name         (CameraFilesystem *fs, const char *folder,
			        int filenumber, const char **filename,
				GPContext *context);
int gp_filesystem_get_folder   (CameraFilesystem *fs, const char *filename,
			        char **folder, GPContext *context);
int gp_filesystem_number       (CameraFilesystem *fs, const char *folder,
				const char *filename, GPContext *context);

/* Listings */
typedef int (*CameraFilesystemListFunc) (CameraFilesystem *fs,
					 const char *folder, CameraList *list,
					 void *data, GPContext *context);
int gp_filesystem_list_files     (CameraFilesystem *fs, const char *folder,
				  CameraList *list, GPContext *context);
int gp_filesystem_list_folders   (CameraFilesystem *fs, const char *folder,
				  CameraList *list, GPContext *context);

/* File information */
typedef int (*CameraFilesystemSetInfoFunc) (CameraFilesystem *fs,
					    const char *folder,
					    const char *filename,
					    CameraFileInfo info, void *data,
					    GPContext *context);
typedef int (*CameraFilesystemGetInfoFunc) (CameraFilesystem *fs,
					    const char *folder,
					    const char *filename,
					    CameraFileInfo *info, void *data,
					    GPContext *context);
int gp_filesystem_get_info       (CameraFilesystem *fs, const char *folder,
				  const char *filename, CameraFileInfo *info,
				  GPContext *context);
int gp_filesystem_set_info       (CameraFilesystem *fs, const char *folder,
				  const char *filename, CameraFileInfo info,
				  GPContext *context);

/* Files */
typedef int (*CameraFilesystemGetFileFunc)    (CameraFilesystem *fs,
					       const char *folder,
					       const char *filename,
					       CameraFileType type,
					       CameraFile *file, void *data,
					       GPContext *context);
typedef int (*CameraFilesystemReadFileFunc)    (CameraFilesystem *fs,
					       const char *folder,
					       const char *filename,
					       CameraFileType type,
					       uint64_t offset,
					       char *buf,
					       uint64_t *size,
					       void *data,
					       GPContext *context);
typedef int (*CameraFilesystemDeleteFileFunc) (CameraFilesystem *fs,
					       const char *folder,
					       const char *filename,
					       void *data, GPContext *context);
int gp_filesystem_get_file       (CameraFilesystem *fs, const char *folder,
				  const char *filename, CameraFileType type,
				  CameraFile *file, GPContext *context);
int gp_filesystem_read_file	(CameraFilesystem *fs, const char *folder,
				 const char *filename, CameraFileType type,
				 uint64_t offset, char *buf, uint64_t *size,
				 GPContext *context);
int gp_filesystem_delete_file    (CameraFilesystem *fs, const char *folder,
				  const char *filename, GPContext *context);

/* Folders */
typedef int (*CameraFilesystemPutFileFunc)   (CameraFilesystem *fs,
					      const char *folder,
					      const char *filename,
					      CameraFileType type,
					      CameraFile *file,
					      void *data,
					      GPContext *context);
typedef int (*CameraFilesystemDeleteAllFunc) (CameraFilesystem *fs,
					      const char *folder, void *data,
					      GPContext *context);
typedef int (*CameraFilesystemDirFunc)       (CameraFilesystem *fs,
					      const char *folder,
					      const char *name, void *data,
					      GPContext *context);

typedef int (*CameraFilesystemStorageInfoFunc) (CameraFilesystem *fs,
					      CameraStorageInformation **,
					      int *nrofstorageinformations,
					      void *data, GPContext *context);

int gp_filesystem_get_storageinfo (CameraFilesystem *fs,
				   CameraStorageInformation **,
				   int *nrofstorageinformations,
				   GPContext *context);

typedef struct _CameraFilesystemFuncs CameraFilesystemFuncs;
struct _CameraFilesystemFuncs {
	CameraFilesystemListFunc	file_list_func;
	CameraFilesystemListFunc	folder_list_func;
	CameraFilesystemPutFileFunc	put_file_func;
	CameraFilesystemDeleteAllFunc	delete_all_func;
	CameraFilesystemGetInfoFunc	get_info_func;
	CameraFilesystemSetInfoFunc	set_info_func;
	CameraFilesystemDirFunc		make_dir_func;
	CameraFilesystemDirFunc		remove_dir_func;
	CameraFilesystemGetFileFunc	get_file_func;
	CameraFilesystemReadFileFunc	read_file_func;
	CameraFilesystemDeleteFileFunc	del_file_func;
	CameraFilesystemStorageInfoFunc	storage_info_func;

	/* for later use. Remove one if you add a new function */
	void				*unused[31];
};
int gp_filesystem_set_funcs	(CameraFilesystem *fs,
				 CameraFilesystemFuncs *funcs,
				 void *data);
int gp_filesystem_put_file   (CameraFilesystem *fs, const char *folder, const char *filename,
			      CameraFileType type, CameraFile *file, GPContext *context);
int gp_filesystem_delete_all (CameraFilesystem *fs, const char *folder,
			      GPContext *context);
int gp_filesystem_make_dir   (CameraFilesystem *fs, const char *folder,
			      const char *name, GPContext *context);
int gp_filesystem_remove_dir (CameraFilesystem *fs, const char *folder,
			      const char *name, GPContext *context);

/* For debugging */
int gp_filesystem_dump         (CameraFilesystem *fs);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __GPHOTO2_FILESYS_H__ */

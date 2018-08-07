/** \file
 * \brief Abstracted gphoto2 file operations.
 *
 * \author Copyright 2000 Scott Fritzinger
 * \author Copyright 2008-2009 Marcus Meissner
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

#ifndef __GPHOTO2_FILE_H__
#define __GPHOTO2_FILE_H__

#include <time.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define GP_MIME_TXT       "text/plain"
#define GP_MIME_WAV       "audio/wav"
#define GP_MIME_RAW       "image/x-raw"
#define GP_MIME_PNG       "image/png"
#define GP_MIME_PGM       "image/x-portable-graymap"
#define GP_MIME_PPM       "image/x-portable-pixmap"
#define GP_MIME_PNM       "image/x-portable-anymap"
#define GP_MIME_JPEG      "image/jpeg"
#define GP_MIME_TIFF      "image/tiff"
#define GP_MIME_BMP       "image/bmp"
#define GP_MIME_QUICKTIME "video/quicktime"
#define GP_MIME_AVI       "video/x-msvideo"
#define GP_MIME_CRW       "image/x-canon-raw"
#define GP_MIME_CR2       "image/x-canon-cr2"
#define GP_MIME_NEF       "image/x-nikon-nef"
#define GP_MIME_UNKNOWN   "application/octet-stream"
#define GP_MIME_EXIF      "application/x-exif"
#define GP_MIME_MP3       "audio/mpeg"
#define GP_MIME_OGG       "application/ogg"
#define GP_MIME_WMA       "audio/x-wma"
#define GP_MIME_ASF       "audio/x-asf"
#define GP_MIME_MPEG      "video/mpeg"
#define GP_MIME_AVCHD     "video/mp2t"
#define GP_MIME_RW2       "image/x-panasonic-raw2"
#define GP_MIME_ARW       "image/x-sony-arw"

/**
 * \brief The type of view on the specified file.
 *
 * Specifies the file of the current file, usually passed
 * to the gp_camera_file_get() and gp_camera_file_put()
 * functions. This is useful for multiple views of one
 * file, like that an single image file has "raw", "normal",
 * "exif" and "preview" views, or a media file has "normal"
 * and "metadata" file views.
 */
typedef enum {
	GP_FILE_TYPE_PREVIEW,	/**< A preview of an image. */
	GP_FILE_TYPE_NORMAL,	/**< The regular normal data of a file. */
	GP_FILE_TYPE_RAW,	/**< The raw mode of a file, for instance the raw bayer data for cameras
				 * where postprocessing is done in the driver. The RAW files of modern
				 * DSLRs are GP_FILE_TYPE_NORMAL usually. */
	GP_FILE_TYPE_AUDIO,	/**< The audio view of a file. Perhaps an embedded comment or similar. */
	GP_FILE_TYPE_EXIF,	/**< The embedded EXIF data of an image. */
	GP_FILE_TYPE_METADATA	/**< The metadata of a file, like Metadata of files on MTP devices. */
} CameraFileType;

/**
 * \brief File storage type.
 *
 * The file storage type. Only used internally for now, but might
 * be exposed later on. See gp_file_new() and gp_file_new_from_fd().
 */
typedef enum {
	GP_FILE_ACCESSTYPE_MEMORY,	/**< File is in system memory. */
	GP_FILE_ACCESSTYPE_FD,		/**< File is associated with a UNIX filedescriptor. */
	GP_FILE_ACCESSTYPE_HANDLER	/**< File is associated with a programmatic handler. */
} CameraFileAccessType;

/* FIXME: api might be unstable. function return gphoto results codes. */
typedef struct _CameraFileHandler {
	int (*size) (void*priv, uint64_t *size); /* only for read? */
	int (*read) (void*priv, unsigned char *data, uint64_t *len);
	int (*write) (void*priv, unsigned char *data, uint64_t *len);
	/* FIXME: should we have both read/write methods? */
	/* FIXME: how to finish method, due to LRU it might be longlived. */
} CameraFileHandler;

/*! \struct CameraFile
 * \brief File structure.
 *
 * The internals of the CameraFile struct are private, please use
 * the accessor functions.
 */
typedef struct _CameraFile CameraFile;

int gp_file_new            (CameraFile **file);
int gp_file_new_from_fd    (CameraFile **file, int fd);
int gp_file_new_from_handler (CameraFile **file, CameraFileHandler *handler, void*priv);
int gp_file_ref            (CameraFile *file);
int gp_file_unref          (CameraFile *file);
int gp_file_free           (CameraFile *file);

int gp_file_set_name       (CameraFile *file, const char  *name);
int gp_file_get_name       (CameraFile *file, const char **name);

int gp_file_set_mime_type  (CameraFile *file, const char  *mime_type);
int gp_file_get_mime_type  (CameraFile *file, const char **mime_type);

int gp_file_set_mtime   (CameraFile *file, time_t  mtime);
int gp_file_get_mtime   (CameraFile *file, time_t *mtime);

int gp_file_detect_mime_type          (CameraFile *file);
int gp_file_adjust_name_for_mime_type (CameraFile *file);
int gp_file_get_name_by_type (CameraFile *file, const char *basename, CameraFileType type, char **newname);

int gp_file_set_data_and_size (CameraFile*,       char *data,
			       unsigned long int size);
int gp_file_get_data_and_size (CameraFile*, const char **data,
			       unsigned long int *size);
/* "Do not use those"
 *
 * These functions probably were originally intended for internal use only.
 * However, due to
 *   - the lack of good documentation
 *   - this being the obvious way to save a file
 *   - the fact that libgphoto2 has been exporting all its internal
 *     symbols for years (until 2005-06)
 *   - our in-house frontends gphoto2 and gtkam using them
 * a number of external frontends started to use these functions, as
 * of 2005-06:
 *    - digikam
 *    - f-spot
 *    - gthumb
 * But a few frontends can live without it (and thus are likely to
 * use the correct API):
 *    - flphoto
 *    - kamera
 *
 * So we're going to phase these functions out over the next year or
 * so, going the GTK way of keeping the ABI but breaking the API. So
 * we'll continue to export functionally equivalent functions, but the
 * header files will not contain definitions for you to use any more.
 */
int gp_file_open           (CameraFile *file, const char *filename);
int gp_file_save           (CameraFile *file, const char *filename);
int gp_file_clean          (CameraFile *file);
int gp_file_copy           (CameraFile *destination, CameraFile *source);


/* These are for use by camera drivers only */
int gp_file_append            (CameraFile*, const char *data,
			       unsigned long int size);
int gp_file_slurp             (CameraFile*, char *data,
			       size_t size, size_t *readlen);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __GPHOTO2_FILE_H__ */

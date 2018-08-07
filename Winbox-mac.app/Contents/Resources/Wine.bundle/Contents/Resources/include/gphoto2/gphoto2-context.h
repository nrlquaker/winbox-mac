/** \file 
 * \brief Context callback operation functions.
 *
 * \author Copyright 2001 Lutz Mueller <lutz@users.sourceforge.net>
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

#ifndef __GPHOTO2_CONTEXT_H__
#define __GPHOTO2_CONTEXT_H__

#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * \brief The gphoto context structure.
 *
 * This structure allows callback handling, passing error contexts back, 
 * progress handling and download cancellation and similar things.
 * It is usually passed around the functions.
 */
typedef struct _GPContext GPContext;

GPContext *gp_context_new (void);

void gp_context_ref   (GPContext *context);
void gp_context_unref (GPContext *context);

/**
 * \brief Return codes that can be returned by progress handling.
 *
 * An application can return special values back to the libgphoto2
 * progress callback handling functions. If "Cancel" is selected,
 * libgphoto2 and the camera driver will try to cancel transfer.
 */
typedef enum _GPContextFeedback {
	GP_CONTEXT_FEEDBACK_OK,		/**< Everything ok... proceed. */
	GP_CONTEXT_FEEDBACK_CANCEL	/**< Please cancel the current transfer if possible. */
} GPContextFeedback;

/* Functions */
typedef void (* GPContextIdleFunc)     (GPContext *context, void *data);
typedef void (* GPContextErrorFunc)    (GPContext *context, const char *text, void *data);
typedef void (* GPContextStatusFunc)   (GPContext *context, const char *text, void *data);
typedef void (* GPContextMessageFunc)  (GPContext *context, const char *text, void *data);
typedef GPContextFeedback (* GPContextQuestionFunc) (GPContext *context,
						     const char *text, void *data);
typedef GPContextFeedback (* GPContextCancelFunc)   (GPContext *context,
						     void *data);
typedef unsigned int (* GPContextProgressStartFunc)  (GPContext *context,
						      float target,
						      const char *text,
						      void *data);
typedef void         (* GPContextProgressUpdateFunc) (GPContext *context,
						      unsigned int id,
						      float current,
						      void *data);
typedef void         (* GPContextProgressStopFunc)   (GPContext *context,
						      unsigned int id,
						      void *data);

/* Setting those functions (frontends) */
void gp_context_set_idle_func      (GPContext *context,
			            GPContextIdleFunc func,     void *data);
void gp_context_set_progress_funcs (GPContext *context,
				    GPContextProgressStartFunc  start_func,
				    GPContextProgressUpdateFunc update_func,
				    GPContextProgressStopFunc   stop_func,
				    void *data);
void gp_context_set_error_func     (GPContext *context,
				    GPContextErrorFunc func,    void *data);
void gp_context_set_status_func    (GPContext *context,
				    GPContextStatusFunc func,   void *data);
void gp_context_set_question_func  (GPContext *context,
				    GPContextQuestionFunc func, void *data);
void gp_context_set_cancel_func    (GPContext *context,
				    GPContextCancelFunc func,   void *data);
void gp_context_set_message_func   (GPContext *context,
				    GPContextMessageFunc func,  void *data);

/* Calling those functions (backends) */
void gp_context_idle     (GPContext *context);
void gp_context_error    (GPContext *context, const char *format, ...)
#ifdef __GNUC__
	__attribute__((__format__(printf,2,3)))
#endif
;
void gp_context_status   (GPContext *context, const char *format, ...)
#ifdef __GNUC__
	__attribute__((__format__(printf,2,3)))
#endif
;
void gp_context_message  (GPContext *context, const char *format, ...)
#ifdef __GNUC__
	__attribute__((__format__(printf,2,3)))
#endif
;
GPContextFeedback gp_context_question (GPContext *context, const char *format,
				       ...)
#ifdef __GNUC__
	__attribute__((__format__(printf,2,3)))
#endif
;
GPContextFeedback gp_context_cancel   (GPContext *context);
unsigned int gp_context_progress_start  (GPContext *context, float target,
					 const char *format, ...)
#ifdef __GNUC__
	__attribute__((__format__(printf,3,4)))
#endif
;
void         gp_context_progress_update (GPContext *context, unsigned int id,
					 float current);
void         gp_context_progress_stop   (GPContext *context, unsigned int id);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __GPHOTO2_CONTEXT_H__ */

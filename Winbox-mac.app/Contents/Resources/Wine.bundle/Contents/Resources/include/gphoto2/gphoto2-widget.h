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

#ifndef __GPHOTO2_WIDGET_H__
#define __GPHOTO2_WIDGET_H__

#include <gphoto2/gphoto2-context.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** \brief internal structure please use the accessors. */
typedef struct _CameraWidget CameraWidget;

#ifdef __cplusplus
}
#endif /* __cplusplus */



#include <gphoto2/gphoto2-camera.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * \brief Type of the widget to be created.
 *
 * The actual widget type we want to create. The type of the value
 * it supports depends on this type.
 */
typedef enum {									/* Value (get/set):	*/
	GP_WIDGET_WINDOW,	/**< \brief Window widget
				 *   This is the toplevel configuration widget. It should likely contain multiple #GP_WIDGET_SECTION entries.
				 */
	GP_WIDGET_SECTION,	/**< \brief Section widget (think Tab) */
	GP_WIDGET_TEXT,		/**< \brief Text widget. */			/* char *		*/
	GP_WIDGET_RANGE,	/**< \brief Slider widget. */			/* float		*/
	GP_WIDGET_TOGGLE,	/**< \brief Toggle widget (think check box) */	/* int			*/
	GP_WIDGET_RADIO,	/**< \brief Radio button widget. */		/* char *		*/
	GP_WIDGET_MENU,		/**< \brief Menu widget (same as RADIO). */	/* char *		*/
	GP_WIDGET_BUTTON,	/**< \brief Button press widget. */		/* CameraWidgetCallback */
	GP_WIDGET_DATE		/**< \brief Date entering widget. */		/* int			*/
} CameraWidgetType;

/**
 * \brief Callback handler for Button widgets.
 */
typedef int (* CameraWidgetCallback) (Camera *, CameraWidget *, GPContext *);

int 	gp_widget_new 	(CameraWidgetType type, const char *label, 
		         CameraWidget **widget);
int    	gp_widget_free 	(CameraWidget *widget);
int     gp_widget_ref   (CameraWidget *widget);
int     gp_widget_unref (CameraWidget *widget);

int	gp_widget_append	(CameraWidget *widget, CameraWidget *child);
int 	gp_widget_prepend	(CameraWidget *widget, CameraWidget *child);

int 	gp_widget_count_children     (CameraWidget *widget);
int	gp_widget_get_child	     (CameraWidget *widget, int child_number, 
				      CameraWidget **child);

/* Retrieve Widgets */
int	gp_widget_get_child_by_label (CameraWidget *widget,
				      const char *label,
				      CameraWidget **child);
int	gp_widget_get_child_by_id    (CameraWidget *widget, int id, 
				      CameraWidget **child);
int	gp_widget_get_child_by_name  (CameraWidget *widget,
                                      const char *name,
				      CameraWidget **child);
int	gp_widget_get_root           (CameraWidget *widget,
                                      CameraWidget **root);
int     gp_widget_get_parent         (CameraWidget *widget,
				      CameraWidget **parent);

int	gp_widget_set_value     (CameraWidget *widget, const void *value);
int	gp_widget_get_value     (CameraWidget *widget, void *value);

int     gp_widget_set_name      (CameraWidget *widget, const char  *name);
int     gp_widget_get_name      (CameraWidget *widget, const char **name);

int	gp_widget_set_info      (CameraWidget *widget, const char  *info);
int	gp_widget_get_info      (CameraWidget *widget, const char **info);

int	gp_widget_get_id	(CameraWidget *widget, int *id);
int	gp_widget_get_type	(CameraWidget *widget, CameraWidgetType *type);
int	gp_widget_get_label	(CameraWidget *widget, const char **label);

int	gp_widget_set_range	(CameraWidget *range, 
				 float  low, float  high, float  increment);
int	gp_widget_get_range	(CameraWidget *range, 
				 float *min, float *max, float *increment);

int	gp_widget_add_choice     (CameraWidget *widget, const char *choice);
int	gp_widget_count_choices  (CameraWidget *widget);
int	gp_widget_get_choice     (CameraWidget *widget, int choice_number, 
                                  const char **choice);

int	gp_widget_changed        (CameraWidget *widget);
int     gp_widget_set_changed    (CameraWidget *widget, int changed);

int     gp_widget_set_readonly   (CameraWidget *widget, int readonly);
int     gp_widget_get_readonly   (CameraWidget *widget, int *readonly);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __GPHOTO2_WIDGET_H__ */

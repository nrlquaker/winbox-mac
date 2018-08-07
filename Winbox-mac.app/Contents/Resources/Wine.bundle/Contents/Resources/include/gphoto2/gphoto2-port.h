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

#ifndef __GPHOTO2_PORT_H__
#define __GPHOTO2_PORT_H__

#include <gphoto2/gphoto2-port-info-list.h>

/* For portability */
#include <gphoto2/gphoto2-port-portability.h>
#ifdef OS2
#include <gphoto2/gphoto2-port-portability-os2.h>
#include <os2.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef TRUE
#define TRUE (0==0)
#endif

#ifndef FALSE
#define FALSE (1==0)
#endif

/**
 * \brief Serial parity
 * 
 * Parity of the serial port.
 */
typedef enum _GPPortSerialParity
{
    GP_PORT_SERIAL_PARITY_OFF = 0,	/**< \brief Parity is off (disabled) */
    GP_PORT_SERIAL_PARITY_EVEN,		/**< \brief Parity is even. */
    GP_PORT_SERIAL_PARITY_ODD		/**< \brief Parity is odd. */
} GPPortSerialParity;

/** \brief Maximum length of receive buffer */
#define GP_PORT_MAX_BUF_LEN 4096             

/**
 * \brief Port settings for serial ports.
 */
typedef struct _GPPortSettingsSerial {
	char port[128];		/**< The portname (/dev/ttyX)*/
	int speed;		/**< The baudrate of the device. */
	int bits;		/**< How many bits data. */
	GPPortSerialParity parity;	/**< parity data, see GP_PORT_SERIAL_PARITY_ 
				  defines */
	int stopbits;		/**< How many stop bits are used. */
} GPPortSettingsSerial;

/**
 * \brief Port settings for USB ports.
 */
typedef struct _GPPortSettingsUSB {
	int inep;		/**< \brief Bulk IN endpoint used. */
	int outep;		/**< \brief Bulk OUT endpoint used. */
	int intep;		/**< \brief Interrupt endpoint used. */
	int config;		/**< \brief USB bConfigurationValue used. */
	int interface;		/**< \brief USB Interface number used. */
	int altsetting;		/**< \brief USB Alternative Setting used. */

	int maxpacketsize;	/**< \brief Maximum USB packetsize of the IN endpoint. (r/o) */

	/* must be last to avoid binary incompatibility.
	 * luckily we just need to make sure this struct does not 
	 * get larger than _GPPortSettingsSerial. */
	char port[64];		/**< \brief USB Portname. Specific to lowlevel USB. */
} GPPortSettingsUSB;

/**
 * \brief Port settings for USB mass storage direct IO ports.
 */
typedef struct _GPPortSettingsUsbDiskDirect {
	char path[128];		/**< /brief The ports device node path (/dev/sdX)*/
} GPPortSettingsUsbDiskDirect;

/**
 * \brief Port settings for USB Mass Storage raw SCSI ports.
 */
typedef struct _GPPortSettingsUsbScsi {
	char path[128];		/**< /brief The ports device node path (/dev/sg#)*/
} GPPortSettingsUsbScsi;

/**
 * \brief Union of port settings.
 *
 * This contains a shared union of possible settings for ports needing
 * them.
 */
typedef union _GPPortSettings {
	GPPortSettingsSerial serial;	/**< \brief Serial specific settings */
	GPPortSettingsUSB usb;		/**< \brief USB specific settings */
	GPPortSettingsUsbDiskDirect usbdiskdirect; /**< \brief usb disk direct port specific settings */
	GPPortSettingsUsbScsi usbscsi;	/**< \brief usb scsi port specific settings */
} GPPortSettings;

enum {
        GP_PORT_USB_ENDPOINT_IN,	/**< \brief USB bulk IN ep */
        GP_PORT_USB_ENDPOINT_OUT,	/**< \brief USB bulk OUT ep */
        GP_PORT_USB_ENDPOINT_INT	/**< \brief USB Interrupt ep */
};

typedef struct _GPPortPrivateLibrary GPPortPrivateLibrary;
typedef struct _GPPortPrivateCore    GPPortPrivateCore;

/**
 * \brief The GPhoto port structure.
 *
 * This structure tracks the physical connection of the device.
 * It can correspond the various methods of lowlevel access, serial
 * usb and others and abstracts them as much as possible.
 *
 * Frontends should consider this structure opaque and only use accessor
 * functions.
 *
 * Camera drivers should only access the type and pl members directly,
 * and use accessor functions for the rest.
 */
typedef struct _GPPort {
	/* For your convenience */
	GPPortType type;		/**< \brief Actual type of this port */

 	GPPortSettings settings;	/**< \brief Current port settings. */
        GPPortSettings settings_pending;/**< \brief Settings to be committed. */

        int timeout; 			/**< \brief Port timeout in milliseconds. */

	GPPortPrivateLibrary *pl;	/**< \brief Camera driver private data pointer. */
	GPPortPrivateCore    *pc;	/**< \brief Port library private data pointer. */
} GPPort;

int gp_port_new         (GPPort **port);
int gp_port_free        (GPPort *port);

int gp_port_set_info    (GPPort *port, GPPortInfo info);
int gp_port_get_info    (GPPort *port, GPPortInfo *info);

int gp_port_open        (GPPort *port);
int gp_port_close       (GPPort *port);

int gp_port_reset       (GPPort *port);

int gp_port_write       (GPPort *port, const char *data, int size);
int gp_port_read        (GPPort *port,       char *data, int size);
int gp_port_check_int   (GPPort *port,       char *data, int size);
int gp_port_check_int_fast (GPPort *port,    char *data, int size);

int gp_port_get_timeout  (GPPort *port, int *timeout);
int gp_port_set_timeout  (GPPort *port, int  timeout);

int gp_port_set_settings (GPPort *port, GPPortSettings  settings);
int gp_port_get_settings (GPPort *port, GPPortSettings *settings);

/**
 * \brief Serial pins.
 * 
 * A number of serial pins to trigger and pull. This is necessary
 * for some devices that have more than just the regular 3 or 4 wires.
 */
typedef enum _GPPin {
	GP_PIN_RTS,	/**< \brief RTS line */
	GP_PIN_DTR,	/**< \brief DTR line */
	GP_PIN_CTS,	/**< \brief CTS line */
	GP_PIN_DSR,	/**< \brief DSR line */
	GP_PIN_CD,	/**< \brief Carrier Detect line */
	GP_PIN_RING	/**< \brief RING (Modem) line */
} GPPin;

/**
 * \brief Level to pull specific lines.
 * 
 * The level on which to pull some of the serial lines.
 */
typedef enum _GPLevel {
	GP_LEVEL_LOW  = 0,	/**< \brief Pull to low (0V) */
	GP_LEVEL_HIGH = 1	/**< \brief Pull to high (nV) */
} GPLevel;

int gp_port_get_pin   (GPPort *port, GPPin pin, GPLevel *level);
int gp_port_set_pin   (GPPort *port, GPPin pin, GPLevel level);

int gp_port_send_break (GPPort *port, int duration);
int gp_port_flush      (GPPort *port, int direction);

int gp_port_usb_find_device (GPPort *port, int idvendor, int idproduct);
int gp_port_usb_find_device_by_class (GPPort *port, int mainclass, int subclass, int protocol);
int gp_port_usb_clear_halt  (GPPort *port, int ep);
int gp_port_usb_msg_write   (GPPort *port, int request, int value,
			     int index, char *bytes, int size);
int gp_port_usb_msg_read    (GPPort *port, int request, int value,
			     int index, char *bytes, int size);
int gp_port_usb_msg_interface_write    (GPPort *port, int request, 
			    int value, int index, char *bytes, int size);
int gp_port_usb_msg_interface_read    (GPPort *port, int request, 
			    int value, int index, char *bytes, int size);
int gp_port_usb_msg_class_write    (GPPort *port, int request, 
			    int value, int index, char *bytes, int size);
int gp_port_usb_msg_class_read    (GPPort *port, int request, 
			    int value, int index, char *bytes, int size);

int gp_port_seek (GPPort *port, int offset, int whence);

int gp_port_send_scsi_cmd (GPPort *port, int to_dev,
				char *cmd, int cmd_size,
				char *sense, int sense_size,
				char *data, int data_size);

/* Error reporting */
int         gp_port_set_error (GPPort *port, const char *format, ...)
#ifdef __GNUC__
	__attribute__((__format__(printf,2,3)))
#endif
;
const char *gp_port_get_error (GPPort *port);

/* DEPRECATED */
/** \deprecated internal typedef */
typedef GPPort gp_port;
/** \deprecated internal typedef */
typedef GPPortSettings gp_port_settings;
/** \deprecated internal define */
#define PIN_CTS GP_PIN_CTS

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __GPHOTO2_PORT_H__ */

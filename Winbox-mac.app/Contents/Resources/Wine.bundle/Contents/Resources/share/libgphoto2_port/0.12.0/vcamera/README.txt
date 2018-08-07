This is a virtual PTP camera embedded in a USB port driver.

It is meant for libgphoto2 test purposes.

If you are seeing this file on a regular system, you likely
did not build any other USB driver.

In that case you should probably install libusb development headers
and libraries and recompile.

If you want to use it, copy JPG and other files into the directory
of this README (standard location is: /usr/share/libgphoto2_port/<version>/ )

Special functions:

Doing an image capture will duplicate an existing JPEG and report it as
being captured.

Doing a deletion is virtual and does not affect the filesystem content.

PTP Opcode 0x9999 can be used to emit PTP Events
First argment is the type, second argument is the delay of the interrupt in 1/1000 seconds

	0x0	objectadded		- will use a random existing jpg and virtually duplicate it
	0x1	objectremoved		- will virtually delete the first existing jpg it finds
	0x2	capturecompleted	- emits a capturecompleted event

Author: Marcus Meissner <marcus@jet.franken.de>

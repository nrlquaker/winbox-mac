# Winbox changelog

## 3.24

What's new in v3.24:

- fixed WinBox crash when viewing firewall rule with src/dst-address-type configured;
- fixed checkbox group disabled state inheritance;
- fixed dates and times in interface link up/down properties (RouterOS v6.47 required);
- fixed system comment message display;
- fixed vertical font alignment in optional fields;
- fixed window size inheritance from the previous session;
- keep advanced and simple mode table settings separately;
- make WinBox upgrade work with wine 5.0 or newer;
- properly show popup windows on top.

## 3.23

- added support for Ctrl+C and Ctrl+A shortcuts in read-only fields;
- always use fixed width font in terminal window;
- do not resize inner windows when main window is resized;
- fixed default configuration approval window disappearing when using "Show Script" button;
- fixed main window size saving between sessions;
- improved large table loading speed in RouterOS v7.

## 3.22

- added 24x24 and 32x32 icon support (RouterOS v6.47 required);
- added Legacy Mode (disabled by default) to allow using older, less secure connections to RouterOS older than v6.43;
- added scroll bar support in item property windows;
- added support for super low DPI - 72, accessible by Zoom Out;
- fixed Log window drawing on HiDPI displays;
- fixed Zoom In/Zoom Out setting persistence after window is closed;
- made table row height 15px by default;
- use monospace font for big pop-up messages.

## 3.21

- added support for HiDPI displays;
- download WinBox specific files from router only into AppData folder and not anywhere else (CVE-2020-5720);
- enabled Drag and Drop support on 64-bit WinBox in Wine;
- font size can be increased/decreased under "Settings/Zoom In" or "Zoom Out";
- improved MikroTik signature checking on WinBox update.

## 3.20

- allow to filter by IPv6 addresses and prefixes;
- build 64-bit Winbox as well (https://mikrotik.com/download);
- do not leave files locked on computer when uploading files to router;
- fixed problem where some fields were not shown for read only users;
- fixed Winbox crash when copying multiple files between routers;
- make Ctrl+A work in script fields and other multiline fields;
- make DLL hijacking attack not work: Winbox will not look at the directory it resides in, when looking for system DLLs;
- on update, Winbox will check that code is signed by MikroTik and not somebody else;
- removed Drag and Drop support on 64-bit Winbox in Wine;
- show system note at login.

## 3.19

- fixed problem where Winbox could not login into RouterOS v6.45 (or later) router;
- fixed DHCP lease sorting by "last seen" column.

## 3.18

- fixed problem where winbox could not login in RouterOS v6.43 router for some users.

## 3.17

- fixed sudden disconnects from router (introduced in v3.15).

## 3.16

- added back support for connecting to older RouterOS v6 versions;
- fixed crash when connecting to newest RouterOS on MacOS wine.

## 3.15

- fixed problem where connecting through RoMON agent with incomplete package set not all menus were available on the target router;
- fixed arrow keys in table filter fields;
- when connected to romon agent mark session as romon one.

## 3.14

- added support for new style authentication and encryption for connections to RouterOS v6.43;
- make all connections in secure mode (all data is encrypted with AES128-CBC-SHA);
- make winbox self upgrade check .exe signature;
- make up/down keys select previous/next entry in address/neighbors list in connect window while login name or password fields are in focus;
- make mouse wheel work anywere in connect window if login or password fields are in focus;
- remember Romon Neighbours Table column widths;
- fixed problem where selected table items were moved to the top if the table filters dropdown button was clicked twice.

## 3.13

- abandoned support for connecting to older RouterOS versions (older than v6), no DLLs will ever be downloaded;
- winbox.exe is now signed executable.

## 3.12

- added new menu entry - "Export Without Passwords";
- make Enter start filtering in Connect window if some of the filters are changed instead of connecting to router;
- do not keep old passwords if user unselected Keep-Password later;
- make file copy & paste work between routers again;
- make Enter key activate Connect if one of connect fields were active even when master password field has not been entered yet;
- fixed Reconnect in RoMON mode with "Open In New Window" enabled;
- other fixes.
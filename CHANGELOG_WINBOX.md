# Winbox changelog

# 3.39

- added support for QR code field.

## 3.38

- fixed connecting to wireless network from QuickSet when there was no password specified;
- fixed date and time value representation in the User Manager;
- fixed skin file reading.

## 3.37

- do not update interface window layout all the time;
- do not send value for empty multi-option field;
- fixed VPLS "cisco-id" field with "&" prefix (introduced v3.36);
- fixed ability to set options that can be hidden;
- fixed floating point field's negative value in `-0.***` format.

## 3.36

- fix issue with non existing records still in winbox ros7;
- fix Graphing and Quickset graphs;
- fix neighbour table filter "all" storage if other was stored previously;
- fix filter combobox saving/restoring;
- fix wifiwave2 Frequency field;
- show error if file upload not enough space;
- fix some vpls fields with required "&" prefix;
- fix sent default value for disabled wireless EAP Methods field;
- do not set some firewall fields by not sending their values when hidden;
- fix managed list category grouping when value is ip with port;
- do not dump connection info to stdout when disconnected;
- fix some field update if it was changed and disabled;
- fix menu missing icon if some submenus are hidden in skin;
- fix skin for Add button with dropdown.

## 3.35

- fixed F4 and F7 keys in Terminal;
- fixed automatic reconnect issues for RoMON;
- fixed crash when connecting in new window (introduced in v3.33);
- show correct data rate for file upload/download.

## 3.34:

- fixed WinBox crash on startup (introduced in v3.33).

## 3.33:

- added support for hex type fields;
- enabled "Stop" button on auto start actions;
- fixed error messages for start, stop and cancel actions;
- fixed skin when opening in new window;
- fixed time zone offset support for some fields;
- improved interface name sorting;
- properly display all packets captured by sniffer.

## 3.32

- added "Auto Reconnect" feature;
- added fast selection of column checkboxes in "Columns" window by simply typing column name without spaces;
- added support for "Tools->Telnet/SSH" extra parameters;
- alert if there was error executing "Cancel" action;
- fixed MAC connection in new window;
- fixed WinBox when started by Windows "runas" tool with different user;
- fixed crash on "Netwatch" entry "host" field;
- fixed crash when table window was closed before its "Columns" window;
- fixed delayed session window open with "Change Password Now" prompt;
- fixed filter type "contains" for network fields;
- fixed focus marker in checkboxes;
- fixed graphs with values higher than 2^31;
- fixed large text paste in "Terminal" window;
- fixed some fields with empty IPv6 value;
- fixed tables with max entry count feature;
- fixed time value fields in "Scheduler" menu;
- keep terminal lines intact when resizing "Terminal" window;
- properly show all fields which depend on other field;
- release "Safe Mode" with info message, when other user took it;
- restore "Managed" table when toggling "Advanced" mode;
- sort "Columns" window alphabetically;
- use router's time in graphs;
- use router's time in last link up/down fields.

## 3.31

- ask to close all WinBox instances before WinBox upgrade, otherwise upgrade will fail;
- fixed table to properly show and hide columns and remember its widths;
- made MAC-telnet work if SSH or telnet was used before;
- update file path after changing its location with drag&drop.

## 3.30

- added support for mouse wheel scroll in field & table show columns windows;
- double click on word in "Terminal" now automatically selects and copies it to clipboard;
- fixed WinBox disconnect when selecting entries in QuickSet's "WiFi Clients" table;
- fixed crash when all inner windows were closed;
- fixed crash when opening some of interfaces;
- fixed glitches while resizing column widths or reordering table entries;
- fixed visual glitch when showing table filters and categories;
- fixed visual glitches when scrolling "Terminal" window and Zoom In or Zoom Out is used;
- made Ctrl++ & Ctrl+- still work if focus is on checkbox;
- made Ctrl+C and Enter right after text selection in "Terminal" window work as copy to clipboard;
- made Ctrl+D pass-through to "Terminal", so it is possible to terminate inner telnet or SSH sessions;
- made Ctrl+V work as paste from clipboard;
- made double click in "Torch" window work again;
- properly show "I" flag for invalid entries;
- use router's time when filling default time in "Scheduler" items.

## 3.29

- added "Windows" menu for list of all currently opened windows;
- added separate "Show Columns" window for list of visible columns;
- allow changing column order by using drag and drop;
- made "Terminal" window titles unique.

## 3.28

- added support for "contains" and "contains not" filtering in IPv4 address ranges;
- allow to modify DHCPv6 server binding settings;
- do not show newly created elements as invalid (in red);
- expand table flag column to show all possible flags;
- fixed IPv6 prefix column sorting in tables;
- fixed WinBox crash after saving current session;
- fixed WinBox crash when accessing v7 routes with VRF set;
- fixed WinBox crash when some opened element was removed;
- fixed WinBox disconnect when large text was pasted into terminal window;
- fixed problem where optional field disappeared if window was maximized;
- fixed table row selection with keyboard to match Windows behavior;
- keep inner maximized window maximized when changing WinBox window size;
- show missing Security Profile field in WiFi simple mode.

## 3.27

- fixed content drawing of read-only tables (introduced in v3.26).

## 3.26

- fixed CAPsMAN service failure when viewing Radios table;
- fixed Hotspot service failure when viewing Hosts table;
- support Ctrl++ & Ctrl+- on keypad for quick access to Zoom In/Zoom Out.

## 3.25

- added "Find Next - F3" tooltip for Find field;
- added support for CTRL+ and CTRL- keyboard shortcuts for Zoom in and Zoom out;
- added support for DNS names in address type fields;
- do not scroll to first log entry when minimizing WinBox if Log window was open;
- fixed crash when an active Terminal window was opened when WinBox was minimized;
- fixed crash when opening session with Health window open;
- fixed multiple "peer" parameter presence when editing an IPsec policy;
- fixed secure connection establishment after trying to connect to legacy mode devices;
- fixed session file size increase with each WinBox usage;
- improved window resizing and scaling behavior on systems that include high DPI monitors;
- show disabled item icons in gray.

## 3.24

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

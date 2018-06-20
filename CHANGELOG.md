# Changelog

## 3.15

- fixed problem where connecting through RoMON agent with incomplete package set not all menus were available on the target router;
- fixed arrow keys in table filter fields;
- when connected to romon agent mark session as romon one;

## 3.14

- added support for new style authentication and encryption for connections to RouterOS v6.43;
- make all connections in secure mode (all data is encrypted with AES128-CBC-SHA);
- make winbox self upgrade check .exe signature;
- make up/down keys select previous/next entry in address/neighbors list in connect window while login name or password fields are in focus;
- make mouse wheel work anywere in connect window if login or password fields are in focus;
- remember Romon Neighbours Table column widths;
- fixed problem where selected table items were moved to the top if the table filters dropdown button was clicked twice;

## 3.13

- abandoned support for connecting to older RouterOS versions (older than v6), no DLLs will ever be downloaded;
- winbox.exe is now signed executable;

## 3.12

- added new menu entry - "Export Without Passwords";
- make Enter start filtering in Connect window if some of the filters are changed instead of connecting to router;
- do not keep old passwords if user unselected Keep-Password later;
- make file copy & paste work between routers again;
- make Enter key activate Connect if one of connect fields were active even when master password field has not been entered yet;
- fixed Reconnect in RoMON mode with "Open In New Window" enabled;
- other fixes.

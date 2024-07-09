# Changelog

## 3.40.1

- update `Wine` to `stable 9.0`.

## 3.40.0

- update winbox to [3.40](https://download.mikrotik.com/winbox/3.40/winbox64.exe).

## 3.39.0

- update winbox to [3.39](https://download.mikrotik.com/winbox/3.39/winbox64.exe);
- update `Wine` to `devel 8.10`.

## 3.38.0

- update winbox to [3.38](https://download.mikrotik.com/winbox/3.38/winbox64.exe).

## 3.37.0

- update winbox to [3.37](https://download.mikrotik.com/winbox/3.37/winbox64.exe).

## 3.36.1

- update `Wine` to `stable 7.0`.

## 3.36.0

- update winbox to [3.36](https://download.mikrotik.com/winbox/3.36/winbox64.exe).

## 3.35.0

- update winbox to [3.35](https://download.mikrotik.com/winbox/3.35/winbox64.exe).

## 3.34.0

- update winbox to [3.34](https://download.mikrotik.com/winbox/3.34/winbox64.exe).

## 3.32.0

- update winbox to [3.32](https://download.mikrotik.com/winbox/3.32/winbox64.exe).

## 3.31.0

- update winbox to [3.31](https://download.mikrotik.com/winbox/3.31/winbox64.exe).

## 3.30.0

- update winbox to [3.30](https://download.mikrotik.com/winbox/3.30/winbox64.exe).

## 3.28.1

- map <kbd>option</kbd> to <kbd>alt</kbd> and <kbd>command</kbd> to <kbd>ctrl</kbd>;
- enable retina mode by default.

## 3.28.0

- update winbox to [3.28](https://download.mikrotik.com/winbox/3.28/winbox64.exe).

## 3.27.1

- update `Wine` to `devel 6.2`;
- use custom `Wine` build to greatly reduce size;
- add support running under Rosetta2.

## 3.27.0

- update winbox to [3.27](https://download.mikrotik.com/winbox/3.27/winbox64.exe).

## 3.25.0

- update winbox to [3.25](https://download.mikrotik.com/winbox/3.25/winbox64.exe).

## 3.24.1

- add `DYLD_FALLBACK_LIBRARY_PATH`.

## 3.24.0

- update winbox to [3.24](https://download.mikrotik.com/winbox/3.24/winbox64.exe);
- update `Wine` to `staging 5.7`.

## 3.23.0

- update winbox to [3.23](https://download.mikrotik.com/winbox/3.23/winbox64.exe).

## 3.22.0

- update winbox to [3.22](https://download.mikrotik.com/winbox/3.22/winbox64.exe);
- drop `dmg` support.

## 3.21.1

- add ability to pass command line arguments;
- add `libpng15.15.dylib`;
- remove fixme-esync from log;
- rename executable to `winbox-mac`.

## 3.21.0

- update winbox to [3.21](https://download.mikrotik.com/winbox/3.21/winbox64.exe).

## 3.20.5

- use `com.mikrotik.winbox` folder in `Application Support` for all versions;
- update `Wine` to `staging 5.1`;
- remove `winbox-mac-addresses`;
- remove `Freetype` and `xQuartz` dependencies;
- fix issue that app opens again after closing main window.

## 3.20.4

- use plutil instead of defaults;
- remove quarantine flag from Application Support folder;
- update `winbox-mac-addresses` to `0.1.1`.

## 3.20.3

- remove `Winetricks.app` and just copy wineprefix to `Application Support`.

## 3.20.2

- add `winbox-mac-addresses`. Its a [simple script](https://github.com/nrlquaker/winbox-mac-addresses) for copying Winbox-mac managed addresses from old versions to current. Valid for versions `>= 3.20.1`.

## 3.20.1

- new [versioning system](VERSIONING.md);
- fix font rendering in some cases;
- fix ability to run app on non English OS;
- change winbox64.exe location from winebottler to winbox.

## 3.20

- update winbox to [3.20 64-bit](https://download.mikrotik.com/winbox/3.20/winbox64.exe);
- package app manually instead of WineBottler;
- use 64-bit Wine compiled by [Mike Kronenberg](http://winebottler.kronenberg.org/specifications). Remove a lot of unneeded for Winbox files to greatly reduce its size;
- use 64-bit Wine prefix;
- change icon to the new one provided by [Lucas di Lucca](https://github.com/luccaccine).

## 3.19

- update winbox to [3.19](https://download2.mikrotik.com/routeros/winbox/3.19/winbox.exe).
- add empty folders in prefix to repo;
- change user to winbox in prefix and reg files;
- use icon from [mriza/winbox-installer](https://github.com/mriza/winbox-installer/tree/master/icons). This fixes visual bugs of the old one in Mojave.

## 3.18

- update winbox to [3.18](https://download2.mikrotik.com/routeros/winbox/3.18/winbox.exe).

## 3.17

- update winbox to [3.17](https://download2.mikrotik.com/routeros/winbox/3.17/winbox.exe).

## 3.16

- update winbox to [3.16](https://download2.mikrotik.com/routeros/winbox/3.16/winbox.exe).

## 3.15

- update winbox to [3.15](https://download2.mikrotik.com/routeros/winbox/3.15/winbox.exe).

## 3.14

- update winbox to [3.14](https://download2.mikrotik.com/routeros/winbox/3.14/winbox.exe).

## 3.13

- update winbox to [3.13](https://download2.mikrotik.com/routeros/winbox/3.13/winbox.exe).

## 3.12-fix

- add user folder to prefix. Without it it wasn't possible to save configuration.

## 3.12

- update winbox to [3.12](https://download2.mikrotik.com/routeros/winbox/3.12/winbox.exe).

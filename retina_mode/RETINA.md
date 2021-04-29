# Retina mode

To enable retina mode run:

```
WINEPREFIX="/Users/$(whoami)/Library/Application Support/com.mikrotik.winbox" /Applications/Winbox-mac.app/Contents/Resources/wine/bin/wine64 reg add "HKEY_CURRENT_USER\Control Panel\Desktop" /v "LogPixels" /t REG_DWORD /d 192
WINEPREFIX="/Users/$(whoami)/Library/Application Support/com.mikrotik.winbox" /Applications/Winbox-mac.app/Contents/Resources/wine/bin/wine64 reg add "HKEY_CURRENT_USER\Software\Wine\Mac Driver" /v "RetinaMode" /t REG_SZ /d "y"
```

If you want to import the registry manually,`retina.reg` is available [here](https://github.com/nrlquaker/winbox-mac/blob/master/retina_mode/retina.reg).

<p align="center">
  <img src="screenshot.png" width="650">
</p>

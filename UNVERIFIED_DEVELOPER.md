# Unverified developer warning

If you want to remove this warning

![winbox-mac screenshot](unverified_developer/warning.png)

Open `System Preferences -> Security & Privacy -> General` and click `Allow anyway` near `winbox64.exe`

![winbox-mac screenshot](unverified_developer/system_preferences.png)

Next time you see warning just click `Open` to not show it again.

![winbox-mac screenshot](unverified_developer/warning2.png)

or just enter the following command in the terminal:

`xattr -rd com.apple.quarantine /Applications/Winbox-mac.app`

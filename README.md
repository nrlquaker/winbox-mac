# winbox-mac

![Downloads count](https://img.shields.io/github/downloads/nrlquaker/winbox-mac/total.svg)

<p align="center">
  <img src="icon.png" width="200">
</p>

winbox-mac is [MikroTik](https://mikrotik.com) Winbox bundled into macOS app with Wine compiled by [Mike Kronenberg](http://winebottler.kronenberg.org/specifications). Wine was cleaned up of unneeded for Winbox files.
Icon is provided by [Lucas di Lucca](https://github.com/luccaccine).

![winbox-mac screenshot](screenshot.png)

## Installation

Can be easily installed with [Homebrew Cask](https://caskroom.github.io):

```sh
brew cask install nrlquaker-winbox
```

There are two dependencies: [Freetype](https://www.freetype.org/index.html) and [XQuartz](https://www.xquartz.org). Installing with `brew cask` installs them automatically.

## Update

Recommended way to update is to use [Homebrew Cask](https://caskroom.github.io):
```
brew update
brew cask upgrade nrlquaker-winbox
```
But please check [Notes](#notes) how to transfer managed addresses.

## Notes

- Check [this document](UNVERIFIED_DEVELOPER.md) for instructions how to remove "`winbox64.exe` cannot be opened because the developer cannot be verified" warning message.
- Managed addresses are saved to `~/Library/Application Support/com.mikrotik.winbox_$(id)`. The id is different for each version of the app. ~~So if you want to keep them after updating not with winbox inner updater, you have to save them in the old version using `Tools -> Export...` then load in the new one with `Tools -> Import...`.~~
- Opening file browsing windows freezes `Winbox-mac`. Its [known issue](https://forum.mikrotik.com/viewtopic.php?f=2&t=152795&p=754827#p755159) and related to `Catalina` or `Wine64`.
- To keep managed address between update just copy `Addresses.cdb`. For example to copy from Winbox-mac 3.19 to 3.20 run
   ```sh
   cp ~/Library/Application\ Support/com.mikrotik.winbox_156313927421589/drive_c/users/winbox/Application\ Data/Mikrotik/Winbox/Addresses.cdb ~/Library/Application\ Support/com.mikrotik.winbox_320/drive_c/users/`id -un`/Application Data/Mikrotik/Winbox
   ```

## Version

Current version is based on [Winbox 3.20](https://download.mikrotik.com/winbox/3.20/winbox64.exe).

Please check [versioning](VERSIONING.md) for versioning scheme explanation.

## License

winbox-mac is released under the [MIT License](https://github.com/nrlquaker/nfov/blob/master/LICENSE)
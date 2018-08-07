# winbox-mac

![Downloads count](https://img.shields.io/github/downloads/nrlquaker/winbox-mac/total.svg)

winbox-mac is [MikroTik](https://mikrotik.com) Winbox converted to macOS app using [WineBottler](http://winebottler.kronenberg.org).
Icon is from [Winbox4Mac](http://joshaven.com/resources/tools/winbox-for-mac/) used with [Joshaven Potter](http://joshaven.com/#contact) permission.

## Installation

Can be easily installed with [Homebrew Cask](https://caskroom.github.io):

```sh
brew tap nrlquaker/personal
brew cask install winbox-mac
```

## Update

Recommended way to update is to use winbox inner updater: `Tools -> Check For Updates`. If you want to update using `brew cask` please check [Notes](#notes).

## Notes

Managed addresses are saved to `~/Library/Application Support/com.mikrotik.winbox_$(id)`. The id is different for each version of the app. So if you want keep them after updating not with winbox inner updater, you have to save them in the old version using `Tools -> Export...` then load in the new one with `Tools -> Import...`

## Version

Current version is based on [Winbox 3.17](https://download.mikrotik.com/routeros/winbox/3.17/winbox.exe)

## Screenshot

![winbox-mac screenshot](screenshot.png)

## License

winbox-mac is released under the [MIT License](https://github.com/nrlquaker/nfov/blob/master/LICENSE)

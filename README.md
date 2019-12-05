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

- This is not official [MikroTik](https://mikrotik.com) build and is not related to Mikrotik in any way.
- Check [this document](UNVERIFIED_DEVELOPER.md) for instructions how to remove "`winbox64.exe` cannot be opened because the developer cannot be verified" warning message.
- Managed addresses are saved to different directory in each version of the app. They can be copied to the new version with [winbox-mac-addresses](https://github.com/nrlquaker/winbox-mac-addresses). Just run `winbox-mac-addresses version`. Version should be 3.20.1 or higher.

## Reporting bugs

Please make sure that you are using [bug report template](https://github.com/nrlquaker/winbox-mac/issues/new?assignees=nrlquaker&labels=&template=bug_report.md&title=) and checklist is complete. Otherwise it may be closed without review.

## Known issues

- Opening file browsing windows freezes `Winbox-mac`. Its related to  `Wine`. This issue is fixed in Wine Staging 4.18. Will wait till stable build is released and update Wine.

## Contributions are welcomed

If you like this project and you find it useful help me to improve it. First of all check if there are some [help needed issues](https://github.com/nrlquaker/winbox-mac/issues?q=is%3Aissue+is%3Aopen+label%3A%22help+wanted%22). Or you can improve code or documentation.

## Version

Current version is based on [Winbox 3.20](https://download.mikrotik.com/winbox/3.20/winbox64.exe).

Please check [versioning](VERSIONING.md) for versioning scheme explanation.

## Changelog

There are two changelogs in this project. [One](CHANGELOG.md) related to `Winbox-mac`, the [other one](CHANGELOG_WINBOX.md) is for original Winbox.

## License

winbox-mac is released under the [MIT License](https://github.com/nrlquaker/winbox-mac/blob/master/LICENSE)

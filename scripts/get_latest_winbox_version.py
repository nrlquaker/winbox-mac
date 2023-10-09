#!/usr/bin/env python3
import plistlib
import requests
import semver

WINBOX_DOWNLOAD_ROOT = "https://download.mikrotik.com/routeros/winbox/"

def get_latest_winbox_version():
    response = requests.get(WINBOX_DOWNLOAD_ROOT + "LATEST.3")
    return semver.VersionInfo.parse(response.text)

def get_current_winbox_version():
    with open("./Winbox-mac.app/Contents/Info.plist", "rb") as f:
        info = plistlib.load(f)
        return semver.VersionInfo.parse(info["CFBundleShortVersionString"])

def main():
    latest_version = get_latest_winbox_version()
    current_version = get_current_winbox_version()
    # Only check of major and minor versions are the same
    if latest_version.major == current_version.major and latest_version.minor == current_version.minor:
        return True
    else:
        return False

if __name__ == "__main__":
    main()
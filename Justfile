update-winbox:
    wget -O Winbox-mac.app/Contents/Resources/winbox64.exe https://mt.lv/winbox64

bump-version:
    ./scripts/bump_version.sh

make-release: 
    ./scripts/make_release.sh

update: update-winbox bump-version make-release
    echo "Updated Winbox and bumped version"
    echo "You will need to update the README.md and CHANGELOG's manually."
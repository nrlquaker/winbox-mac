update-winbox:
    wget -O Winbox-mac.app/Contents/Resources/winbox64.exe https://mt.lv/winbox64

bump-version VERSION:
    ./scripts/bump_version {{VERSION}}

make-release: 
    ./scripts/release

update VERSION: update-winbox (bump-version VERSION) make-release
    echo "Updated Winbox and bumped version"
    echo "You will need to update the README.md and CHANGELOG's manually."
#!/bin/sh

#
# bottler.sh
# of the 'WBottler' target in the 'WineBottler' project
#
# Copyright 2009 Mike Kronenberg
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
#



##########                 Might be stripped by macOS                 ##########
################################################################################
[ "$LD_LIBRARY_PATH" == "" ] && {
    export LD_LIBRARY_PATH="$WINEPREFIX/lib":"/opt/X11/lib":"/usr/X11/lib"
}
[ "$DYLD_FALLBACK_LIBRARY_PATH" == "" ] && {
    export DYLD_FALLBACK_LIBRARY_PATH="$WINEPREFIX/lib":"/usr/lib":"/opt/X11/lib:/usr/X11/lib"
}



##########                         Debug Info                         ##########
################################################################################
WINE_VERSION=$("$WINEPATH/wine" --version |sed 's/wine-//')

echo "###BOTTLING### Gathering debug Info..."
echo ""
echo "Versions"
echo "OS...........................: "$OSTYPE
echo "Wine.........................: "$WINE_VERSION
echo "WineBottler..................: "$(pl < "../../Info.plist" | grep CFBundleVersion | sed 's/    CFBundleVersion = "//g' | sed 's/";//g')
echo "Wineticks....................: "$(sh "$HOME/Library/Application Support/Wine/winetricks" --version)
echo ""
echo "Environment"
echo "PWD..........................: '"$(PWD)"'"
echo "PATH.........................: $PATH"
echo "USER.........................: $USER"
echo "HOME.........................: $HOME"
echo "COMPUTERNAME.................: $COMPUTERNAME"
echo "BUNDLERESOURCEPATH...........: $BUNDLERESOURCEPATH"
echo "WINEPREFIX...................: $WINEPREFIX"
echo "WINEPATH.....................: $WINEPATH"
echo "LD_LIBRARY_PATH..............: $LD_LIBRARY_PATH"
echo "DYLD_FALLBACK_LIBRARY_PATH...: $DYLD_FALLBACK_LIBRARY_PATH"
echo "SILENT.......................: $SILENT"
echo "http_proxy...................: $http_proxy"
echo "https_proxy..................: $https_proxy"
echo "ftp_proxy....................: $ftp_proxy"
echo "socks5_proxy.................: $socks5_proxy"
echo ""
echo "Bottle"
echo "TEMPLATE.....................: $TEMPLATE"
echo "BOTTLE.......................: $BOTTLE"
echo "INSTALLER_URL................: $INSTALLER_URL"
echo "INSTALLER_IS_ZIPPED..........: $INSTALLER_IS_ZIPPED"
echo "INSTALLER_NAME...............: $INSTALLER_NAME"
echo "INSTALLER_ARGUMENTS..........: $INSTALLER_ARGUMENTS"
echo "REMOVE_MONO..................: $REMOVE_MONO"
echo "REMOVE_GECKO.................: $REMOVE_GECKO"
echo "REMOVE_USERS.................: $REMOVE_USERS"
echo "REMOVE_INSTALLERS............: $REMOVE_INSTALLERS"
echo "WINETRICKS_ITEMS.............: $WINETRICKS_ITEMS"
echo "DLL_OVERRIDES................: $DLL_OVERRIDES"
echo "EXECUTABLE_PATH..............: $EXECUTABLE_PATH"
echo "EXECUTABLE_ARGUMENTS.........: $EXECUTABLE_ARGUMENTS"
echo "EXECUTABLE_VERSION...........: $EXECUTABLE_VERSION"
echo "BUNDLE_COPYRIGHT.............: $BUNDLE_COPYRIGHT"
echo "BUNDLE_IDENTIFIER............: $BUNDLE_IDENTIFIER"
echo "BUNDLE_CATEGORYTYPE..........: $BUNDLE_CATEGORYTYPE"
echo "SILENT.......................: $SILENT"
echo ""
/usr/sbin/system_profiler SPHardwareDataType
sleep 1



##########        Some export because I had troubles with paths        #########
################################################################################
export PATH="$BUNDLERESOURCEPATH":"$BUNDLERESOURCEPATH/bin":"$WINEPATH":$PATH
export WINE="$WINEPATH/wine"
export WINESERVER="$WINEPATH/wineserver"
export WINEPREFIX="$BOTTLE/Contents/Resources/wineprefix"
export USERNAME="$USER"
export WINEBOTTLER_TMP="/private/tmp/winebottler_$(date +%s)"
export WINEDLLOVERRIDES=$DLL_OVERRIDES
#export LANG=fr.UTF-8
#export LC_CTYPE=fr_FR.UTF-8

##########         Some overrides necessary bevore first launch        #########
################################################################################
[ "$REMOVE_MONO" == "1" ] && {
    export WINEDLLOVERRIDES=$WINEDLLOVERRIDES"mscoree=;"
}
[ "$REMOVE_GECKO" == "1" ] && {
    export WINEDLLOVERRIDES=$WINEDLLOVERRIDES"mshtml=;"
}



##########            Fix "new" rendering engine of freetype           #########
################################################################################
# https://bugs.winehq.org/show_bug.cgi?id=41639
export FREETYPE_PROPERTIES="truetype:interpreter-version=35"



##########              MULTIINSTANCE AND NOSPACE SUPPORT              #########
################################################################################
# - sometime people try to run multiple instances of winetricks, so we run them in separated places, so that we can tidy up afterwards
# - winetricks is often not safe for paths with spaces, so we link everithing to save paths)
export NOSPACE_PATH=$WINEBOTTLER_TMP"/nospace"
mkdir -p "$NOSPACE_PATH"



##########                       chatch errors                        ##########
################################################################################
winebottlerTry () {
    log=$("$@")
    status=$?
    if test $status -ne 0
    then
        rm -rf "$NOSPACE_PATH"
		echo "### LOG ### Command '$@' returned status $status."
		echo ""
		echo "$log"
		echo ""
        echo "###ERROR### Command '$@' returned status $status."
        wait
        exit 1
    fi
}
export -f winebottlerTry



##########           chatch errors of msi installer                   ##########
################################################################################
winebottlerTryMsi () {
    log=$("$@")
    status=$?
	#support ERROR_SUCCESS, ERROR_SUCCESS_REBOOT_INITIATED and ERROR_SUCCESS_REBOOT_REQUIRED
    if test $status -ne 0
		then
		if test $status -ne 1641
			then
			if test $status -ne 3010
                then
                echo "### LOG ### Command '$@' returned status $status."
                echo ""
                echo $log
                echo ""
				echo "###ERROR### Command '$@' returned status $status."
                wait
                exit 1
			fi
		fi
	fi
}
export -f winebottlerTryMsi



##########                  support for native dlls                   ##########
################################################################################
winebottlerOverrideDlls() {
    mode=$1
    shift
#    echo Using $mode override for following DLLs: $@
    cat > /tmp/override-dll.reg <<_EOF_
REGEDIT4

[HKEY_CURRENT_USER\Software\Wine\DllOverrides]
_EOF_
    while test "$1" != ""
    do
        case "$1" in
        comctl32)
           rm -rf "$WINDIR"/winsxs/manifests/x86_microsoft.windows.common-controls_6595b64144ccf1df_6.0.2600.2982_none_deadbeef.manifest
           ;;
        esac
        echo "\"$1\"=\"$mode\"" >> /tmp/override-dll.reg
    shift
    done

    "$WINE" regedit /tmp/override-dll.reg
    rm /tmp/override-dll.reg
}
export -f winebottlerOverrideDlls



##########                     File downloading                       ##########
################################################################################
winebottlerDownload() {
    if [ $# -ne 2 ]; then
        filename=$(basename ${1})
    else
        filename="${2}"
    fi
	
	if [ "$socks5_proxy"  != "" ]; then
		curl --socks5-hostname "$socks5_proxy" -s -L -o "$filename" -C - --header "Accept-Encoding: gzip,deflate" ${1}
	else
		curl -s -L -o "$filename" -C - --header "Accept-Encoding: gzip,deflate" ${1}
	fi
}
export -f winebottlerDownload



##########                    Create exact copy                       ##########
################################################################################
tarcp() {
    (cd "$1"; tar cfv - . ) | ( mkdir -p "$2"; cd "$2" ; tar xfpv - )
}
export -f tarcp



##########                Create a new app container                  ##########
################################################################################
winebottlerApp () {
    echo "###BOTTLING### Create .app..."
	
	APP_RANDOMID=$(echo "$(date +%s)$RANDOM")
	APP_PREFS_DOMAIN=""$BUNDLE_IDENTIFIER"_"$APP_RANDOMID""
	APP_NAME="$(basename -s .app "$BOTTLE")"

    #create app layout (copy file by file to not destroy a template)
    mkdir -p "$BOTTLE/Contents/Resources/English.lproj/main.nib"
	mkdir -p "$BOTTLE/Contents/MacOS/"

	sed -e "s/APP_NAME/$APP_NAME/g" -e "s/EXECUTABLE_VERSION/$EXECUTABLE_VERSION/g" "$BUNDLERESOURCEPATH/Credits.html" > "$BOTTLE/Contents/Resources/Credits.html"

    ditto "$(echo $(cd "$BUNDLERESOURCEPATH/../../../Resources/Winetricks.app"; pwd))" "$BOTTLE/Contents/Resources/Winetricks.app"
	wait
	
	#startwine
    cat > "$BOTTLE/Contents/MacOS/startwine" <<_EOF_
#!/bin/bash



BUNDLERESOURCEPATH="\$(dirname "\$0")/../Resources"



#find wine, try in Bundle, ~/Applications, /Applications, Spotlight
if [ -f "\$BUNDLERESOURCEPATH/Wine.bundle/Contents/Resources/bin/wine" ]; then
    export WINEUSRPATH="\$BUNDLERESOURCEPATH/Wine.bundle/Contents/Resources"
elif [ -f "\$HOME/Applications/Wine.app/Contents/Resources/bin/wine" ]; then
    export WINEUSRPATH="\$HOME/Applications/Wine.app/Contents/Resources"
elif [ -f "/Applications/Wine.app/Contents/Resources/bin/wine" ]; then
    export WINEUSRPATH="/Applications/Wine.app/Contents/Resources"
elif [ -f "\$(mdfind 'kMDItemCFBundleIdentifier == org.kronenberg.Wine' | grep -m 1 'Wine.app')/Contents/Resources/bin/wine" ]; then
    export WINEUSRPATH="\$(mdfind 'kMDItemCFBundleIdentifier == org.kronenberg.Wine' | grep -m 1 'Wine.app')/Contents/Resources"
else
    echo "Wine not found!"
    exit 1
fi



# create working copy
export WINEPREFIX="\$HOME/Library/Application Support/$APP_PREFS_DOMAIN"
if [ ! -d "\$WINEPREFIX" ]; then
    "\$BUNDLERESOURCEPATH/Winetricks.app/Contents/MacOS/./Winetricks" "\$BUNDLERESOURCEPATH/wineprefix" "\$WINEPREFIX" "\$(defaults read "\$BUNDLERESOURCEPATH/../Info" CFBundleName)"
fi



# exports (we keep X11 for fallback) fix new Freetype 2.7+ engine (https://bugs.winehq.org/show_bug.cgi?id=41639)
export PATH="\$WINEUSRPATH/bin":"\$PATH"
export LD_LIBRARY_PATH="\$LD_LIBRARY_PATH":"\$WINEUSRPATH/lib":"/opt/X11/lib":"/usr/X11/lib"
export DYLD_FALLBACK_LIBRARY_PATH="/usr/lib":"\$WINEUSRPATH/lib":"/opt/X11/lib":"/usr/X11/lib"
export WINEPATH="\$WINEUSRPATH/bin"
export FREETYPE_PROPERTIES="truetype:interpreter-version=35"

#some default windows vars that might be missing ( http://ss64.com/nt/syntax-variables.html )
[ -z "\$COMPUTERNAME" ] && export COMPUTERNAME="\$(/usr/sbin/scutil --get ComputerName)"

# start wine and program, if possible in the programs root directory, change to forwardslashes
BIN_FILE="\$(sed 's|\\\\|/|g' <<< "\$(defaults read "\$BUNDLERESOURCEPATH/../Info" WineProgramPath)")"
BIN_PATH="\$BUNDLERESOURCEPATH/wineprefix/drive_c\$(sed 's|C:||' <<< "\$(dirname "\$BIN_FILE")")"
if [ -d "\$BIN_PATH" ]; then
    cd "\$BIN_PATH"
fi
if [ "\$(defaults read "\$BUNDLERESOURCEPATH/../Info" WineProgramArguments)" != "" ]; then
"\$WINEUSRPATH/bin/wine" "\$BIN_FILE" \$(defaults read "\$BUNDLERESOURCEPATH/../Info" WineProgramArguments)
else
"\$WINEUSRPATH/bin/wine" "\$BIN_FILE"
fi

_EOF_
	chmod a+x "$BOTTLE/Contents/MacOS/startwine"

    #Info.plist
    SANITIZED_EXECUTABLE_PATH="$(echo "$EXECUTABLE_PATH" | sed -e 's/\&/\&amp;/g' -e 's|\\|/|g')"
    cat > "$BOTTLE/Contents/Info.plist" <<_EOF_
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
    <key>WineProgramPath</key>
    <string>$SANITIZED_EXECUTABLE_PATH</string>
    <key>WineProgramArguments</key>
    <string>$EXECUTABLE_ARGUMENTS</string>
    <key>CFBundleDevelopmentRegion</key>
    <string>English</string>
    <key>CFBundleExecutable</key>
    <string>startwine</string>
	<key>NSHumanReadableCopyright</key>
	<string>$BUNDLE_COPYRIGHT</string>
    <key>CFBundleIdentifier</key>
    <string>$APP_PREFS_DOMAIN</string>
    <key>CFBundleInfoDictionaryVersion</key>
    <string>6.0</string>
    <key>CFBundleName</key>
    <string>$APP_NAME</string>
    <key>CFBundlePackageType</key>
    <string>APPL</string>
    <key>CFBundleSignature</key>
    <string>????</string>
    <key>CFBundleVersion</key>
    <string>$EXECUTABLE_VERSION</string>
    <key>CFBundleShortVersionString</key>
    <string>$EXECUTABLE_VERSION</string>
	<key>CFBundleIconFile</key>
	<string>Icon.icns</string>
	<key>LSApplicationCategoryType</key>
	<string>$BUNDLE_CATEGORYTYPE</string>
    <key>CFBundleDocumentTypes</key>
	<array>
        <dict>
            <key>CFBundleTypeExtensions</key>
            <array>
                <string>*</string>
            </array>
            <key>CFBundleTypeName</key>
            <string>All</string>
            <key>CFBundleTypeRole</key>
            <string>Editor</string>
            <key>LSTypeIsPackage</key>
            <false/>
            <key>NSPersistentStoreTypeKey</key>
            <string>Binary</string>
        </dict>
    </array>
</dict>
</plist>
_EOF_
}
export -f winebottlerApp



##########            Registering OS X corefonts in prefix            ##########
################################################################################
winebottlerRegisterOSXCoreFonts() {
    echo "###BOTTLING### Registering Truetype Fonts..."
    cat > /tmp/register-font.reg <<_EOF_
REGEDIT4

[HKEY_LOCAL_MACHINE\Software\Microsoft\Windows NT\CurrentVersion\Fonts]
"Arial Black (TrueType)"="Arial Black.ttf"
"Arial Bold Italic (TrueType)"="Arial Bold Italic.ttf"
"Arial Bold (TrueType)"="Arial Bold.ttf"
"Arial Italic (TrueType)"="Arial Italic.ttf"
"Arial Narrow Bold Italic (TrueType)"="Arial Narrow Bold Italic.ttf"
"Arial Narrow Bold (TrueType)"="Arial Narrow Bold.ttf"
"Arial Narrow Italic (TrueType)"="Arial Narrow Italic.ttf"
"Arial Narrow (TrueType)"="Arial Narrow.ttf"
"Arial Rounded Bold (TrueType)"="Arial Rounded Bold.ttf"
"Arial Unicode (TrueType)"="Arial Unicode.ttf"
"Arial (TrueType)"="Arial.ttf"
"Ayuthaya (TrueType)"="Ayuthaya.ttf"
"Baghdad (TrueType)"="Baghdad.ttf"
"Brush Script (TrueType)"="Brush Script.ttf"
"Comic Sans MS Bold (TrueType)"="Comic Sans MS Bold.ttf"
"Comic Sans MS (TrueType)"="Comic Sans MS.ttf"
"Courier New Bold Italic (TrueType)"="Courier New Bold Italic.ttf"
"Courier New Bold (TrueType)"="Courier New Bold.ttf"
"Courier New Italic (TrueType)"="Courier New Italic.ttf"
"Courier New (TrueType)"="Courier New.ttf"
"Georgia Bold Italic (TrueType)"="Georgia Bold Italic.ttf"
"Georgia Bold (TrueType)"="Georgia Bold.ttf"
"Georgia Italic (TrueType)"="Georgia Italic.ttf"
"Georgia (TrueType)"="Georgia.ttf"
"Impact (TrueType)"="Impact.ttf"
"Microsoft Sans Serif (TrueType)"="Microsoft Sans Serif.ttf"
"Tahoma Bold (TrueType)"="Tahoma Bold.ttf"
"Tahoma (TrueType)"="Tahoma.ttf"
"Times New Roman Bold Italic (TrueType)"="Times New Roman Bold Italic.ttf"
"Times New Roman Bold (TrueType)"="Times New Roman Bold.ttf"
"Times New Roman Italic (TrueType)"="Times New Roman Italic.ttf"
"Times New Roman (TrueType)"="Times New Roman.ttf"
"Trebuchet MS Bold Italic (TrueType)"="Trebuchet MS Bold Italic.ttf"
"Trebuchet MS Bold (TrueType)"="Trebuchet MS Bold.ttf"
"Trebuchet MS Italic (TrueType)"="Trebuchet MS Italic.ttf"
"Trebuchet MS (TrueType)"="Trebuchet MS.ttf"
"Verdana Bold Italic (TrueType)"="Verdana Bold Italic.ttf"
"Verdana Bold (TrueType)"="Verdana Bold.ttf"
"Verdana Italic (TrueType)"="Verdana Italic.ttf"
"Verdana (TrueType)"="Verdana.ttf"
"Webdings (TrueType)"="Webdings.ttf"
"Wingdings 2 (TrueType)"="Wingdings 2.ttf"
"Wingdings 3 (TrueType)"="Wingdings 3.ttf"
"Wingdings (TrueType)"="Wingdings.ttf"
_EOF_
	winebottlerTry "$WINE" regedit /tmp/register-font.reg
    winebottlerTry rm /tmp/register-font.reg
}
export -f winebottlerRegisterOSXCoreFonts



##########              Registering OS X fonts in prefix              ##########
################################################################################
winebottlerRegisterFont() {
    file=$1
    shift
    font=$1
    cat > /tmp/register-font.reg <<_EOF_
REGEDIT4

[HKEY_LOCAL_MACHINE\Software\Microsoft\Windows NT\CurrentVersion\Fonts]
"$font"="$file"
_EOF_
    winebottlerTry "$WINE" regedit /tmp/register-font.reg
    winebottlerTry rm /tmp/register-font.reg
}
export -f winebottlerRegisterFont



##########      CoreAudio, Colors, Antialiasing  and flat menus       ##########
################################################################################
winebottlerReg() {
    echo "###BOTTLING### Enabling CoreAudio, Colors, Antialiasing  and flat menus..."


[ "$WINDOWS_COLOR" != "" ] && {
    cat > /tmp/reg.reg <<_EOF_
REGEDIT4

[HKEY_CURRENT_USER\Control Panel\Colors]
"ActiveBorder"="237 237 237"
"ActiveTitle"="10 36 106"
"AppWorkSpace"="110 110 110"
"Background"="255 255 255"
"ButtonAlternateFace"="181 181 181"
"ButtonDkShadow"="80 80 80"
"ButtonFace"="237 237 237"
"ButtonHilight"="255 255 255"
"ButtonLight"="237 237 237"
"ButtonShadow"="169 169 169"
"ButtonText"="0 0 0"
"GradientActiveTitle"="166 202 240"
"GradientInactiveTitle"="192 192 192"
"GrayText"="110 110 110"
"Hilight"="78 110 244"
"HilightText"="255 255 255"
"HotTrackingColor"="0 0 128"
"InactiveBorder"="167 167 167"
"InactiveTitle"="110 110 110"
"InactiveTitleText"="212 208 200"
"InfoText"="0 0 0"
"InfoWindow"="255 255 225"
"Menu"="255 255 255"
"MenuBar"="167 167 167"
"MenuHilight"="78 110 244"
"MenuText"="0 0 0"
"Scrollbar"="212 212 212"
"TitleText"="255 255 255"
"Window"="255 255 255"
"WindowFrame"="169 169 169"
"WindowText"="0 0 0"

[HKEY_CURRENT_USER\Control Panel\Desktop]
"FontSmoothing"="2"
"FontSmoothingType"=dword:00000002
"FontSmoothingGamma"=dword:00000578
"FontSmoothingOrientation"=dword:00000001
"UserPreferenceMask"=hex:10,00,02,80

[HKEY_CURRENT_USER\Control Panel\Desktop\WindowMetrics]
"MenuFont"=hex:f3,ff,ff,ff,00,00,00,00,00,00,00,00,00,00,00,00,90,01,00,00,00,\
  00,00,00,00,00,00,22,42,00,69,00,74,00,73,00,74,00,72,00,65,00,61,00,6d,00,\
  20,00,56,00,65,00,72,00,61,00,20,00,53,00,61,00,6e,00,73,00,00,00,00,00,00,\
  00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00
"MenuHeight"="21"
"MenuWidth"="21"
_EOF_
    winebottlerTry "$WINE" regedit /tmp/reg.reg
    winebottlerTry rm /tmp/reg.reg
}

cat > /tmp/reg.reg <<_EOF_
REGEDIT4

[HKEY_CURRENT_USER\Control Panel\Desktop]
"FontSmoothing"="2"
"FontSmoothingType"=dword:00000002
"FontSmoothingGamma"=dword:00000578
"FontSmoothingOrientation"=dword:00000001

[HKEY_CURRENT_USER\Software\Wine\Drivers]
"Audio"="coreaudio"

[HKEY_CURRENT_USER\Software\Wine\DllOverrides]
"winemenubuilder.exe"="native"

_EOF_
    winebottlerTry "$WINE" regedit /tmp/reg.reg
    winebottlerTry rm /tmp/reg.reg

    cp "$BUNDLERESOURCEPATH/winemenubuilder.exe" "$WINEPREFIX/drive_c/windows/System32/"
}
export -f winebottlerReg



##########                          sandbox                           ##########
################################################################################
winebottlerSandbox () {
    echo "###BOTTLING### Sandboxing..."
	
    winebottlerTry find "$WINEPREFIX/drive_c/users/$USER" -name '*' -type l -exec sh -c 'rm "{}"; mkdir -p "{}"' \;
}
export -f winebottlerSandbox



##########                       create prefix                        ##########
################################################################################
winebottlerPrefix () {

    winebottlerReg
	wait
	[ "$WINE_VERSION" != "1.0.1" ] && {
		winebottlerSandbox
		wait
	}
	cd "$WINEPREFIX/drive_c/windows"
#   winebottlerTry rm -rf "$WINEPREFIX/drive_c/windows/system"
#	wait
#	winebottlerTry ln -s "system32" "system"
#	wait
    echo "###BOTTLING### Installing Truetype Fonts..."
    find /Library/Fonts -name \*.ttf -exec sh -c 'ln -s "{}" "$WINEPREFIX/drive_c/windows/Fonts/`basename "{}"`"' \;
    find ~/Library/Fonts -name \*.ttf -exec sh -c 'ln -s "{}" "$WINEPREFIX/drive_c/windows/Fonts/`basename "{}"`"' \;
	winebottlerRegisterOSXCoreFonts
	wait
    cd -
    winebottlerTry "$WINESERVER" -k
	wait

	mv "$BOTTLE/Contents/Info.plist" "$BOTTLE/Contents/Info.plist2"
	sed "s/%ProgramFiles%/$( sed 's/\\/\\\\/g' <<< $("$WINE" cmd.exe /c echo %ProgramFiles% | tr -d "\015"))/" "$BOTTLE/Contents/Info.plist2" > "$BOTTLE/Contents/Info.plist"
	rm "$BOTTLE/Contents/Info.plist2"
	
	# mark this as a WineBottler prefix
	echo "Made by WineBottler" > "$WINEPREFIX/WineBottler.id"
}
export -f winebottlerPrefix



##########                        copy prefix                         ##########
################################################################################
winebottlerPrefixCopy () {
    echo "###BOTTLING### Copy prefix..."

    tarcp "$TEMPLATE" "$WINEPREFIX"
    wait

    winebottlerTry "$WINESERVER" -k
    wait

    mv "$BOTTLE/Contents/Info.plist" "$BOTTLE/Contents/Info.plist2"
    sed "s/%ProgramFiles%/$( sed 's/\\/\\\\/g' <<< $("$WINE" cmd.exe /c echo %ProgramFiles% | tr -d "\015"))/" "$BOTTLE/Contents/Info.plist2" > "$BOTTLE/Contents/Info.plist"
    rm "$BOTTLE/Contents/Info.plist2"

    # mark this as a WineBottler prefix
    echo "Made by WineBottler" > "$WINEPREFIX/WineBottler.id"
}
export -f winebottlerPrefixCopy



##########                  Add items from winetricks                  #########
################################################################################
function winebottlerWinetricks () {
[ "$WINETRICKS_ITEMS" != "" ] && {

        # be sure to have a nospace folder
        mkdir -p "$NOSPACE_PATH"

        # prepare winetricks
        head -$(($(cat "$HOME/Library/Application Support/Wine/winetricks" | grep -n "execute_command()" | sed 's/[^0-9]//g') - 2)) "$HOME/Library/Application Support/Wine/winetricks" > "$NOSPACE_PATH/winetricks.sh"
        cat "$HOME/Library/Application Support/Wine/customverbs" >> "$NOSPACE_PATH/winetricks.sh"
        tail -$(($(wc -l "$HOME/Library/Application Support/Wine/winetricks" | sed 's/[^0-9]//g') - $(cat "$HOME/Library/Application Support/Wine/winetricks" | grep -n "execute_command()" | sed 's/[^0-9]//g') + 2)) "$HOME/Library/Application Support/Wine/winetricks" >> "$NOSPACE_PATH/winetricks.sh"

		# PROXY support
		if [ "$socks5_proxy"  != "" ]; then
			SaveSocks5_proxy=`echo "$socks5_proxy" | sed 's:[]\[\^\$\.\*\/]:\\\\&:g'`
			mv "$NOSPACE_PATH/winetricks.sh" "$NOSPACE_PATH/winetricks.sh2"
			sed 's/try curl /try curl --socks5-hostname $SaveSocks5_proxy /g' "$NOSPACE_PATH/winetricks.sh2" > "$NOSPACE_PATH/winetricks.sh"
			rm "$NOSPACE_PATH/winetricks.sh2"
		fi
		
		# WORKAROUND create a "no-spaces environment"
		WINESAVE=$WINE
		PATHSAVE=$PATH
		PREFSAVE=$WINEPREFIX
		ln -s "$WINEPATH/wine" "$NOSPACE_PATH/wine"
		ln -s "$(which cabextract)" "/$NOSPACE_PATH/cabextract"
		ln -s "$WINEPREFIX" "$NOSPACE_PATH/wineprefix"
		export PATH="$NOSPACE_PATH":"$PATH"
		export WINE="$NOSPACE_PATH/wine"
		export WINEPREFIX="$NOSPACE_PATH/wineprefix"

		# APPLY winetricks
		for W in $WINETRICKS_ITEMS; do
			echo "###BOTTLING### installing $W"
			winebottlerTry source "$NOSPACE_PATH/winetricks.sh" --no-isolate $SILENT $W
		done
		
        # /WORKAROUND create "no-spaces environment"
        export PATH="$PATHSAVE"
		export WINE="$WINESAVE"
        export WINEPREFIX="$PREFSAVE"
        rm -rf "$NOSPACE_PATH"
	}
}
export -f winebottlerWinetricks



##########                         Proxy                               #########
################################################################################
function winebottlerProxy () {
    [ "$http_proxy" != "" ] && {
		echo "###BOTTLING### Enabling HTTP Proxy..."
    
		cat > /tmp/proxy.reg <<_EOF_
REGEDIT4

[HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Internet Settings]
"MigrateProxy"=dword:00000001
"ProxyEnable"=dword:00000001
"ProxyHttp1.1"=dword:00000000
"ProxyServer"="http://$http_proxy"
"ProxyOverride"="<local>"

_EOF_
		winebottlerTry "$WINE" regedit /tmp/proxy.reg
		winebottlerTry rm /tmp/proxy.reg
    }
	
	[ "$socks5_proxy" != "" ] && {
		echo "###BOTTLING### Enabling Socks5 Proxy..."
    
		cat > /tmp/proxy.reg <<_EOF_
REGEDIT4

[HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Internet Settings]
"MigrateProxy"=dword:00000001
"ProxyEnable"=dword:00000001
"ProxyHttp1.1"=dword:00000000
"ProxyServer"="http://$socks5_proxy"
"ProxyOverride"="<local>"

_EOF_
		winebottlerTry "$WINE" regedit /tmp/proxy.reg
		winebottlerTry rm /tmp/proxy.reg
    }
}
export -f winebottlerProxy



##########                       Overrides                             #########
################################################################################
function winebottlerOverride () {
    echo "###BOTTLING### Registering native dlls..."
    [ "$DLL_OVERRIDES"  != "" ] && {
cat > /tmp/override-dll.reg <<_EOF_
REGEDIT4

[HKEY_CURRENT_USER\Software\Wine\DllOverrides]
_EOF_

        arr=$(echo $DLL_OVERRIDES | tr ";" "\n")
        for x in $arr
        do
            sed -e 's/\(.*\)=\(.*\)/"\1"="\2"/' <<< "$x" >> /tmp/override-dll.reg
        done
        "$WINE" regedit /tmp/override-dll.reg
        rm /tmp/override-dll.reg

    }
}
export -f winebottlerOverride



##########               Running command in clean env                  #########
################################################################################
function runSanitized () {
    cat > "$WINEPREFIX/drive_c/windows/temp/sanitized.sh" << __EOF__
export WINEPATH="$WINEPATH"
export DYLD_FALLBACK_LIBRARY_PATH="$DYLD_FALLBACK_LIBRARY_PATH"
export LD_LIBRARY_PATH="$LD_LIBRARY_PATH"
export WINEDEBUG="$WINEDEBUG"
export DISPLAY="$DISPLAY"
export PATH="$NOSPACE_PATH":"$PATH"
export USER="$USER"
export HOME="$HOME"
export FREETYPE_PROPERTIES="truetype:interpreter-version=35"



# WORKAROUND create "no-spaces environment"
mkdir -p "$NOSPACE_PATH"
ln -s "$WINEPREFIX" "$NOSPACE_PATH/wineprefix"
export WINEPREFIX="$NOSPACE_PATH/wineprefix"

# DO
$1

# CLEANUP "no-spaces environment"
rm -rf "$NOSPACE_PATH" &> /dev/null

__EOF__

    winebottlerTry env -i sh "$WINEPREFIX/drive_c/windows/temp/sanitized.sh"
    rm "$WINEPREFIX/drive_c/windows/temp/sanitized.sh"
}
export -f runSanitized



##########                      Installation                           #########
################################################################################
function winebottlerInstall () {


    #winebottlerTry "$WINESERVER" -k
    wait
    sleep 2



    [ "$INSTALLER_URL" != "" ] && {
	
		#do we have to download it first?
		DOWNLOAD_FIRST=0;
		if test $(echo "$INSTALLER_URL" | grep http://); then DOWNLOAD_FIRST=1; fi
		if test $(echo "$INSTALLER_URL" | grep https://); then DOWNLOAD_FIRST=1; fi
		if test $(echo "$INSTALLER_URL" | grep ftp://); then DOWNLOAD_FIRST=1; fi
		
		if [ "$DOWNLOAD_FIRST" -eq "1" ]; then
		
			echo "###BOTTLING### Downloading "$INSTALLER_NAME"..."
			winebottlerTry rm "$WINEPREFIX/dosdevices/z:"
			mkdir -p "$WINEPREFIX/drive_c/windows/temp/installer"
			if [ "$INSTALLER_IS_ZIPPED" == "1" ]; then
				winebottlerDownload "$INSTALLER_URL" "$WINEPREFIX/drive_c/windows/temp/installer/wbdownloadwb.zip"
				unzip -d "$WINEPREFIX/drive_c/windows/temp/installer" "$WINEPREFIX/drive_c/windows/temp/installer/wbdownloadwb.zip"
				rm "$WINEPREFIX/drive_c/windows/temp/installer/wbdownloadwb.zip"
			else
				winebottlerDownload "$INSTALLER_URL" "$WINEPREFIX/drive_c/windows/temp/installer/$INSTALLER_NAME"
			fi
			
			echo "###BOTTLING### Installing "$INSTALLER_NAME"..."
			# only copy installer
			if test $(echo "$INSTALLER_ARGUMENTS" | grep "WINEBOTTLERCOPYFILEONLY"); then
				mkdir "$WINEPREFIX/drive_c/winebottler"
				mv "$WINEPREFIX/drive_c/windows/temp/installer/$INSTALLER_NAME" "$WINEPREFIX/drive_c/winebottler/"
			
			# copy whole folder
			elif test $(echo "$INSTALLER_ARGUMENTS" | grep "WINEBOTTLERCOPYFOLDERONLY"); then
				mkdir -p "$WINEPREFIX/drive_c/winebottler"
				cp -r "$WINEPREFIX/drive_c/windows/temp/installer/"* "$WINEPREFIX/drive_c/winebottler/"
			
			# normal installation
			else
                cd "$WINEPREFIX/drive_c/windows/temp/installer"
                if test $(echo "$INSTALLER_NAME" | grep .msi); then
                    runSanitized "\"$WINE\" msiexec /i \"C:/windows/temp/installer/$INSTALLER_NAME\" $INSTALLER_ARGUMENTS"
                else
                    runSanitized "\"$WINE\" \"C:/windows/temp/installer/$INSTALLER_NAME\" $INSTALLER_ARGUMENTS"
                fi
                cd -
			fi
			winebottlerTry ln -s "/" "$WINEPREFIX/dosdevices/z:"
			winebottlerTry rm -rf "$WINEPREFIX/drive_c/windows/temp/installer"
		
		else
		
			echo "###BOTTLING### Installing "$INSTALLER_NAME"..."
			# only copy installer
			if test $(echo "$INSTALLER_ARGUMENTS" | grep "WINEBOTTLERCOPYFILEONLY"); then
				mkdir "$WINEPREFIX/drive_c/winebottler"
				cp "$INSTALLER_URL" "$WINEPREFIX/drive_c/winebottler/"
			
			# copy whole folder
			elif test $(echo "$INSTALLER_ARGUMENTS" | grep "WINEBOTTLERCOPYFOLDERONLY"); then
				mkdir -p "$WINEPREFIX/drive_c/winebottler"
				cp -r "$(dirname "$INSTALLER_URL")/"* "$WINEPREFIX/drive_c/winebottler/"
			
			# normal installation
			else
#mkdir -p "$WINEPREFIX/drive_c/windows/temp/installer"
#cp "$INSTALLER_URL" "$WINEPREFIX/drive_c/windows/temp/installer/"
                ln -s "$(dirname "$INSTALLER_URL")" "$WINEPREFIX/drive_c/windows/temp/installer"
                cd "$WINEPREFIX/drive_c/windows/temp/installer"
                if test $(echo "$INSTALLER_NAME" | grep .msi); then
                    runSanitized "\"$WINE\" msiexec /i \"C:/windows/temp/installer/$INSTALLER_NAME\" $INSTALLER_ARGUMENTS"
                else
                    runSanitized "\"$WINE\" \"C:/windows/temp/installer/$INSTALLER_NAME\" $INSTALLER_ARGUMENTS"
                fi
                cd -
#winebottlerTry rm -rf "$WINEPREFIX/drive_c/windows/temp/installer"
                winebottlerTry rm -f "$WINEPREFIX/drive_c/windows/temp/installer"
			fi

		fi
	}
	
	#fix permissions
	chmod -R a+rw "$WINEPREFIX"
}
export -f winebottlerInstall




##########                         Cleanup                             #########
################################################################################
function winebottlerCleanup () {

    #dont load mono
    [ "$REMOVE_MONO" == "1" ] && {
        cat > /tmp/override-dll.reg <<_EOF_
REGEDIT4

[HKEY_CURRENT_USER\Software\Wine\DllOverrides]
"mscoree"=""

_EOF_
        "$WINE" regedit /tmp/override-dll.reg
        rm /tmp/override-dll.reg
    }

    #don't load gecko
    [ "$REMOVE_GECKO" == "1" ] && {
        cat > /tmp/override-dll.reg <<_EOF_
REGEDIT4

[HKEY_CURRENT_USER\Software\Wine\DllOverrides]
"mshtml"=""

_EOF_
        "$WINE" regedit /tmp/override-dll.reg
        rm /tmp/override-dll.reg
    }

    #remove user dir?
    [ "$REMOVE_USERS" == "1" ] && {
        find "$WINEPREFIX/drive_c/users" -maxdepth 1 ! -name "Public" -type d -exec rm -rf "{}" \;
    }

    cd "$WINEPREFIX/drive_c/windows"

    #remove installers?
    [ "$REMOVE_INSTALLERS" == "1" ] && {
        rm -rf installer/*
    }

    #remove temp, logs and printer drivers
    rm -rf temp/*
    rm -rf logs/*
    rm -rf system32/spool/drivers/*

    cd -

    # CLEANUP
    rm -rf "$WINEBOTTLER_TMP"
echo "$WINEBOTTLER_TMP"
}
export -f winebottlerCleanup
